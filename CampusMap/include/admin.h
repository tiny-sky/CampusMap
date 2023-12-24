#ifndef ADMIN_H_
#define ADMIN_H_

#include <string>
const std::string DIR_ADMINISTER = "../infomation/administer/";

class admin {
private:
    std::string account;// name of the admin
    std::string passwd;

public:
    auto administer_login() -> int;// admin login
    void menu_administer(); // admin menu
};

#endif