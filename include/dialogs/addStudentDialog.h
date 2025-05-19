//
// Created by gujial on 25-5-16.
//

#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "controller.h"

class addStudentDialog : public QDialog {
Q_OBJECT
public:
    explicit addStudentDialog(QWidget *parent, controller *c);
    ~addStudentDialog();

private slots:
    void addButtonClicked(controller *c);

private:
    QLabel *numberLabel;
    QLineEdit *numberLineEdit;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *birthdayLabel;
    QLineEdit *birthdayLineEdit;
    QLabel *addressLabel;
    QLineEdit *addressLineEdit;
    QGridLayout *layout;
    QPushButton *button;
};



#endif //ADDSTUDENTDIALOG_H
