#include "../include/map.h"

#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

void map::CreateMapFromFile() {

    std::ifstream input;
    int length;
    std::string loc1, loc2;

    input.open("../information/SchoolMap.txt");
    if (!input.is_open()) {
        cout << "init SchoolMap failed..." << endl;
        return;
    }

    input >> numVertexes >> numEdges;
    for (int i = 0; i < numVertexes; i++) {
        input >> Map[i].name;
        Map[i].FirstEdge = nullptr;
    }

    for (int i = 0; i < numEdges; i++) {
        input >> loc1 >> loc2 >> length;
        if (addEdges(loc1, loc2, length) < 0) {
            cout << "addEdges failed..." << endl;
            return;
        }
    }
}

int map::findVertexNum(const std::string &str) const {
    for (int i = 0; i < numVertexes; i++) {
        if (str == Map[i].name) {
            return i;
        }
    }
    return -1;
}

void map::addPlace() {
    int n, num, length;
    std::string loc1, loc2;

    cout << "请输入要添加的地点个数: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        VertexNode *node = new VertexNode;
        cout << "第" << i + 1 << "个地点信息:\n";
        cout << "名称 : ";
        cin >> loc1;
        node->name = loc1;
        node->FirstEdge = nullptr;

        Map.push_back(*node);
        numVertexes++;

        cout << "请输入相邻的地点个数 : ";
        cin >> num;
        for (int j = 0; j < num; j++) {
            cout << "请输入第" << j + 1 << "个相邻的地点名称 : ";
            cin >> loc2;
            cout << "请输入该地点与添加地址之间的距离 : ";
            cin >> length;
            if (addEdges(loc1, loc2, length) < 0)
                return;
            numEdges++;
        }
    }
}

int map::addEdges(std::string loc1, std::string loc2, int length) {

    int index1 = findVertexNum(loc1);
    int index2 = findVertexNum(loc2);
    if (index1 < 0 || index2 < 0) {
        cout << "The location was not found " << endl;
        return -1;
    }

    EdgeNode *node = new EdgeNode;
    node->adjvex = index2;
    node->length = length;
    node->next = Map[index1].FirstEdge;
    Map[index1].FirstEdge = node;

    node = new EdgeNode;
    node->adjvex = index1;
    node->length = length;
    node->next = Map[index2].FirstEdge;
    Map[index2].FirstEdge = node;
}

void map::FindAllByDFS(const int start, const int end, std::vector<bool> visited, std::vector<int> path) const {
    EdgeNode *p = Map[start].FirstEdge;
    visited[start] = true;
    path.push_back(start);

    while (p) {
        if (p->adjvex != end && !visited[p->adjvex])
            FindAllByDFS(p->adjvex, end, visited, path);
        else if (p->adjvex == end) {
            std::cout << "The path is :";
            for (const auto &index : path)
                std::cout << Mymap.getNameByIndex(index) << " --> ";
            std::cout << Map[end].name << std::endl;
        }
        p = p->next;
    }
    visited[start] = false;
    path.pop_back();
}

void map::FindShortByDFS(const int start, const int end, std::vector<bool> visited, std::vector<int> path, std::vector<int> &shortestPath) const {
    EdgeNode *p = Map[start].FirstEdge;
    p = Map[start].FirstEdge;
    visited[start] = true;
    path.push_back(start);

    while (p) {
        if (p->adjvex != end && !visited[p->adjvex])
            FindShortByDFS(p->adjvex, end, visited, path, shortestPath);
        else if (p->adjvex == end) {
            if (shortestPath.empty() || path.size() < shortestPath.size())
                shortestPath = path;
        }
        p = p->next;
    }
    visited[start] = false;
    path.pop_back();
}

void map::FindBestByDFS(const int start, const int end, std::vector<bool> &visited, std::vector<int> &path, int &minDist, int currentDist) const {
    visited[start] = true;
    path.push_back(start);

    if (start == end) {
        if (minDist > currentDist) {
            minDist = currentDist;
        }
    } else {
        for (EdgeNode *p = Map[start].FirstEdge; p; p = p->next) {
            if (!visited[p->adjvex]) {
                FindBestByDFS(p->adjvex, end, visited, path, minDist, currentDist + p->length);
            }
        }
    }

    visited[start] = false;
    path.pop_back();
}