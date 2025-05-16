//
// Created by gujial on 25-5-13.
//

#ifndef USER_H
#define USER_H
#include <string>
#include <QString>
#include "utils.h"

class user {
    QString username;
    QString password;
    QString email;
    int type_id;
public:
    user(const QString& username, const QString& password, const QString& email, int type_id);
    QString getUsername();
    QString getPassword();
    QString getEmail();
    int getTypeId() const;
    void setUsername(const QString& username);
    void setPassword(const QString& password);
    void setEmail(const QString& email);
    void setTypeId(int type_id);
};



#endif //USER_H
