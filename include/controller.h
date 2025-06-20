//
// Created by gujial on 25-5-7.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "student.h"
#include "utils.h"
#include "user.h"
#include "classname.h"
#include "department.h"

class controller {
public:
    user loggedInUser;
    QList<department> departments;
    QList<classname> classnames;

    controller(const QString& db_hostname, const QString& db_name, const QString& db_user, const QString& db_password, int db_port);
    ~controller();
    void userLogin(const QString& username, const QString& password);
    void userRegister(const QString& username, const QString& password, const QString& email, int type_id) const;
    QList<user> getUsers() const;
    void modifyUser(const QString &email, const QString& newEmail, const QString& username, const QString& typeId);
    QString getUserTypeName(int type_id);
    user getUser(const QString& email) const;
    void modifyUserPassword(const QString& email, const QString& password) const;
    void deleteUser(const QString& email) const;

    void addStudent(student newStudent);
    void deleteStudent(const QString& studentNum) const;
    QList<student> getStudents() const;
    void modifyStudent(const QString& studentNum, student newStudent);
    student getStudent(const QString& studentNum) const;

    void getDepartments();
    void getClassnames();
    QString getDepartmentNumber(const QString& departmentName);
    QString getClassnameNumber(const QString& className);
private:
    QSqlDatabase db;
    std::map<int, QString> userTypes;

    void checkOperationSafe(const QString& email);
};



#endif //CONTROLLER_H
