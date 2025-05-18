//
// Created by gujial on 25-5-16.
//

#include "loginDialog.h"

loginDialog::loginDialog(QWidget *parent) {
    setWindowTitle("Login");
    layout = new QGridLayout();
    userNameLabel = new QLabel("username:");
    userNameLineEdit = new QLineEdit();
    passwordLabel = new QLabel("password:");
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login");

    layout->addWidget(userNameLabel, 0, 0);
    layout->addWidget(userNameLineEdit, 0, 1);
    layout->addWidget(passwordLabel, 1, 0);
    layout->addWidget(passwordLineEdit, 1, 1);
    layout->addWidget(loginButton, 2, 0, 1, 0);
    setLayout(layout);

    connect(loginButton, &QPushButton::clicked, this, &loginDialog::loginButtonClicked);
}

loginDialog::~loginDialog() {
}

void loginDialog::loginButtonClicked() {

}

#include "moc_loginDialog.cpp"