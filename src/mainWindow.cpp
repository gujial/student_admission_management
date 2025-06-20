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
    statusBar = new QStatusBar(this);
    statusBar->addPermanentWidget(new QLabel("Select one line or more before delete student."));
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
    table->setHorizontalHeaderLabels(QStringList() << "Student ID" << "Name" << "Gender" << "Birthday" << "Address"
                                                   << "Department" << "Classname");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

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
    setStatusBar(statusBar);

    // 设置菜单
    menuHelp->addAction(actionAbout);

    if (c->loggedInUser.getTypeId() == 0) {
        menuEdit->addAction(actionAddStudent);
        menuEdit->addAction(actionDeleteStudent);
        menuFile->addAction(actionManageUsers);
    }

    menuEdit->addAction(actionFindStudent);
    menuEdit->addAction(actionPrevMatch);
    menuEdit->addAction(actionNextMatch);
    menuFile->addAction(actionSettings);
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
        aboutDlg->adjustSize();
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
        userManageWd->adjustSize();
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

    const bool readOnly = c->loggedInUser.getTypeId() != 0;

    for (int i = 0; i < students.size(); ++i) {
        student &s = students[i];

        auto *idItem = new QTableWidgetItem(s.getNumber());
        auto *nameItem = new QTableWidgetItem(s.getName());
        auto *birthdayItem = new QTableWidgetItem(s.getBirthday().toString("yyyy-MM-dd"));
        auto *addressItem = new QTableWidgetItem(s.getAddress());

        if (readOnly) {
            idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
            nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
            birthdayItem->setFlags(birthdayItem->flags() & ~Qt::ItemIsEditable);
            addressItem->setFlags(addressItem->flags() & ~Qt::ItemIsEditable);
        }

        table->setItem(i, 0, idItem);
        table->setItem(i, 1, nameItem);
        table->setItem(i, 3, birthdayItem);
        table->setItem(i, 4, addressItem);

        // Gender ComboBox
        QComboBox *genderBox = new QComboBox();
        genderBox->addItems({"Male", "Female"});
        genderBox->setCurrentText(s.getGender());
        genderBox->setEnabled(!readOnly);
        table->setCellWidget(i, 2, genderBox);

        connect(genderBox, &QComboBox::currentTextChanged, this, [this, i, readOnly](const QString &) {
            if (!readOnly && !updatingTable)
                onCellChanged(i, 2);
        });

        // Department ComboBox
        QComboBox *departmentBox = new QComboBox();
        for (const auto &d: c->departments) {
            departmentBox->addItem(d.getName());
        }
        departmentBox->setCurrentText(s.getDepartment());
        departmentBox->setEnabled(!readOnly);
        table->setCellWidget(i, 5, departmentBox);

        connect(departmentBox, &QComboBox::currentTextChanged, this, [this, i, readOnly](const QString &newDepartment) {
            if (updatingTable || readOnly)
                return;

            if (auto *classnameBox = qobject_cast<QComboBox *>(table->cellWidget(i, 6))) {
                classnameBox->blockSignals(true); // 防止触发 currentTextChanged
                classnameBox->clear();
                for (const auto &cls: c->classnames) {
                    if (cls.getDepartment() == newDepartment) {
                        classnameBox->addItem(cls.getName());
                    }
                }
                if (classnameBox->count() > 0) {
                    classnameBox->setCurrentIndex(0); // 设置为第一个候选项
                }
                classnameBox->blockSignals(false);
            }

            onCellChanged(i, 5);
            onCellChanged(i, 6);
        });


        // Classname ComboBox
        QComboBox *classnameBox = new QComboBox();
        for (const auto &cls: c->classnames) {
            if (cls.getDepartment() == departmentBox->currentText()) {
                classnameBox->addItem(cls.getName());
            }
        }
        classnameBox->setCurrentText(s.getClassname());
        classnameBox->setEnabled(!readOnly);
        table->setCellWidget(i, 6, classnameBox);

        connect(classnameBox, &QComboBox::currentTextChanged, this, [this, i, readOnly](const QString &) {
            if (!readOnly && !updatingTable)
                onCellChanged(i, 6);
        });
    }

    updatingTable = false;
    table->resizeColumnsToContents();
}

void mainWindow::onCellChanged(int row, int column) {
    if (updatingTable)
        return;

    QString studentId = table->item(row, 0)->text();
    QString name = table->item(row, 1)->text();
    QString birthdayStr = table->item(row, 3)->text();
    QString address = table->item(row, 4)->text();

    QComboBox *departmentBox = qobject_cast<QComboBox *>(table->cellWidget(row, 5));
    QString department = departmentBox ? departmentBox->currentText() : "";

    QComboBox *classnameBox = qobject_cast<QComboBox *>(table->cellWidget(row, 6));
    QString classname = classnameBox ? classnameBox->currentText() : "";

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

    studentId.replace(0, 4, c->getDepartmentNumber(department));
    studentId.replace(5, 2, c->getClassnameNumber(classname));

    const student s(name, QDate::fromString(birthdayStr, "yyyy-MM-dd"), studentId, address, department, classname,
                    gender);
    try {
        c->modifyStudent(students[row].getNumber(), s);
        students = c->getStudents();
        displayStudents();
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

    QComboBox *departmentBox = qobject_cast<QComboBox *>(table->cellWidget(row, 5));
    if (departmentBox)
        departmentBox->setCurrentText(s.getDepartment());

    QComboBox *classnameBox = qobject_cast<QComboBox *>(table->cellWidget(row, 6));
    if (classnameBox)
        classnameBox->setCurrentText(s.getClassname());

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
