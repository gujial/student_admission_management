//
// Created by gujial on 25-5-7.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "student.h"
#include "utils.h"
#include "user.h"

class controller {
public:
    controller(const QString& db_hostname, const QString& db_name, const QString& db_user, const QString& db_password);
    ~controller();
    void userLogin(const QString& username, const QString& password);
    void userRegister(const QString& username, const QString& password, const QString& email, int type_id) const;
    std::list<user> getUsers() const;
    void modifyUser(const QString& email, user newUser) const;
    QString getUserTypeName(int type_id);
    user getUser(const QString& email) const;

    void addStudent(student newStudent) const;
    void deleteStudent(int studentNum) const;
    std::list<student> getStudents() const;
    void modifyStudent(int studentNum, student newStudent) const;
    student getStudent(int studentNum) const;
private:
    QSqlDatabase db;
    std::map<int, QString> userTypes;
    user loggedInUser;
};



#endif //CONTROLLER_H
