//
// Created by gujial on 25-5-16.
//

#include "loginDialog.h"

loginDialog::loginDialog(QWidget *parent) {
    setWindowTitle("Login");
    layout = new QGridLayout();
    dbHostnameLabel = new QLabel("database hostname:");
    dbHostnameLineEdit = new QLineEdit("localhost");
    dbUserNameLabel = new QLabel("database username:");
    dbUserNameLineEdit = new QLineEdit("root");
    dbPasswordLabel = new QLabel("database password:");
    dbPasswordLineEdit = new QLineEdit();
    dbPasswordLineEdit->setEchoMode(QLineEdit::Password);
    dbNameLabel = new QLabel("database name:");
    dbNameLineEdit = new QLineEdit("login");
    userNameLabel = new QLabel("username:");
    userNameLineEdit = new QLineEdit();
    passwordLabel = new QLabel("password:");
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login");

    layout->addWidget(dbHostnameLabel, 0, 0);
    layout->addWidget(dbHostnameLineEdit, 0, 1);
    layout->addWidget(dbUserNameLabel, 1, 0);
    layout->addWidget(dbUserNameLineEdit, 1, 1);
    layout->addWidget(dbPasswordLabel, 2, 0);
    layout->addWidget(dbPasswordLineEdit, 2, 1);
    layout->addWidget(dbNameLabel, 3, 0);
    layout->addWidget(dbNameLineEdit, 3, 1);
    layout->addWidget(userNameLabel, 4, 0);
    layout->addWidget(userNameLineEdit, 4, 1);
    layout->addWidget(passwordLabel, 5, 0);
    layout->addWidget(passwordLineEdit, 5, 1);
    layout->addWidget(loginButton, 6, 0, 1, 0);
    setLayout(layout);

    connect(loginButton, &QPushButton::clicked, this, &loginDialog::loginButtonClicked);
}

loginDialog::~loginDialog() {
}

void loginDialog::loginButtonClicked() {

}

#include "moc_loginDialog.cpp"