//
// Created by gujial on 25-5-16.
//

#include "loginDialog.h"

loginDialog::loginDialog(QWidget *parent, controller *c) {
    setWindowTitle("Login");
    setWindowIcon(QIcon(":/assets/images/icon.png"));

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

    connect(loginButton, &QPushButton::clicked, this, [=]() {
        loginButtonClicked(c);
    });
}

loginDialog::~loginDialog() {
}

void loginDialog::loginButtonClicked(controller *c) {
    try {
        c->userLogin(userNameLineEdit->text(), passwordLineEdit->text());
        accept();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

#include "moc_loginDialog.cpp"