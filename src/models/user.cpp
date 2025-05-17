//
// Created by gujial on 25-5-13.
//

#include "user.h"

user::user(const QString &username, const QString &password, const QString &email, int type_id) {
    this->username = username;
    this->password = QString::fromStdString(utils::md5(password.toStdString()));
    this->email = email;
    this->type_id = type_id;
}

QString user::getEmail() {
    return this->email;
}

QString user::getUsername() {
    return this->username;
}

QString user::getPassword() {
    return this->password;
}

int user::getTypeId() const {
    return this->type_id;
}

void user::setEmail(const QString &email) {
    this->email = email;
}

void user::setPassword(const QString &password) {
    this->password = QString::fromStdString(utils::md5(password.toStdString()));
}

void user::setTypeId(int type_id) {
    this->type_id = type_id;
}

void user::setUsername(const QString &username) {
    this->username = username;
}
