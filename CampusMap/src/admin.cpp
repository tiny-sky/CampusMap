#include "../include/admin.h"
#include "../include/common.h"
#include "../include/map.h"

#include <fstream>
#include <iostream>
#include <string.h>

extern map Mymap;

int admin::administer_login() {
    CLEAR;

    std::string filename,RPasswd;
    std::cout << "请输入管理员帐号: ";
    std::cin >> account;
    std::cout << "请输入密码: ";
    system("stty -echo");
    std::cin >> passwd;
    system("stty echo");

    //文件存储太低效了，有时间了换成redis数据库
    filename = DIR_ADMINISTER + account;

    std::ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
        std::cout << "登录出错...\n";
        Mystd::exit();
        return;
    }
    fin >> RPasswd;
    fin.close();
    if (passwd == RPasswd) {
        std::cout << "\n登录成功...\n";
        Mystd::exit();
        return 0;
    }
    std::cout << "密码错误..." << std::endl;
    Mystd::exit();
    return -1;
}

void admin::menu_administer() {
    do {
        CLEAR
        std::cout << "\t1. 添加地点\n\n";
        std::cout << "\t2. 删除地点\n\n";
        std::cout << "\t0. 退出\n\n";

        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "输入错误...\n";
            Mystd::exit();
        }
        Mystd::getchar(choice);
        switch (choice) {
            case 0:
                return;
            case 1:
                Mymap.addPlace();
                break;
            // case 2: delPlace(); break;
            default:
                std::cout << "输入错误...\n";
        }
    } while (true);
}