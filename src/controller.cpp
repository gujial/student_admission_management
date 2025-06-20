//
// Created by gujial on 25-5-7.
//

#include "controller.h"

controller::controller(const QString& db_hostname, const QString& db_name, const QString& db_user, const QString& db_password, int db_port)
: loggedInUser(user(
    "anonymous",
    "",
    "",
    1
)) {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(db_hostname);
    db.setDatabaseName(db_name);
    db.setUserName(db_user);
    db.setPassword(db_password);
    db.setPort(db_port);

    if (!db.open()) {
        throw std::runtime_error("Failed to open database");
    }
    qDebug() << "Database opened";

    QSqlQuery query(db);
    query.exec("select type_id,type_name from user_type");
    while (query.next()) {
        this->userTypes.insert(std::make_pair(query.value(0).toInt(), query.value(1).toString()));
    }
}

controller::~controller() {
    db.close();
}

QString controller::getUserTypeName(int type_id) {
    return userTypes[type_id];
}

void controller::userLogin(const QString &username, const QString &password) {
    utils::checkFormat(username.toStdString(), password.toStdString());

    QSqlQuery query(db);
    query.prepare("select username from user where username = ? and password = ?;");
    query.bindValue(0, username);
    query.bindValue(1, QString::fromStdString(utils::md5(password.toStdString())));
    query.exec();
    if (query.next()) {
        qDebug() << "Login successful";

        query.prepare("select username,password,email,type_id from user where username = ?");
        query.bindValue(0, username);
        query.exec();
        query.next();
        this->loggedInUser = user(
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toInt()
            );

        this->getDepartments();
        this->getClassnames();
    } else {
        throw std::invalid_argument("Login failed. No matched password");
    }
}

void controller::userRegister(const QString &username, const QString &password, const QString &email, int type_id) const {
    utils::checkUserPermission(this->loggedInUser.getTypeId());
    utils::checkFormat(username.toStdString(), email.toStdString(), password.toStdString());

    QSqlQuery query(db);
    query.prepare("insert into user(username, password, email, type_id) values (?, ?, ?, ?);");
    query.bindValue(0, username);
    query.bindValue(1, QString::fromStdString(utils::md5(password.toStdString())));
    query.bindValue(2, email);
    query.bindValue(3, type_id);
    if (query.exec()) {
        qDebug() << "Register successfully";
    } else {
        throw std::invalid_argument(query.lastError().text().toStdString());
    }
}

void controller::modifyUser(const QString &email, const QString& newEmail, const QString& username, const QString& typeId) {
    utils::checkUserPermission(this->loggedInUser.getTypeId());
    utils::checkEmailFormat(newEmail.toStdString());
    utils::checkUsernameFormat(username.toStdString());

    if (typeId.toInt() == 1) {
        checkOperationSafe(newEmail);
    }

    QSqlQuery query(db);
    query.prepare("update user set username = ?, type_id = ?, email = ? where email = ?;");
    query.bindValue(0, username);
    query.bindValue(1, typeId);
    query.bindValue(2, newEmail);
    query.bindValue(3, email);
    if (query.exec()) {
        qDebug() << "Modify successfully";
    } else {
        throw std::invalid_argument(query.lastError().text().toStdString());
    }
}

QList<user> controller::getUsers() const {
    QList<user> users;
    QSqlQuery query(db);
    query.prepare("select username,password,email,type_id from user;");
    query.exec();

    while (query.next()) {
        users.emplace_back(
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toInt()
            );
    }

    return users;
}

void controller::addStudent(student newStudent) {
    utils::checkUserPermission(this->loggedInUser.getTypeId());
    utils::checkStudentNameFormat(newStudent.getName().toStdString());
    utils::checkStudentNumberFormat(newStudent.getNumber().toStdString(),
        getDepartmentNumber(newStudent.getDepartment()).toStdString(),
        getClassnameNumber(newStudent.getClassname()).toStdString());
    utils::checkGenderFormat(newStudent.getGender().toStdString());

    QSqlQuery query(db);
    query.prepare("insert into student(number, name, birthday, address, department, classname, gender) values (?, ?, ?, ?, ?, ?, ?);");
    query.bindValue(0, newStudent.getNumber());
    query.bindValue(1, newStudent.getName());
    query.bindValue(2, newStudent.getBirthday());
    query.bindValue(3, newStudent.getAddress());
    query.bindValue(4, newStudent.getDepartment());
    query.bindValue(5, newStudent.getClassname());
    query.bindValue(6, newStudent.getGender());
    if (query.exec()) {
        qDebug() << "Add student successfully";
    } else {
        throw std::invalid_argument(query.lastError().text().toStdString());
    }
}

void controller::deleteStudent(const QString& studentNum) const {
    utils::checkUserPermission(this->loggedInUser.getTypeId());

    QSqlQuery query(db);
    query.prepare("delete from student where number = ?;");
    query.bindValue(0, studentNum);
    if (query.exec()) {
        qDebug() << "Delete student successfully";
    } else {
        throw std::invalid_argument(query.lastError().text().toStdString());
    }
}

void controller::modifyStudent(const QString& studentNum, student newStudent) {
    utils::checkUserPermission(this->loggedInUser.getTypeId());
    utils::checkStudentNameFormat(newStudent.getName().toStdString());
    utils::checkStudentNumberFormat(newStudent.getNumber().toStdString(),
        getDepartmentNumber(newStudent.getDepartment()).toStdString(),
        getClassnameNumber(newStudent.getClassname()).toStdString());
    utils::checkGenderFormat(newStudent.getGender().toStdString());

    QSqlQuery query(db);
    query.prepare("update student set name = ?, birthday = ?, address = ?, number = ?, department = ?, classname = ?, gender = ? where number = ?;");
    query.bindValue(0, newStudent.getName());
    query.bindValue(1, newStudent.getBirthday());
    query.bindValue(2, newStudent.getAddress());
    query.bindValue(3, newStudent.getNumber());
    query.bindValue(4, newStudent.getDepartment());
    query.bindValue(5, newStudent.getClassname());
    query.bindValue(6, newStudent.getGender());
    query.bindValue(7, studentNum);
    if (query.exec()) {
        qDebug() << "Modify student successfully";
    } else {
        throw std::invalid_argument(query.lastError().text().toStdString());
    }
}

QList<student> controller::getStudents() const {
    QList<student> students;

    QSqlQuery query(db);
    query.prepare("select number, name, birthday, address, department, classname, gender from student;");
    query.exec();

    while (query.next()) {
        students.emplace_back(
            query.value(1).toString(),
            QDate::fromString(query.value(2).toString(),"yyyy-MM-dd"),
            query.value(0).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString()
            );
    }

    return students;
}

user controller::getUser(const QString& email) const {
    QSqlQuery query(db);
    query.prepare("select username, password, email, type_id from user where email = ?;");
    query.bindValue(0, email);
    query.exec();

    while (query.next()) {
        return {
            query.value(0).toString(),
                query.value(1).toString(),
                query.value(2).toString(),
                query.value(3).toInt()
        };
    }
    throw std::runtime_error("User not found");
}

student controller::getStudent(const QString& studentNum) const {
    QSqlQuery query(db);
    query.prepare("select number, name, birthday, address from student where number = ?;");
    query.bindValue(0, studentNum);
    query.exec();

    while (query.next()) {
        return {
            query.value(0).toString(),
            QDate::fromString(query.value(2).toString()),
            query.value(1).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString()
        };
    }
    throw std::runtime_error("Student not found");
}

void controller::modifyUserPassword(const QString &email, const QString &password) const {
    utils::checkUserPermission(this->loggedInUser.getTypeId());
    utils::checkPasswordFormat(password.toStdString());
    utils::checkEmailFormat(email.toStdString());

    QSqlQuery query(db);
    query.prepare("update user set password = ? where email = ?;");
    query.bindValue(0, QString::fromStdString(utils::md5(password.toStdString())));
    query.bindValue(1, email);
    if (query.exec()) {
        qDebug() << "Modify user password successfully";
    } else {
        throw std::invalid_argument(query.lastError().text().toStdString());
    }
}

void controller::deleteUser(const QString &email) const {
    utils::checkUserPermission(this->loggedInUser.getTypeId());
    utils::checkPasswordFormat(email.toStdString());

    QSqlQuery query(db);
    query.prepare("delete from user where email = ?;");
    query.bindValue(0, email);
    if (query.exec()) {
        qDebug() << "Delete user successfully";
    } else {
        throw std::invalid_argument(query.lastError().text().toStdString());
    }
}

void controller::checkOperationSafe(const QString &email) {
    if (email == loggedInUser.getEmail()) {
        throw std::invalid_argument("Can't operate to yourself.");
    }
}

void controller::getDepartments() {
    QList<department> departments;

    QSqlQuery query(db);
    query.prepare("select name, number from department;");
    query.exec();

    while (query.next()) {
        departments.emplace_back(
            query.value(0).toString(),
            query.value(1).toString()
            );
    }

    this->departments = departments;
}

void controller::getClassnames() {
    QList<classname> classnames;

    QSqlQuery query(db);
    query.prepare("select name, number, department from classname;");
    query.exec();

    while (query.next()) {
        classnames.emplace_back(
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(2).toString()
            );
    }

    this->classnames = classnames;
}

QString controller::getDepartmentNumber(const QString& departmentName) {
    for (const auto &department : this->departments ) {
        if (department.getName() == departmentName) {
            return department.getNumber();
        }
    }
    throw std::invalid_argument("Department not found");
}

QString controller::getClassnameNumber(const QString& className) {
    for (const auto &classname : this->classnames ) {
        if (classname.getName() == className) {
            return classname.getNumber();
        }
    }
    throw std::invalid_argument("Classname not found");
}

