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
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <QRegularExpression>

class utils {
public:
    static void checkUsernameFormat(const std::string& name);
    static void checkPasswordFormat(const std::string& password);
    static void checkEmailFormat(const std::string& email);
    static void checkFormat(const std::string& name, const std::string& email, const std::string& password);
    static void checkFormat(const std::string& name, const std::string& password);
    static std::string md5(const std::string& src);
    static void checkUserPermission(int type_id);
    static void checkGenderFormat(const std::string& gender);

    static void checkStudentNameFormat(const std::string& name);
    static void checkStudentNumberFormat(const std::string& number);
    static nlohmann::json loadConfig(const std::string& path);
};



#endif //UTILS_H
