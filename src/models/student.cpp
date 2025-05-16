//
// Created by gujial on 25-5-7.
//

#include "student.h"

student::student(const QString& name, const QDate& birthday, const QString& number, const QString& address) {
    this->name = name;
    this->birthday = birthday;
    this->number = number;
    this->address = address;
}

QString student::getName() {
    return this->name;
}

QString student::getNumber() {
    return this->number;
}

QString student::getAddress() {
    return this->address;
}

void student::setName(const QString& name) {
    this->name = name;
}

void student::setAddress(const QString & address) {
    this->address = address;
}

void student::setNumber(const QString & number) {
    this->number = number;
}

QDate student::getBirthday() const {
    return this->birthday;
}

void student::setBirthday(const QDate & birthday) {
    this->birthday = birthday;
}
