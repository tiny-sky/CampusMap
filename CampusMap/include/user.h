#ifndef USER_H_
#define USER_H_
#include <string>
#include <vector>

const std::string DIR_UESR = "../infomation/user/";

class user {
private:
    std::string name;// name of user
public:
    //void Register() const;// 注册 user
    //int info() const;     // address infomation
    auto user_login() const -> int;
    void menu_user() const;
    void FindPath(int flag) const;// 所有简单路径
};

#endif