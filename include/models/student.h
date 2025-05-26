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
    QString department;
    QString classname;
    QString gender;

public:
    student(const QString&, const QDate&, const QString&, const QString&, const QString&, const QString&, const QString&);
    QString getName();
    QString getNumber();
    QString getAddress();
    QDate getBirthday() const;
    QString getClassname() const;
    QString getDepartment() const;
    QString getGender() const;

    void setName(const QString&);
    void setNumber(const QString&);
    void setAddress(const QString&);
    void setBirthday(const QDate&);
    void setClassname(const QString&);
    void setDepartment(const QString&);
    void setGender(const QString&);
};



#endif //STUDENT_H
