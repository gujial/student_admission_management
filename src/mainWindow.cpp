//
// Created by gujial on 25-5-16.
//

#include "mainWindow.h"

#include "addStudentDialog.h"
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
    actionAddStudent = new QAction("Add Student");
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
    menuFile->addAction(actionAddStudent);
    menuFile->addAction(actionExit);
    menu->addMenu(menuFile);
    menu->addMenu(menuEdit);
    menu->addMenu(menuHelp);
    setMenuBar(menu);

    // 向布局中添加组件
    layout->addWidget(table);

    connect(actionExit, &QAction::triggered, this, &mainWindow::close);
    connect(actionAddStudent, &QAction::triggered, this, [=]() {
        const auto addStudentDlg = new addStudentDialog(this, c);
        addStudentDlg->show();
        if (addStudentDlg->exec() != QDialog::Accepted) {
            QMessageBox::warning(this, "Error", "Add student failed");
        }

        displayStudents();
    });
    connect(table, &QTableWidget::cellChanged, this, &mainWindow::onCellChanged);

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
        QMessageBox::warning(this, "Error", e.what());
    }
    displayStudents();
}

#include "moc_mainWindow.cpp"