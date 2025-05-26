//
// Created by gujial on 25-5-19.
//

#include <QApplication>
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

    c->userRegister("administrator", "administrator", "456@123.123", 0);
    // c->userLogin("administrator", "administrator");
}