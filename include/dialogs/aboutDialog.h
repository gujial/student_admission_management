//
// Created by gujial on 25-5-19.
//

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QPixmap>

class aboutDialog : public QDialog {
    Q_OBJECT
public:
    explicit aboutDialog(QWidget *parent = 0);
    ~aboutDialog() override;
private:
    QLabel *nameLabel;
    QLabel *versionLabel;
    QLabel *authorLabel;
    QLabel *iconLabel;
    QGridLayout *layout;
    QPushButton *closeButton;
};

#endif //ABOUTDIALOG_H
