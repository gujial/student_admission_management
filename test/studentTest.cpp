//
// Created by gujial on 25-5-19.
//

#include <QApplication>
#include <QDate>
#include "controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    controller * c = new controller(
        "localhost",
        "login",
        "root",
        "041109",
        3306
    );

    QDate birthday = QDate(2020,2,5);

    c->userLogin("administrator", "administrator");
    c->addStudent({
        "aaaa",
        birthday,
        "465567",
        "china",
        "department",
        "classname",
        "male"
    });
}