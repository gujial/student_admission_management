//
// Created by gujial on 25-5-16.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QGridLayout>
#include <QAction>
#include <QTableWidget>
#include <QGridLayout>
#include <QHeaderView>
#include <QList>
#include <QListWidgetItem>
#include <QSet>
#include <QInputDialog>
#include <regex>
#include <QStatusBar>

#include "controller.h"
#include "userManageWindow.h"
#include "settingDialog.h"

class mainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent, controller *c);
    ~mainWindow() override;

private:
    QMenuBar *menu;
    QStatusBar *statusBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionAddStudent;
    QAction *actionDeleteStudent;
    QAction *actionSettings;
    QAction *actionManageUsers;
    QAction *actionLogout;
    QAction *actionFindStudent;
    QAction *actionNextMatch;
    QAction *actionPrevMatch;
    QTableWidget *table;
    QGridLayout *layout;
    QWidget *central;
    QList<student> students;
    bool updatingTable = false;
    controller *c;
    QList<int> matchedRows;
    int currentMatchIndex = -1;

    void displayStudents();
    void onCellChanged(int row, int column);
    void revertRow(int row);
    void highlightMatch();

signals:
    void logoutRequested();
};



#endif //MAINWINDOW_H
