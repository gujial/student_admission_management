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
    actionModifyPassword = new QAction("Modify password");
    table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList() << "Username" << "Email" << "Type ID");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    actionExit->setShortcut(QKeySequence(QKeySequence("Ctrl+Q")));
    actionAddUser->setShortcut(QKeySequence("Ctrl+N"));
    actionDeleteUser->setShortcut(QKeySequence(Qt::Key_Delete));
    actionModifyPassword->setShortcut(QKeySequence("Ctrl+M"));

    central = new QWidget(this);
    layout = new QGridLayout(central);
    central->setLayout(layout);
    setCentralWidget(central);

    menuEdit->addAction(actionAddUser);
    menuEdit->addAction(actionDeleteUser);
    menuEdit->addAction(actionModifyPassword);
    menuFile->addAction(actionExit);
    menu->addMenu(menuFile);
    menu->addMenu(menuEdit);
    setMenuBar(menu);

    layout->addWidget(table);

    connect(actionExit, &QAction::triggered, this, &userManageWindow::close);

    connect(actionAddUser, &QAction::triggered, this, [this, c]() {
        const auto addUserDlg = new addUserDialog(this, c);
        addUserDlg->resize(400, 300);
        addUserDlg->exec();
        displayUsers();
    });

    connect(actionDeleteUser, &QAction::triggered, this, [this, c]() {
        QList<QTableWidgetItem *> selectedItems = table->selectedItems();
        QSet<int> selectedRows;

        if (selectedItems.isEmpty()) {
            QMessageBox::warning(this, "Error", "No user selected");
            return;
        }

        for (QTableWidgetItem *item : selectedItems) {
            selectedRows.insert(item->row());
        }

        for (const int row : selectedRows) {
            try {
                c->deleteUser(users[row].getEmail());
            } catch (const std::exception &e) {
                QMessageBox::warning(this, "Error", e.what());
            }
        }
        displayUsers();
    });

    connect(actionModifyPassword, &QAction::triggered, this, [this, c]() {
        QList<QTableWidgetItem *> selectedItems = table->selectedItems();

        if (selectedItems.isEmpty()) {
            QMessageBox::warning(this, "Error", "No user selected");
            return;
        }

        if (selectedItems.size() > 1) {
            QMessageBox::warning(this, "Error", "Too many users selected");
            return;
        }

        try {
            const auto modifyPasswordDlg = new modifyPasswordDialog(this, c, users[selectedItems[0]->row()].getEmail());
            modifyPasswordDlg->exec();
            displayUsers();
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", e.what());
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

        QComboBox* comboBox = getTypeComboBox(u.getTypeId());
        table->setCellWidget(i, 2, comboBox);

        connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int) {
            if (updatingTable) return;
            QString username = table->item(i, 0)->text();
            QString email = table->item(i, 1)->text();
            int newTypeId = comboBox->currentData().toInt();

            try {
                c->modifyUser(users[i].getEmail(), email, username, QString::number(newTypeId));
                users[i].setTypeId(newTypeId);
            } catch (const std::exception& e) {
                QMessageBox::warning(this, "Error", e.what());
                displayUsers();
            }
        });
    }
    updatingTable = false;
}

void userManageWindow::onCellChanged(int row, int column) {
    if (updatingTable) return;

    QString username = table->item(row, 0)->text();
    QString email = table->item(row, 1)->text();
    int typeId = users[row].getTypeId();

    try {
        c->modifyUser(users[row].getEmail(), email, username, QString::number(typeId));
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

    QComboBox* comboBox = qobject_cast<QComboBox*>(table->cellWidget(row, 2));
    if (comboBox) {
        comboBox->setCurrentIndex(comboBox->findData(u.getTypeId()));
    }

    updatingTable = false;
}

QComboBox *userManageWindow::getTypeComboBox(int currentTypeId) const {
    QComboBox *comboBox = new QComboBox();
    comboBox->addItem(c->getUserTypeName(0), 0);
    comboBox->addItem(c->getUserTypeName(1), 1);
    comboBox->setCurrentIndex(comboBox->findData(currentTypeId));
    return comboBox;
}

#include "moc_userManageWindow.cpp"
