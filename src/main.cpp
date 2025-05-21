#include "mainWindow.h"
#include "loginDialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto* c = new controller("localhost", "login", "root", "041109");

    while (true) {
        loginDialog loginDlg(nullptr, c);
        if (loginDlg.exec() != QDialog::Accepted) {
            break;
        }

        auto* e = new mainWindow(nullptr, c);
        e->resize(800, 600);

        bool logoutRequested = false;

        QObject::connect(e, &mainWindow::logoutRequested, [&]() {
            logoutRequested = true;
        });

        e->show();

        a.exec();

        delete e;

        if (!logoutRequested) {
            break;
        }
    }

    delete c;

    return 0;
}
