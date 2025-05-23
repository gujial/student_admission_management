//
// Created by gujial on 25-5-21.
//

#include "settingDialog.h"

#include <QMessageBox>

settingDialog::settingDialog(QWidget *parent) {
    setWindowTitle("Setting");
    setWindowIcon(QIcon(":/assets/images/icon.png"));

    auto config = utils::loadConfig("config/config.json");

    hostnameLabel = new QLabel("Database Hostname:");
    hostnameLineEdit = new QLineEdit(QString::fromStdString(config["database_hostname"].get<std::string>()));
    databaseNameLabel = new QLabel("Database Name:");
    databaseNameLineEdit = new QLineEdit(QString::fromStdString(config["database_name"].get<std::string>()));
    portLabel = new QLabel("Database Port:");
    portLineEdit = new QLineEdit(QString::number(config["database_port"].get<int>()));
    userNameLabel = new QLabel("Database User Name:");
    userNameLineEdit = new QLineEdit(QString::fromStdString(config["database_username"].get<std::string>()));
    passwordLabel = new QLabel("Database Password:");
    passwordLineEdit = new QLineEdit(QString::fromStdString(config["database_password"].get<std::string>()));
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    okButton = new QPushButton("OK");
    okButton->setDefault(true);
    cancelButton = new QPushButton("Cancel");
    layout = new QGridLayout();

    layout->addWidget(hostnameLabel, 0, 0);
    layout->addWidget(hostnameLineEdit, 0, 1);
    layout->addWidget(databaseNameLabel, 1, 0);
    layout->addWidget(databaseNameLineEdit, 1, 1);
    layout->addWidget(portLabel, 2, 0);
    layout->addWidget(portLineEdit, 2, 1);
    layout->addWidget(userNameLabel, 3, 0);
    layout->addWidget(userNameLineEdit, 3, 1);
    layout->addWidget(passwordLabel, 4, 0);
    layout->addWidget(passwordLineEdit, 4, 1);
    layout->addWidget(okButton, 5, 0);
    layout->addWidget(cancelButton, 5, 1);
    setLayout(layout);

    connect(okButton, &QPushButton::clicked, this, &settingDialog::okButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &settingDialog::close);
}

settingDialog::~settingDialog() {  }

void settingDialog::okButtonClicked() {
    if (hostnameLineEdit->text().isEmpty() || databaseNameLineEdit->text().isEmpty() || portLineEdit->text().isEmpty() ||userNameLineEdit->text().isEmpty() ||passwordLineEdit->text().isEmpty()) {
        QMessageBox::information(this, "Error", "Please enter a valid setting");
        return;
    }

    emit saveSettingsRequested();
    accept();
}

#include "moc_settingDialog.cpp"
