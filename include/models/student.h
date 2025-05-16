//
// Created by gujial on 25-5-7.
//

#ifndef STUDENT_H
#define STUDENT_H
#include <QApplication>
#include <QString>
#include <QDate>

class student {
    QString name;
    QDate birthday;
    QString number;
    QString address;
public:
    student(const QString&, const QDate&, const QString&, const QString&);
    QString getName();
    QString getNumber();
    QString getAddress();
    QDate getBirthday() const;
    void setName(const QString&);
    void setNumber(const QString&);
    void setAddress(const QString&);
    void setBirthday(const QDate&);
};



#endif //STUDENT_H
