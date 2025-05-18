//
// Created by gujial on 25-5-16.
//

#include "loginDialog.h"

loginDialog::loginDialog(QWidget *parent) {
    setWindowTitle("Login");
    layout = new QGridLayout();
    dbHostnameLabel = new QLabel("database hostname:");
    dbHostnameLineEdit = new QLineEdit();
    dbPortLabel = new QLabel("database port:");
    dbPortLineEdit = new QLineEdit();
    dbUserNameLabel = new QLabel("database username:");
    dbUserNameLineEdit = new QLineEdit();
    dbPasswordLabel = new QLabel("database password:");
    dbPasswordLineEdit = new QLineEdit();
    dbNameLabel = new QLabel("database name:");
    dbNameLineEdit = new QLineEdit();
    userNameLabel = new QLabel("username:");
    userNameLineEdit = new QLineEdit();
    passwordLabel = new QLabel("password:");
    passwordLineEdit = new QLineEdit();
    loginButton = new QPushButton("Login");

    layout->addWidget(dbHostnameLabel, 0, 0);
    layout->addWidget(dbHostnameLineEdit, 0, 1);
    layout->addWidget(dbPortLabel, 1, 0);
    layout->addWidget(dbPortLineEdit, 1, 1);
    layout->addWidget(dbUserNameLabel, 2, 0);
    layout->addWidget(dbUserNameLineEdit, 2, 1);
    layout->addWidget(dbPasswordLabel, 3, 0);
    layout->addWidget(dbPasswordLineEdit, 3, 1);
    layout->addWidget(dbNameLabel, 4, 0);
    layout->addWidget(dbNameLineEdit, 4, 1);
    layout->addWidget(userNameLabel, 5, 0);
    layout->addWidget(userNameLineEdit, 5, 1);
    layout->addWidget(passwordLabel, 6, 0);
    layout->addWidget(passwordLineEdit, 6, 1);
    layout->addWidget(loginButton, 7, 0, 1, 0);
    setLayout(layout);
}

loginDialog::~loginDialog() {

}

#include "moc_loginDialog.cpp"