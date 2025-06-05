//
// Created by gujial on 25-5-16.
//

#include "addStudentDialog.h"

addStudentDialog::addStudentDialog(QWidget *parent, controller *c) {
    setWindowTitle("Add Student");
    setWindowIcon(QIcon(":/assets/images/icon.png"));

    numberLabel = new QLabel("student number:");
    numberLineEdit = new QLineEdit();
    numberLineEdit->setPlaceholderText("Should be numbers");
    nameLabel = new QLabel("name:");
    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("Start with letter or chinese charactor");
    birthdayLabel = new QLabel("birthday:");
    birthdayLineEdit = new QLineEdit(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    birthdayLineEdit->setPlaceholderText("yyyy-MM-dd");
    addressLabel = new QLabel("address:");
    addressLineEdit = new QLineEdit();
    departmentLabel = new QLabel("department:");
    departmentComboBox = new QComboBox();
    for (const auto &dept: c->departments) {
        departmentComboBox->addItem(dept.getName());
    }
    classnameLabel = new QLabel("classname:");
    classnameComboBox = new QComboBox();
    for (const auto &cls: c->classnames) {
        if (cls.getDepartment() == departmentComboBox->currentText()) {
            classnameComboBox->addItem(cls.getName());
        }
    }
    genderLabel = new QLabel("gender:");
    genderComboBox = new QComboBox();
    genderComboBox->addItem("Male");
    genderComboBox->addItem("Female");
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
    layout->addWidget(departmentLabel, 4, 0);
    layout->addWidget(departmentComboBox, 4, 1);
    layout->addWidget(classnameLabel, 5, 0);
    layout->addWidget(classnameComboBox, 5, 1);
    layout->addWidget(genderLabel, 6, 0);
    layout->addWidget(genderComboBox, 6, 1);
    layout->addWidget(button, 7, 0, 1, 0);
    setLayout(layout);

    connect(button, &QPushButton::clicked, this, [this, c]() { addButtonClicked(c); });

    connect(departmentComboBox, &QComboBox::currentTextChanged, this, [this, c]() {
        classnameComboBox->clear();
        QString currentDept = departmentComboBox->currentText();

        for (const auto &cls: c->classnames) {
            if (cls.getDepartment() == currentDept) {
                classnameComboBox->addItem(cls.getName());
            }
        }
    });
}

addStudentDialog::~addStudentDialog() {}

void addStudentDialog::addButtonClicked(controller *c) {
    if (numberLineEdit->text().isEmpty() || nameLineEdit->text().isEmpty() || birthdayLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Number, name and birthday can't be empty.");
        return;
    }

    try {
        const QString birthdayStr = birthdayLineEdit->text();

        if (const QRegularExpression regex("^\\d{4}-\\d{2}-\\d{2}$"); !regex.match(birthdayStr).hasMatch()) {
            QMessageBox::warning(this, "Invalid date", "Birthday format must be yyyy-MM-dd.");
            return;
        }

        const QDate birthday = QDate::fromString(birthdayStr, "yyyy-MM-dd");
        if (!birthday.isValid()) {
            QMessageBox::warning(this, "Invalid date", "Input value is invalid.");
            return;
        }

        if (QDate today = QDate::currentDate(); birthday > today || birthday.year() < 1900) {
            QMessageBox::warning(this, "Invalid date", "Input value is invalid.");
            return;
        }

        c->addStudent({
                nameLineEdit->text(),
                birthday,
                numberLineEdit->text(),
                addressLineEdit->text(),
                departmentComboBox->currentText(),
                classnameComboBox->currentText(),
                genderComboBox->currentText(),
        });
        accept();
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

#include "moc_addStudentDialog.cpp"
