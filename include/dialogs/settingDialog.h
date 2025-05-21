//
// Created by gujial on 25-5-21.
//

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

#include "utils.h"

class settingDialog : public QDialog {
    Q_OBJECT
public:
    explicit settingDialog(QWidget *parent);
    ~settingDialog() override;

private slots:
    void okButtonClicked();

private:
    QLabel *hostnameLabel;
    QLineEdit *hostnameLineEdit;
    QLabel *databaseNameLabel;
    QLineEdit *databaseNameLineEdit;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QGridLayout *layout;

signals:
    void saveSettingsRequested();
};

#endif //SETTINGDIALOG_H
