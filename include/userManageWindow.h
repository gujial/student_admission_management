//
// Created by gujial on 25-5-19.
//

#ifndef USERMANAGEWINDOW_H
#define USERMANAGEWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QGridLayout>
#include <QAction>
#include <QTableWidget>
#include <QGridLayout>
#include <QHeaderView>
#include <QMessageBox>

#include "addUserDialog.h"
#include "user.h"
#include "controller.h"

class userManageWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit userManageWindow(QWidget *parent, controller *c);
    ~userManageWindow() override;

private:
    QMenuBar *menu;
    QMenu *menuFile;
    QMenu *menuEdit;
    QAction *actionExit;
    QAction *actionAddUser;
    QAction *actionDeleteUser;
    QTableWidget *table;
    QGridLayout *layout;
    QWidget *central;
    QList<user> users;
    bool updatingTable = false;

    void displayUsers(controller *c);
    void onCellChanged(int row, int column);
    void revertRow(int row);
};

#endif //USERMANAGEWINDOW_H
