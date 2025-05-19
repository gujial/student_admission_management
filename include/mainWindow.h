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

#include "controller.h"

class mainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

private:
    QMenuBar *menu;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QAction *actionAbout;
    QAction *actionExit;
    QAction *actionAddStudent;
    QTableWidget *table;
    QGridLayout *layout;
    QWidget *central;
    controller *c = nullptr;

    void displayStudents() const;
};



#endif //MAINWINDOW_H
