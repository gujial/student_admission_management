//
// Created by gujial on 25-5-19.
//

#include "aboutDialog.h"

aboutDialog::aboutDialog(QWidget *parent) {
    setWindowTitle("About");
    setWindowIcon(QIcon(":/assets/images/icon.png"));

    nameLabel = new QLabel("Student Admission Management");
    versionLabel = new QLabel("1.0.0");
    authorLabel = new QLabel("软件工程2305班 古佳乐 8008123201");
    iconLabel = new QLabel(this);
    iconLabel->setPixmap(QPixmap(":/assets/images/icon.png").scaled(80, 80, Qt::KeepAspectRatio));
    layout = new QGridLayout(this);
    closeButton = new QPushButton("close");

    layout->addWidget(nameLabel, 0, 1);
    layout->addWidget(versionLabel, 1, 1);
    layout->addWidget(authorLabel, 2, 1);
    layout->addWidget(iconLabel, 0, 2);
    layout->addWidget(closeButton, 3, 2);
    setLayout(layout);

    connect(closeButton, &QPushButton::clicked, this, &aboutDialog::close);
}

aboutDialog::~aboutDialog() {

}

#include "moc_aboutDialog.cpp"
