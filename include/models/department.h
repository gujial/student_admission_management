//
// Created by gujial on 25-6-5.
//

#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QApplication>
#include <QString>

class department {
private:
    QString name;
    QString number;
public:
    department(const QString &name, const QString &number);
    QString getName() const;
    QString getNumber() const;
    void setName(const QString &name);
    void setNumber(const QString &number);
};

#endif //DEPARTMENT_H
