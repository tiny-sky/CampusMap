#include "../include/user.h"
#include "../include/common.h"
#include "../include/map.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

extern map Mymap;
extern user account;

void user::FindPath(int flag) const {
    std::string loc1, loc2;
    int start, end, minDist = std::numeric_limits<int>::max();
    std::vector<bool> visited(map::MAXVER, false);
    std::vector<int> path;
    std::vector<int> shortpath;

    std::cout << "请输入路径的起点:";
    std::cin >> loc1;
    std::cout << "请输入路径的终点:";
    std::cin >> loc2;

    start = Mymap.findVertexNum(loc1);
    end = Mymap.findVertexNum(loc1);

    if (start < 0 || end < 0) {
        std::cout << "The location was not found " << std::endl;
        return;
    }

    if (flag == 0)
        Mymap.FindAllByDFS(start, end, visited, path);
    else if (flag == 1) {
        Mymap.FindShortByDFS(start, end, visited, path, shortpath);

        if (shortpath.empty()) {
            std::cout << "No shortest path found..." << std::endl;
            return;
        }

        std::cout << "The path that least passes through a node is :";
        for (const auto &index : shortpath)
            std::cout << Mymap.getNameByIndex(index) << " --> ";
        std::cout << Mymap.getNameByIndex(end) << std::endl;
    } else if (flag == 2) {
        Mymap.FindBestByDFS(start, end, visited, path, minDist, 0);

        if (shortpath.empty()) {
            std::cout << "No shortest path found..." << std::endl;
            return;
        }

        std::cout << "The shortest path (minimum distance) is:\n";
        for (int vertex : path) {
            std::cout << Mymap.getNameByIndex(vertex) << " --> ";
        }
        std::cout << Mymap.getNameByIndex(end) << std::endl;
        std::cout << "The shortest path length is: " << minDist << std::endl;
    }
}

int user::user_login() const {
    CLEAR;

    std::string account, passwd, RPasswd;
    std::cout << "请输入帐号:";
    std::cin >> account;
    std::cout << "请输入密码: ";
    system("stty -echo");
    std::cin >> passwd;
    system("stty echo");

    std::string filename = DIR_UESR + account;
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cout << "没有该用户: " << account << " ...\n";
        Mystd::exit();
        return;
    }

    file >> RPasswd;
    file.close();
    if (passwd == RPasswd) {
        std::cout << "\n登录成功...\n";
        Mystd::exit();
        return 0;
    }
    std::cout << "密码错误..." << std::endl;
    Mystd::exit();
    return -1;
}

void user::menu_user() const {
    int choice;

    do {
        CLEAR;
        std::cout << "============================================" << std::endl;
        std::cout << "=========       校园导航系统        ==========" << std::endl;
        std::cout << "============================================" << std::endl;
        std::cout << "======    1. 输出校园平面图              ======" << std::endl;
        std::cout << "======    2. 查询校园信息               ======" << std::endl;
        std::cout << "======    3. 查询两地间所有简单路径       ======" << std::endl;
        std::cout << "======    4. 查询两地间中转次数最少路径    ======" << std::endl;
        std::cout << "======    5. 查询两地间最佳访问路径       ======" << std::endl;
        std::cout << "======    6. 设计最佳布网方案            ======" << std::endl;
        std::cout << "======    0. 退出                      ======" << std::endl;
        std::cout << "============================================" << std::endl;
        std::cout << "请选择你要查询的信息编号：\n";

        Mystd::getchar(choice);

        switch (choice) {
            case 0:
                return;
            case 1:
                system("feh ../infomation/map.jpg");
                Mystd::exit();
                break;
            //case 2:
            case 3:
                FindPath(0);
                Mystd::exit();
                break;
            case 4:
                FindPath(1);
                Mystd::exit();
                break;
            case 5:
                FindPath(2);
                Mystd::exit();
                break;
        }
    } while (true);
}