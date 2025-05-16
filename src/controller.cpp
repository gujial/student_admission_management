//
// Created by gujial on 25-5-7.
//

#include "controller.h"

controller::controller(const QString& db_hostname, const QString& db_name, const QString& db_user, const QString& db_password)
: loggedInUser(user(
    "anonymous",
    "",
    "",
    0
)) {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(db_hostname);
    db.setDatabaseName(db_name);
    db.setUserName(db_user);
    db.setPassword(db_password);

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
        this->loggedInUser = user(
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toInt()
            );
    } else {
        throw std::invalid_argument("Login failed. No matched password");
    }
}

void controller::userRegister(const QString &username, const QString &password, const QString &email, int type_id) const {
    utils::checkFormat(username.toStdString(), email.toStdString(), password.toStdString());

    QSqlQuery query(db);
    query.prepare("insert into user(username, password, email, type_id) values (?, ?, ?, ?);");
    query.bindValue(0, username);
    query.bindValue(1, QString::fromStdString(utils::md5(password.toStdString())));
    query.bindValue(2, email);
    query.bindValue(3, type_id);
    query.exec();
    qDebug() << "Register successfully";
}

void controller::modifyUser(const QString &email, user newUser) const {
    utils::checkEmailFormat(email.toStdString());
    utils::checkFormat(newUser.getUsername().toStdString(), newUser.getPassword().toStdString());

    QSqlQuery query(db);
    query.prepare("update user set username = ?, password = ?, type_id = ? where email = ?;");
    query.bindValue(0, newUser.getUsername());
    query.bindValue(1, QString::fromStdString(utils::md5(newUser.getPassword().toStdString())));
    query.bindValue(2, newUser.getTypeId());
    query.bindValue(3, email);
    query.exec();
    qDebug() << "Modify successfully";
}

std::list<user> controller::getUsers() const {
    std::list<user> users;
    QSqlQuery query(db);
    query.prepare("select username,password,email,type_id form user;");
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

void controller::addStudent(student newStudent) const {
    utils::checkUserPermission(this->loggedInUser.getTypeId());
    utils::checkStudentNameFormat(newStudent.getName().toStdString());

    QSqlQuery query(db);
    query.prepare("insert into student(number, name, birthday, address) values ?, ?, ?, ?;");
    query.bindValue(0, newStudent.getNumber());
    query.bindValue(1, newStudent.getName());
    query.bindValue(2, newStudent.getBirthday());
    query.bindValue(3, newStudent.getAddress());
    query.exec();
    qDebug() << "Add student successfully";
}

void controller::deleteStudent(int studentNum) const {
    utils::checkUserPermission(this->loggedInUser.getTypeId());

    QSqlQuery query(db);
    query.prepare("delete from student where number = ?;");
    query.bindValue(0, studentNum);
    query.exec();
    qDebug() << "Delete student successfully";
}

void controller::modifyStudent(int studentNum, student newStudent) const {
    utils::checkUserPermission(this->loggedInUser.getTypeId());
    utils::checkStudentNameFormat(newStudent.getName().toStdString());

    QSqlQuery query(db);
    query.prepare("update student set name = ?, birthday = ?, address = ? where number = ?;");
    query.bindValue(0, newStudent.getName());
    query.bindValue(1, newStudent.getBirthday());
    query.bindValue(2, newStudent.getAddress());
    query.bindValue(3, studentNum);
    query.exec();
    qDebug() << "Modify student successfully";
}

std::list<student> controller::getStudents() const {
    std::list<student> students;

    QSqlQuery query(db);
    query.prepare("select number, name, birthday, address from student;");
    query.exec();

    while (query.next()) {
        students.emplace_back(
            query.value(1).toString(),
            QDate::fromString(query.value(2).toString()),
            query.value(0).toString(),
            query.value(3).toString()
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

student controller::getStudent(int studentNum) const {
    QSqlQuery query(db);
    query.prepare("select number, name, birthday, address from student where number = ?;");
    query.bindValue(0, studentNum);
    query.exec();

    while (query.next()) {
        return {
            query.value(0).toString(),
            QDate::fromString(query.value(2).toString()),
            query.value(1).toString(),
            query.value(3).toString()
        };
    }
    throw std::runtime_error("Student not found");
}

