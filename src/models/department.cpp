//
// Created by gujial on 25-6-5.
//

#include "department.h"

department::department(const QString &name, const QString &number) {
    this->name = name;
    this->number = number;
}

QString department::getName() const {
    return this->name;
}

QString department::getNumber() const {
    return this->number;
}

void department::setName(const QString &name) {
    this->name = name;
}

void department::setNumber(const QString &number) {
    this->number = number;
}

