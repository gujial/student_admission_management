#include "mainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *e = new mainWindow();
    e->resize(800, 600);
    e->show();
    return QApplication::exec();
}