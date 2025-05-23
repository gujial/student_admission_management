//
// Created by gujial on 25-5-16.
//

#include "addStudentDialog.h"

addStudentDialog::addStudentDialog(QWidget *parent, controller *c) {
    setWindowTitle("Add Student");
    setWindowIcon(QIcon(":/assets/images/icon.png"));

    numberLabel = new QLabel("student number:");
    numberLineEdit = new QLineEdit();
    nameLabel = new QLabel("name:");
    nameLineEdit = new QLineEdit();
    birthdayLabel = new QLabel("birthday:");
    birthdayLineEdit = new QLineEdit();
    addressLabel = new QLabel("address:");
    addressLineEdit = new QLineEdit();
    layout = new QGridLayout();
    button = new QPushButton("Add Student");

    layout->addWidget(numberLabel, 0, 0);
    layout->addWidget(numberLineEdit, 0, 1);
    layout->addWidget(nameLabel, 1, 0);
    layout->addWidget(nameLineEdit, 1, 1);
    layout->addWidget(birthdayLabel, 2, 0);
    layout->addWidget(birthdayLineEdit, 2, 1);
    layout->addWidget(addressLabel, 3, 0);
    layout->addWidget(addressLineEdit, 3, 1);
    layout->addWidget(button, 4, 0, 1, 0);
    setLayout(layout);

    connect(button, &QPushButton::clicked, this, [this, c]() {
        addButtonClicked(c);
    });
}

addStudentDialog::~addStudentDialog() {
}

void addStudentDialog::addButtonClicked(controller *c) {
    if (numberLineEdit->text().isEmpty() || nameLineEdit->text().isEmpty() || birthdayLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Number, name and birthday can't be empty.");
        return;
    }

    try {
        auto birthday = QDate::fromString(birthdayLineEdit->text(), "yyyy-MM-dd");

        if (!birthday.isValid()) {
            QMessageBox::warning(this, "Error", "Birthday format should be yyyy-MM-dd.");
            return;
        }

        c->addStudent({
            nameLineEdit->text(),
            birthday,
            numberLineEdit->text(),
            addressLineEdit->text()
        });
        accept();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

#include "moc_addStudentDialog.cpp"