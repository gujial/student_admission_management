//
// Created by gujial on 25-5-16.
//

#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>

#include "controller.h"

class addUserDialog : public QDialog {
Q_OBJECT
public:
    explicit addUserDialog(QWidget *parent, controller *c);
    ~addUserDialog() override;

private slots:
    void addButtonClicked(controller *c);

private:
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *passwordLabel2;
    QLineEdit *passwordLineEdit2;
    QLabel *typeIdLabel;
    QComboBox *typeIdComboBox;
    QLabel *passwordWarnLabel;
    QGridLayout *layout;
    QPushButton *button;
};



#endif //ADDUSERDIALOG_H
