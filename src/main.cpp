#include "mainWindow.h"
#include "loginDialog.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    while (true) {
        bool logoutRequested = false;

        if (QSqlDatabase::contains("qt_sql_default_connection")) {
            QSqlDatabase::removeDatabase("qt_sql_default_connection");
        }

        auto config = utils::loadConfig("config/config.json");
        auto* c = new controller(
            QString::fromStdString(config["database_hostname"].get<std::string>()),
            QString::fromStdString(config["database_name"].get<std::string>()),
            QString::fromStdString(config["database_username"].get<std::string>()),
            QString::fromStdString(config["database_password"].get<std::string>()),
            config["database_port"].get<int>()
        );

        auto *loginDlg = new loginDialog(nullptr, c);
        if (loginDlg->exec() != QDialog::Accepted) {
            break;
        }

        auto* e = new mainWindow(nullptr, c);
        e->resize(800, 600);

        QObject::connect(e, &mainWindow::logoutRequested, [&]() {
            logoutRequested = true;
        });

        e->show();

        QApplication::exec();

        delete e;
        delete c;
        delete loginDlg;

        if (!logoutRequested) {
            break;
        }
    }

    return 0;
}
