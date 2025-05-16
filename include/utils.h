//
// Created by gujial on 25-5-7.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <regex>
#include <openssl/md5.h>
#include <openssl/evp.h>
#include <iomanip>

class utils {
public:
    static void checkUsernameFormat(const std::string& name);
    static void checkPasswordFormat(const std::string& password);
    static void checkEmailFormat(const std::string& email);
    static void checkFormat(const std::string& name, const std::string& email, const std::string& password);
    static void checkFormat(const std::string& name, const std::string& password);
    static std::string md5(const std::string& src);
    static void checkUserPermission(int type_id);

    static void checkStudentNameFormat(const std::string& name);
};



#endif //UTILS_H
