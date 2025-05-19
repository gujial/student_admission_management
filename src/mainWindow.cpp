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
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels(QStringList() << "Student ID" << "Name" << "Birthday" << "Address");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    c = new controller(
        "localhost",
        "login",
        "root",
        "041109"
        );

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

    const auto loginDlg = new loginDialog(this, c);
    loginDlg->show();
    if (loginDlg->exec() != QDialog::Accepted) {
       throw std::runtime_error("Error during login");
    }

    displayStudents();
}

mainWindow::~mainWindow() {
    delete c;
}

void mainWindow::displayStudents() const {
    QList<student> students = c->getStudents();
    table->clearContents();
    table->setRowCount(students.size());

    for (int i = 0; i < students.size(); ++i) {
        student& s = students[i];
        table->setItem(i, 0, new QTableWidgetItem(s.getNumber()));
        table->setItem(i, 1, new QTableWidgetItem(s.getName()));
        table->setItem(i, 2, new QTableWidgetItem(s.getBirthday().toString("yyyy-MM-dd")));
        table->setItem(i, 3, new QTableWidgetItem(s.getAddress()));
    }
}

#include "moc_mainWindow.cpp"