//
// Created by gujial on 25-5-7.
//

#include "utils.h"

void utils::checkUsernameFormat(const std::string &name) {
    char firstLetter = name.at(0);
    int firstLetterInt = firstLetter;
    if (name.length() < 6) {
        throw std::invalid_argument("Username must be more than 6 characters");
    }
    if (firstLetterInt < 65 || firstLetterInt > 122) {
        throw std::invalid_argument("First charactor of username must be letters");
    }
}

void utils::checkPasswordFormat(const std::string &password) {
    if (password.length() > 20) {
        throw std::invalid_argument("password is too long");
    }
    if (password.length() < 6) {
        throw std::invalid_argument("password is too short");
    }
}

void utils::checkEmailFormat(const std::string &email) {
    const std::regex pattern(R"((^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$))");
    if (std::regex_match(email, pattern)) {
        return;
    }
    throw std::invalid_argument("Email format not right");
}

void utils::checkFormat(const std::string &name, const std::string &email, const std::string &password) {
    checkUsernameFormat(name);
    checkPasswordFormat(password);
    checkEmailFormat(email);
}

void utils::checkFormat(const std::string &name, const std::string &password) {
    checkUsernameFormat(name);
    checkPasswordFormat(password);
}

std::string utils::md5(const std::string& src) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx)
        throw std::runtime_error("Failed to create EVP_MD_CTX");

    unsigned char md[MD5_DIGEST_LENGTH] = {0};

    if (EVP_DigestInit_ex(ctx, EVP_md5(), nullptr) != 1 ||
        EVP_DigestUpdate(ctx, src.data(), src.size()) != 1 ||
        EVP_DigestFinal_ex(ctx, md, nullptr) != 1) {
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("MD5 calculation failed");
        }

    EVP_MD_CTX_free(ctx);

    std::ostringstream oss;
    for (unsigned char i : md) {
        oss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }

    return oss.str();
}

void utils::checkUserPermission(int type_id) {
    if (type_id == 0) {
        return;
    }
    throw std::runtime_error("Permission denied");
}

void utils::checkStudentNameFormat(const std::string &name) {
    char firstLetter = name.at(0);
    int firstLetterInt = firstLetter;
    if (firstLetterInt < 65 || firstLetterInt > 122) {
        throw std::invalid_argument("First charactor of name must be letters");
    }
}

void utils::checkStudentNumberFormat(const std::string &number) {
    if (number.length() > 20) {
        throw std::invalid_argument("student number is too long");
    }
    if (number.length() < 6) {
        throw std::invalid_argument("student number is too short");
    }
}

nlohmann::json utils::loadConfig(const std::string &path) {
    namespace fs = std::filesystem;

    if (!fs::exists(path)) {
        std::cout << "No config file. Creating a new one..." << std::endl;
        nlohmann::json defaultConfig = {
            {"database_hostname", "localhost"},
            {"database_port", 3306},
            {"database_name", "login"},
            {"database_username", "root"},
            {"database_password", "041109"}
          };

        fs::create_directories(fs::path(path).parent_path());
        std::ofstream out(path);
        out << defaultConfig.dump(4);
        out.close();
        return defaultConfig;
    }

    std::ifstream file(path);
    nlohmann::json config;
    file >> config;
    return config;
}
