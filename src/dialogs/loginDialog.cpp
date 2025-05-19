//
// Created by gujial on 25-5-16.
//

#include "loginDialog.h"

loginDialog::loginDialog(QWidget *parent, controller *c) {
    setWindowTitle("Login");
    layout = new QGridLayout();
    userNameLabel = new QLabel("username:");
    userNameLineEdit = new QLineEdit();
    passwordLabel = new QLabel("password:");
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login");
    ref_c = c;
    ref_c = new controller(
        "localhost",
        "login",
        "root",
        "041109"
    );

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
    try {
        ref_c->userLogin(userNameLineEdit->text(), passwordLineEdit->text());
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

#include "moc_loginDialog.cpp"