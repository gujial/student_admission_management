//
// Created by gujial on 25-5-19.
//

#include "userManageWindow.h"

userManageWindow::userManageWindow(QWidget *parent, controller *c) {
    setWindowTitle("Users");
    setWindowIcon(QIcon(":/assets/images/icon.png"));
    this->c = c;

    menu = new QMenuBar(this);
    menuFile = new QMenu("File");
    menuEdit = new QMenu("Edit");
    actionExit = new QAction("Exit");
    actionAddUser = new QAction("Add user");
    actionDeleteUser = new QAction("Delete user");
    table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList() << "Username" << "Email" << "Type ID");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    central = new QWidget(this);
    layout = new QGridLayout(central);
    central->setLayout(layout);
    setCentralWidget(central);

    menuEdit->addAction(actionAddUser);
    menuEdit->addAction(actionDeleteUser);
    menuFile->addAction(actionExit);
    menu->addMenu(menuFile);
    menu->addMenu(menuEdit);
    setMenuBar(menu);

    layout->addWidget(table);

    connect(actionExit, &QAction::triggered, this, &userManageWindow::close);

    connect(actionAddUser, &QAction::triggered, this, [this, c]() {
        // const auto addUserDlg = new addUserDialog(this, c);
        // addUserDlg->show();

        displayUsers();
    });

    connect(actionDeleteUser, &QAction::triggered, this, [this, c]() {
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
                c->deleteStudent(users[row].getEmail());
            } catch (const std::exception &e) {
                QMessageBox::warning(this, "Error", e.what());
            }
        }
        displayUsers();
    });

    connect(table, &QTableWidget::cellChanged, this, &userManageWindow::onCellChanged);

    displayUsers();
}

userManageWindow::~userManageWindow() {

}

void userManageWindow::displayUsers() {
    updatingTable = true;
    users = c->getUsers();
    table->clearContents();
    table->setRowCount(users.size());

    for (int i = 0; i < users.size(); ++i) {
        user& u = users[i];
        table->setItem(i, 0, new QTableWidgetItem(u.getUsername()));
        table->setItem(i, 1, new QTableWidgetItem(u.getEmail()));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(u.getTypeId())));
    }
    updatingTable = false;
}

void userManageWindow::onCellChanged(int row, int column) {
    if (updatingTable) return;

    QString username = table->item(row, 0)->text();
    QString email = table->item(row, 1)->text();
    QString typeId = table->item(row, 2)->text();

    try {
        c->modifyUser(users[row].getEmail(), email, username, typeId);
    } catch (const std::exception& e) {
        revertRow(row);
        QMessageBox::warning(this, "Error", e.what());
    }
}

void userManageWindow::revertRow(int row) {
    updatingTable = true;

    user &u = users[row];
    table->item(row, 0)->setText(u.getUsername());
    table->item(row, 1)->setText(u.getEmail());
    table->item(row, 2)->setText(QString::number(u.getTypeId()));

    updatingTable = false;
}

#include "moc_userManageWindow.cpp"
