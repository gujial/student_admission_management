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
    actionFindStudent = new QAction("Find Student");
    actionNextMatch = new QAction("Next Match");
    actionPrevMatch = new QAction("Previous Match");
    actionNextMatch->setEnabled(false);
    actionPrevMatch->setEnabled(false);
    table = new QTableWidget(this);
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels(QStringList() << "Student ID" << "Name" << "Gender" << "Birthday" << "Address" << "Department" << "Classname");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    actionAddStudent->setShortcut(QKeySequence("Ctrl+N"));
    actionDeleteStudent->setShortcut(QKeySequence(Qt::Key_Delete));
    actionFindStudent->setShortcut(QKeySequence("Ctrl+F"));
    actionPrevMatch->setShortcut(QKeySequence(Qt::Key_F2));
    actionNextMatch->setShortcut(QKeySequence(Qt::Key_F3));
    actionSettings->setShortcut(QKeySequence("Ctrl+P"));
    actionManageUsers->setShortcut(QKeySequence("Ctrl+U"));
    actionExit->setShortcut(QKeySequence("Ctrl+Q"));
    actionAbout->setShortcut(QKeySequence(Qt::Key_F1));
    actionLogout->setShortcut(QKeySequence("Ctrl+L"));

    // 设置布局
    central = new QWidget(this);
    layout = new QGridLayout(central);
    central->setLayout(layout);
    setCentralWidget(central);

    // 设置菜单
    menuHelp->addAction(actionAbout);
    menuEdit->addAction(actionAddStudent);
    menuEdit->addAction(actionDeleteStudent);
    menuEdit->addAction(actionFindStudent);
    menuEdit->addAction(actionPrevMatch);
    menuEdit->addAction(actionNextMatch);
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
        addStudentDlg->resize(400, 300);
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

        for (QTableWidgetItem *item: selectedItems) {
            selectedRows.insert(item->row());
        }

        for (int row: selectedRows) {
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

    connect(actionFindStudent, &QAction::triggered, this, [this]() {
        bool ok;
        QString keyword =
                QInputDialog::getText(this, "Find Student", "Enter name, ID, or address:", QLineEdit::Normal, "", &ok);

        if (!ok || keyword.isEmpty())
            return;

        matchedRows.clear();
        currentMatchIndex = -1;

        for (int i = 0; i < table->rowCount(); ++i) {
            for (int j = 0; j < table->columnCount(); ++j) {
                QTableWidgetItem *item = table->item(i, j);
                if (item && item->text().contains(keyword, Qt::CaseInsensitive)) {
                    matchedRows.append(i);
                    break;
                }
            }
        }

        if (matchedRows.isEmpty()) {
            QMessageBox::information(this, "No Match", "No matching student found.");
            actionNextMatch->setEnabled(false);
            actionPrevMatch->setEnabled(false);
            return;
        }

        currentMatchIndex = 0;
        highlightMatch();

        actionNextMatch->setEnabled(true);
        actionPrevMatch->setEnabled(true);
    });

    connect(actionNextMatch, &QAction::triggered, this, [this]() {
        if (matchedRows.isEmpty())
            return;

        currentMatchIndex = (currentMatchIndex + 1) % matchedRows.size(); // 循环
        highlightMatch();
    });

    connect(actionPrevMatch, &QAction::triggered, this, [this]() {
        if (matchedRows.isEmpty())
            return;

        currentMatchIndex = (currentMatchIndex - 1 + matchedRows.size()) % matchedRows.size(); // 循环
        highlightMatch();
    });

    connect(actionSettings, &QAction::triggered, this, [this]() {
        const auto settingDlg = new settingDialog(this);

        connect(settingDlg, &settingDialog::saveSettingsRequested, [this]() {
            emit logoutRequested();
            close();
        });

        settingDlg->exec();
    });

    setWindowTitle("Student Admission Management - Welcome " + c->loggedInUser.getUsername());
    displayStudents();
}

mainWindow::~mainWindow() {}

void mainWindow::displayStudents() {
    updatingTable = true;
    students = c->getStudents();
    table->clearContents();
    table->setRowCount(students.size());

    for (int i = 0; i < students.size(); ++i) {
        student &s = students[i];
        table->setItem(i, 0, new QTableWidgetItem(s.getNumber()));
        table->setItem(i, 1, new QTableWidgetItem(s.getName()));

        QComboBox *genderBox = new QComboBox();
        genderBox->addItems({"Male", "Female"});
        genderBox->setCurrentText(s.getGender());
        table->setCellWidget(i, 2, genderBox);

        table->setItem(i, 3, new QTableWidgetItem(s.getBirthday().toString("yyyy-MM-dd")));
        table->setItem(i, 4, new QTableWidgetItem(s.getAddress()));
        table->setItem(i, 5, new QTableWidgetItem(s.getDepartment()));
        table->setItem(i, 6, new QTableWidgetItem(s.getClassname()));

        connect(genderBox, &QComboBox::currentTextChanged, this, [this](const QString &newGender) {
            if (!updatingTable) {
                onCellChanged(i, 2);
            }
        });
    }
    updatingTable = false;
}

void mainWindow::onCellChanged(int row, int column) {
    if (updatingTable)
        return;

    QString studentId = table->item(row, 0)->text();
    QString name = table->item(row, 1)->text();
    QString birthdayStr = table->item(row, 3)->text();
    QString address = table->item(row, 4)->text();
    QString department = table->item(row, 5)->text();
    QString classname = table->item(row, 6)->text();
    QComboBox *genderBox = qobject_cast<QComboBox *>(table->cellWidget(row, 2));
    QString gender = genderBox ? genderBox->currentText() : "";

    if (const QRegularExpression regex("^\\d{4}-\\d{2}-\\d{2}$"); !regex.match(birthdayStr).hasMatch()) {
        QMessageBox::warning(this, "Invalid date", "Birthday format must be yyyy-MM-dd.");
        revertRow(row);
        return;
    }

    const QDate birthday = QDate::fromString(birthdayStr, "yyyy-MM-dd");
    if (!birthday.isValid()) {
        QMessageBox::warning(this, "Invalid date", "Input value is invalid.");
        revertRow(row);
        return;
    }

    if (QDate today = QDate::currentDate(); birthday > today || birthday.year() < 1900) {
        QMessageBox::warning(this, "Invalid date", "Input value is invalid.");
        revertRow(row);
        return;
    }

    const student s(
        name,
        QDate::fromString(birthdayStr, "yyyy-MM-dd"),
        studentId,
        address,
        department,
        classname,
        gender
        );
    try {
        c->modifyStudent(students[row].getNumber(), s);
        students = c->getStudents();
    } catch (const std::exception &e) {
        revertRow(row);
        QMessageBox::warning(this, "Error", e.what());
    }
}

void mainWindow::revertRow(int row) {
    updatingTable = true;

    student &s = students[row];
    table->item(row, 0)->setText(s.getNumber());
    table->item(row, 1)->setText(s.getName());
    QComboBox *genderBox = qobject_cast<QComboBox *>(table->cellWidget(row, 2));
    if (genderBox)
        genderBox->setCurrentText(s.getGender());
    table->item(row, 3)->setText(s.getBirthday().toString("yyyy-MM-dd"));
    table->item(row, 4)->setText(s.getAddress());
    table->item(row, 5)->setText(s.getDepartment());
    table->item(row, 6)->setText(s.getClassname());

    updatingTable = false;
}

void mainWindow::highlightMatch() {
    if (matchedRows.isEmpty() || currentMatchIndex < 0 || currentMatchIndex >= matchedRows.size())
        return;

    int row = matchedRows[currentMatchIndex];
    table->clearSelection();
    table->selectRow(row);
    table->scrollToItem(table->item(row, 0));
}


#include "moc_mainWindow.cpp"
