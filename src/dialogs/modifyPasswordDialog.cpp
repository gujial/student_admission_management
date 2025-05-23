//
// Created by gujial on 25-5-20.
//

#include "modifyPasswordDialog.h"

modifyPasswordDialog::modifyPasswordDialog(QWidget *parent, controller *c, const QString& email) {
    setWindowTitle(email);
    setWindowIcon(QIcon(":/assets/images/icon.png"));

    passwordLabel = new QLabel("new password:");
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLabel2 = new QLabel("password again:");
    passwordLineEdit2 = new QLineEdit();
    passwordLineEdit2->setEchoMode(QLineEdit::Password);
    button = new QPushButton("Modify password");
    layout = new QGridLayout();

    layout->addWidget(passwordLabel, 0,0);
    layout->addWidget(passwordLineEdit, 0, 1);
    layout->addWidget(passwordLabel2, 1, 0);
    layout->addWidget(passwordLineEdit2, 1, 1);
    layout->addWidget(button, 3, 0, 1, 0);
    setLayout(layout);

    connect(button, &QPushButton::clicked, this, [this, email, c]() {
        buttonClicked(c, email);
    });
}

modifyPasswordDialog::~modifyPasswordDialog() {

}

void modifyPasswordDialog::buttonClicked(controller *c, const QString& email) {
    if (passwordLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Password can't be empty");
        return;
    }

    if (passwordLineEdit->text() != passwordLineEdit2->text()) {
        QMessageBox::warning(this, "Error", "Two passwords are not same");
        return;
    }

    try {
        c->modifyUserPassword(email, passwordLineEdit->text());
        accept();
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

#include "moc_modifyPasswordDialog.cpp"