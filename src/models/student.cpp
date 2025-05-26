//
// Created by gujial on 25-5-7.
//

#include "student.h"

student::student(
    const QString& name,
    const QDate& birthday,
    const QString& number,
    const QString& address,
    const QString& department,
    const QString& classname,
    const QString& gender
    ) {
    this->name = name;
    this->birthday = birthday;
    this->number = number;
    this->address = address;
    this->department = department;
    this->classname = classname;
    this->gender = gender;
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

QString student::getClassname() const {
    return this->classname;
}

void student::setClassname(const QString & classname) {
    this->classname = classname;
}

QString student::getGender() const {
    return this->gender;
}

void student::setGender(const QString & gender) {
    this->gender = gender;
}

QString student::getDepartment() const {
    return this->department;
}

void student::setDepartment(const QString & department) {
    this->department = department;
}
