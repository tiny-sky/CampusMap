#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <limits>

#define CLEAR system("clear");

namespace Mystd {

inline void exit(void) {
    std::cout << "\nPress any key to continue..." << std::endl;
    while (std::getchar() != '\n')
        ;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline void getchar(int &choice) {
    std::string line;

    while (true) {
        std::cin >> std::ws >> line;
        if (std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (line.length() == 1) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\033[F\033[K";// 返回上一行并清空该行
    }
    choice = line.c_str()[0];
    std::cout << "\033[F\033[K";// 返回上一行并清空该行
}
}// namespace Mystd

#endif