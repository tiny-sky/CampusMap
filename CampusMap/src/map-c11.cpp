#include "../include/map-c11.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

void map::CreateMapFromFile() {

    std::ifstream input;
    int length;
    std::string loc1, loc2;

    input.open("../information/SchoolMap.txt");
    if (!input.is_open()) {
        std::cout << "init SchoolMap failed..." << std::endl;
        return;
    }

    input >> numVertexes >> numEdges;
    for (int i = 0; i < numVertexes; i++) {
        Map[i].setname(input);
    }

    for (int i = 0; i < numEdges; i++) {
        input >> loc1 >> loc2 >> length;
        if (addEdges(loc1, loc2, length) < 0) {
            std::cout << "addEdges failed..." << std::endl;
            return;
        }
    }
}

int map::addEdges(std::string loc1, std::string loc2, int length) {
    int index1 = findVertexNum(loc1);
    int index2 = findVertexNum(loc2);
    if (index1 < 0 || index2 < 0) {
        std::cout << "The location was not found " << std::endl;
        return -1;
    }

    Map[index1].addEdges(EdgeNode(index2, length));
    Map[index2].addEdges(EdgeNode(index1, length));
}

int map::findVertexNum(const std::string &str) const {
    auto result = std::find_if(Map.begin(), Map.end(), [&str](const std::string &s) { return s == str; });

    if (result != Map.end()) {
        return std::distance(Map.begin(), result);
    }
    return -1;
}