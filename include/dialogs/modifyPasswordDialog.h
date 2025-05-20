//
// Created by gujial on 25-5-20.
//

#ifndef MODIFYPASSWORDDIALOG_H
#define MODIFYPASSWORDDIALOG_H

#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>

#include "controller.h"

class modifyPasswordDialog : public QDialog {
    Q_OBJECT
public:
    explicit modifyPasswordDialog(QWidget *parent, controller *c, const QString& email);
    ~modifyPasswordDialog() override;

private slots:
    void buttonClicked(controller *c, const QString& email);

private:
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *passwordLabel2;
    QLineEdit *passwordLineEdit2;
    QPushButton *button;
    QGridLayout *layout;
};

#endif //MODIFYPASSWORDDIALOG_H
