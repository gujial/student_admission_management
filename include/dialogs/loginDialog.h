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

class loginDialog : public QDialog {
Q_OBJECT
public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog() override;

private:
    QGridLayout *layout;
    QLabel *dbHostnameLabel;
    QLineEdit *dbHostnameLineEdit;
    QLabel *dbUserNameLabel;
    QLineEdit *dbUserNameLineEdit;
    QLabel *dbPasswordLabel;
    QLineEdit *dbPasswordLineEdit;
    QLabel *dbPortLabel;
    QLineEdit *dbPortLineEdit;
    QLabel *dbNameLabel;
    QLineEdit *dbNameLineEdit;
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
};



#endif //LOGINDIALOG_H
