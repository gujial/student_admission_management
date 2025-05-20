//
// Created by gujial on 25-5-16.
//

#include "mainWindow.h"

#include "aboutDialog.h"
#include "addStudentDialog.h"

mainWindow::mainWindow(QWidget *parent, controller *c) {
    setWindowTitle("Student Admission Management");
    setWindowIcon(QIcon(":/assets/images/icon.png"));

    // 初始化成员变量
    this->c = c;
    menu = new QMenuBar(this);
    menuFile = new QMenu("File");
    menuEdit = new QMenu("Edit");
    menuHelp = new QMenu("Help");
    actionAbout = new QAction("About");
    actionExit = new QAction("Exit");
    actionAddStudent = new QAction("Add Student");
    actionDeleteStudent = new QAction("Delete Student");
    actionSettings = new QAction("Settings");
    actionLogout = new QAction("Logout");
    actionManageUsers = new QAction("Manage users");
    table = new QTableWidget(this);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels(QStringList() << "Student ID" << "Name" << "Birthday" << "Address");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 设置布局
    central = new QWidget(this);
    layout = new QGridLayout(central);
    central->setLayout(layout);
    setCentralWidget(central);

    // 设置菜单
    menuHelp->addAction(actionAbout);
    menuEdit->addAction(actionAddStudent);
    menuEdit->addAction(actionDeleteStudent);
    menuFile->addAction(actionSettings);
    menuFile->addAction(actionManageUsers);
    menuFile->addAction(actionLogout);
    menuFile->addAction(actionExit);
    menu->addMenu(menuFile);
    menu->addMenu(menuEdit);
    menu->addMenu(menuHelp);
    setMenuBar(menu);

    // 向布局中添加组件
    layout->addWidget(table);

    connect(actionExit, &QAction::triggered, this, &QApplication::quit);

    connect(actionAddStudent, &QAction::triggered, this, [this, c]() {
        const auto addStudentDlg = new addStudentDialog(this, c);
        addStudentDlg->show();
        addStudentDlg->exec();
        displayStudents();
    });

    connect(actionAbout, &QAction::triggered, this, [this]() {
        const auto aboutDlg = new aboutDialog(this);
        aboutDlg->show();
    });

    connect(actionDeleteStudent, &QAction::triggered, this, [this, c]() {
        QList<QTableWidgetItem *> selectedItems = table->selectedItems();
        QSet<int> selectedRows;

        if (selectedItems.isEmpty()) {
            QMessageBox::warning(this, "Error", "No Student selected");
            return;
        }

        for (QTableWidgetItem *item : selectedItems) {
            selectedRows.insert(item->row());
        }

        for (int row : selectedRows) {
            try {
                c->deleteStudent(students[row].getNumber());
            } catch (const std::exception &e) {
                QMessageBox::warning(this, "Error", e.what());
            }
        }
        displayStudents();
    });

    connect(actionManageUsers, &QAction::triggered, this, [this, c]() {
        try {
            utils::checkUserPermission(c->loggedInUser.getTypeId());
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", e.what());
            return;
        }

        const auto userManageWd = new userManageWindow(this, c);
        userManageWd->resize(400, 300);
        userManageWd->show();
    });

    connect(table, &QTableWidget::cellChanged, this, &mainWindow::onCellChanged);

    connect(actionLogout, &QAction::triggered, this, [this]() {
        emit logoutRequested();
        close();
    });


    setWindowTitle("Student Admission Management - Welcome "+c->loggedInUser.getUsername());
    displayStudents();
}

mainWindow::~mainWindow() {

}

void mainWindow::displayStudents() {
    updatingTable = true;
    students = c->getStudents();
    table->clearContents();
    table->setRowCount(students.size());

    for (int i = 0; i < students.size(); ++i) {
        student& s = students[i];
        table->setItem(i, 0, new QTableWidgetItem(s.getNumber()));
        table->setItem(i, 1, new QTableWidgetItem(s.getName()));
        table->setItem(i, 2, new QTableWidgetItem(s.getBirthday().toString("yyyy-MM-dd")));
        table->setItem(i, 3, new QTableWidgetItem(s.getAddress()));
    }
    updatingTable = false;
}

void mainWindow::onCellChanged(int row, int column) {
    if (updatingTable) return;

    QString studentId = table->item(row, 0)->text();
    QString name = table->item(row, 1)->text();
    QString birthdayStr = table->item(row, 2)->text();
    QString address = table->item(row, 3)->text();

    QDate birthday = QDate::fromString(birthdayStr, "yyyy-MM-dd");
    if (!birthday.isValid()) {
        QMessageBox::warning(this, "Invalid date", "Birthday format must be yyyy-MM-dd");
        revertRow(row);
        return;
    }

    const student s(
        name,
        QDate::fromString(birthdayStr, "yyyy-MM-dd"),
        studentId,
        address
        );
    try {
        c->modifyStudent(students[row].getNumber(), s);
    } catch (const std::exception& e) {
        revertRow(row);
        QMessageBox::warning(this, "Error", e.what());
    }
}

void mainWindow::revertRow(int row) {
    updatingTable = true;

    student &s = students[row];
    table->item(row, 0)->setText(s.getNumber());
    table->item(row, 1)->setText(s.getName());
    table->item(row, 2)->setText(s.getBirthday().toString("yyyy-MM-dd"));
    table->item(row, 3)->setText(s.getAddress());

    updatingTable = false;
}

#include "moc_mainWindow.cpp"