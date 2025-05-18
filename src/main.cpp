#include "loginDialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *e = new loginDialog();
    e->show();
    return QApplication::exec();
}