//
// Created by gujial on 25-5-16.
//

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "controller.h"

class loginDialog : public QDialog {
Q_OBJECT
public:
    explicit loginDialog(QWidget *parent, controller *c);
    ~loginDialog() override;

private slots:
    void loginButtonClicked();

private:
    QGridLayout *layout;
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    controller *ref_c;
};



#endif //LOGINDIALOG_H
