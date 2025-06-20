//
// Created by gujial on 25-5-16.
//

#include "addUserDialog.h"

addUserDialog::addUserDialog(QWidget *parent, controller *c) {
    setWindowTitle("Add User");
    setWindowIcon(QIcon(":/assets/images/icon.png"));

    usernameLabel = new QLabel("Username:");
    usernameLineEdit = new QLineEdit();
    usernameLineEdit->setPlaceholderText("Start with letter");
    emailLabel = new QLabel("Email:");
    emailLineEdit = new QLineEdit();
    emailLineEdit->setPlaceholderText("Format is xxx@xxx.xxx and should be letters");
    passwordLabel = new QLabel("Password:");
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setPlaceholderText("More than 6 and less than 20");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLabel2 = new QLabel("Password again:");
    passwordLineEdit2 = new QLineEdit();
    passwordLineEdit2->setPlaceholderText("Should be same with last line edit");
    passwordLineEdit2->setEchoMode(QLineEdit::Password);
    typeIdLabel = new QLabel("User Type:");

    typeIdComboBox = new QComboBox();
    typeIdComboBox->addItem(c->getUserTypeName(0), 0);
    typeIdComboBox->addItem(c->getUserTypeName(1), 1);
    typeIdComboBox->setCurrentIndex(1);

    passwordWarnLabel = new QLabel("Two passwords are not same");
    passwordWarnLabel->setHidden(true);
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
    layout->addWidget(passwordWarnLabel, 4, 1);
    layout->addWidget(typeIdLabel, 5, 0);
    layout->addWidget(typeIdComboBox, 5, 1);
    layout->addWidget(button, 6, 0, 1, 0);
    setLayout(layout);

    connect(button, &QPushButton::clicked, this, [this, c]() {
        addButtonClicked(c);
    });

    connect(passwordLineEdit2, &QLineEdit::textChanged, this, [this]() {
        if (passwordLineEdit2->text() != passwordLineEdit->text()) {
            passwordWarnLabel->setHidden(false);
        } else {
            passwordWarnLabel->setHidden(true);
        }
    });
}

addUserDialog::~addUserDialog() {

}

void addUserDialog::addButtonClicked(controller *c) {
    if (usernameLineEdit->text().isEmpty() || emailLineEdit->text().isEmpty() || passwordLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "All information can't be empty.");
        return;
    }

    if (passwordLineEdit->text() != passwordLineEdit2->text()) {
        QMessageBox::warning(this, "Error", "Two passwords are not same");
        return;
    }

    try {
        c->userRegister(
            usernameLineEdit->text(),
            passwordLineEdit->text(),
            emailLineEdit->text(),
            typeIdComboBox->currentData().toInt()
            );
        accept();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

#include "moc_addUserDialog.cpp"
