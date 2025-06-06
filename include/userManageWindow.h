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
#include <QStatusBar>

#include "addUserDialog.h"
#include "modifyPasswordDialog.h"
#include "user.h"
#include "controller.h"

class userManageWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit userManageWindow(QWidget *parent, controller *c);
    ~userManageWindow() override;

private:
    QMenuBar *menu;
    QStatusBar *statusBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QAction *actionExit;
    QAction *actionAddUser;
    QAction *actionDeleteUser;
    QAction *actionModifyPassword;
    QTableWidget *table;
    QGridLayout *layout;
    QWidget *central;
    QList<user> users;
    bool updatingTable = false;
    controller *c;

    void displayUsers();
    void onCellChanged(int row, int column);
    void revertRow(int row);
    QComboBox *getTypeComboBox(int currentTypeId) const;
};

#endif //USERMANAGEWINDOW_H
