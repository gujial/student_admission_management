//
// Created by gujial on 25-5-16.
//

#include "addUserDialog.h"

addUserDialog::addUserDialog(QWidget *parent, controller *c) {
    setWindowTitle("Add User");
    setWindowIcon(QIcon(":/assets/images/icon.png"));

    usernameLabel = new QLabel("Username:");
    usernameLineEdit = new QLineEdit();
    emailLabel = new QLabel("Email:");
    emailLineEdit = new QLineEdit();
    passwordLabel = new QLabel("Password:");
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLabel2 = new QLabel("Password again:");
    passwordLineEdit2 = new QLineEdit();
    passwordLineEdit2->setEchoMode(QLineEdit::Password);
    typeIdLabel = new QLabel("Type Id:");
    typeIdLineEdit = new QLineEdit();
    button = new QPushButton("Add User");
    layout = new QGridLayout();

    layout->addWidget(usernameLabel, 0, 0);
    layout->addWidget(usernameLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(emailLineEdit, 1, 1);
    layout->addWidget(passwordLabel, 2, 0);
    layout->addWidget(passwordLineEdit, 2, 1);
    layout->addWidget(passwordLabel2, 3, 0);
    layout->addWidget(passwordLineEdit2, 3, 1);
    layout->addWidget(typeIdLabel, 4, 0);
    layout->addWidget(typeIdLineEdit, 4, 1);
    layout->addWidget(button, 5, 0, 1, 0);
    setLayout(layout);

    connect(button, &QPushButton::clicked, this, [this, c]() {
        addButtonClicked(c);
    });
}

addUserDialog::~addUserDialog() {

}

void addUserDialog::addButtonClicked(controller *c) {
    if (passwordLineEdit->text() != passwordLineEdit2->text()) {
        QMessageBox::warning(this, "Error", "Two passwords are not same");
        return;
    }

    try {
        c->userRegister(
            usernameLineEdit->text(),
            passwordLineEdit->text(),
            emailLineEdit->text(),
            typeIdLineEdit->text().toInt()
            );
        accept();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

#include "moc_addUserDialog.cpp"
