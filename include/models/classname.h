//
// Created by gujial on 25-6-5.
//

#ifndef CLASSNAME_H
#define CLASSNAME_H

#include <QApplication>
#include <QString>


class classname {
private:
    QString name;
    QString number;
    QString department;
public:
    classname(const QString &name, const QString &number, const QString &department);
    QString getName() const;
    QString getNumber() const;
    QString getDepartment() const;
    void setName(const QString &name);
    void setNumber(const QString &number);
    void setDepartment(const QString &department);
};

#endif //CLASSNAME_H
