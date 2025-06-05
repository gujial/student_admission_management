//
// Created by gujial on 25-6-5.
//

#include "classname.h"

classname::classname(const QString &name, const QString &number, const QString &department) {
    this->name = name;
    this->number = number;
    this->department = department;
}

QString classname::getName() const {
    return this->name;
}

QString classname::getNumber() const {
    return this->number;
}

QString classname::getDepartment() const {
    return this->department;
}

void classname::setName(const QString &name) {
    this->name = name;
}

void classname::setNumber(const QString &number) {
    this->number = number;
}

void classname::setDepartment(const QString &department) {
    this->department = department;
}