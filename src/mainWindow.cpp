//
// Created by gujial on 25-5-16.
//

#include "mainWindow.h"
#include "loginDialog.h"

mainWindow::mainWindow(QWidget *parent) {
    setWindowTitle("Student Admission Management");

    // 初始化成员变量
    menu = new QMenuBar(this);
    menuFile = new QMenu("File");
    menuEdit = new QMenu("Edit");
    menuHelp = new QMenu("Help");
    actionAbout = new QAction("About");
    actionExit = new QAction("Exit");
    table = new QTableWidget(this);

    // 设置布局
    central = new QWidget(this);
    layout = new QGridLayout(central);
    central->setLayout(layout);
    setCentralWidget(central);

    // 设置菜单
    menuHelp->addAction(actionAbout);
    menuFile->addAction(actionExit);
    menu->addMenu(menuFile);
    menu->addMenu(menuEdit);
    menu->addMenu(menuHelp);
    setMenuBar(menu);

    // 向布局中添加组件
    layout->addWidget(table);
    connect(actionExit, &QAction::triggered, this, &mainWindow::close);

    if (c == nullptr) {
        const auto loginDlg = new loginDialog(this, c);
        loginDlg->show();
        if (loginDlg->exec() != QDialog::Accepted || c == nullptr) {
            throw std::runtime_error("Error during login");
        }
    }
}

mainWindow::~mainWindow() {

}

#include "moc_mainWindow.cpp"