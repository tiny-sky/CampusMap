//===----------------------------------------------------------------------===//
//
//                         School Map
//
// map.h
//
// Identification: src/include/map.h
//
// Copyright (c) 2023,yuan xiao tian
//
//===----------------------------------------------------------------------===//

#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <vector>

//#define MAXVER 20

struct EdgeNode {
    int adjvex;// 坐标编号
    int length;// 距离
    struct EdgeNode *next;
};

struct VertexNode {
    std::string name;// 名称
    EdgeNode *FirstEdge;
};

class map {
private:
    /** adjacency list. */
    std::vector<VertexNode> Map;
    /** Number of nodes*/
    int numVertexes;
    /** Number of sides*/
    int numEdges;

public:
    /**
     * @brief Initialize map.
     * @param numVertexes represents the number of nodes.
     * @param numEdges the number of edges.
    */
    map() : numVertexes(0), numEdges(0){};

    /**
    * @brief Destroys the map.
   */
    ~map() = default;

    /** @brief The user enters an address and adds the address to the map class.*/
    void addPlace();

    /** @brief For the given two addresses, create the given critical matrix of the weighted undirected graph. */
    auto addEdges(std::string loc1, std::string loc2, int length) -> int;

    /** @brief Read the data and build an adjacency list with a weighted undirected graph to describe the campus map. */
    void CreateMapFromFile();

    /**
     * @param index is the following table of adjacency list arrays
     * @brief Get the corresponding name through the passed in parameters
    */
    auto map::getNameByIndex(int index) -> std::string { return Map[index].name; };

    /** @return the following table of adjacency lists found by name*/

    auto findVertexNum(const std::string &str) const -> int;

    //void print() const;

    /** @brief Use DFS algorithm to find all routes corresponding to the adjacency list*/
    void FindAllByDFS(const int start, const int end, std::vector<bool> visited, std::vector<int> path) const;

    /** @brief Use the DFS algorithm to find the route with the fewest nodes in the corresponding adjacency list.*/
    void FindShortByDFS(const int start, const int end, std::vector<bool> visited, std::vector<int> path, std::vector<int> &shortestPath) const;

    /** 
     * @brief Find the shortest path corresponding to the adjacency list through the DFS algorithm
     * @param minDist is used to record the length of the shortest path that has been found so far. It represents the sum of the weights of the path from the starting point to the current node.
    */
    void FindBestByDFS(const int start, const int end, std::vector<bool> &visited, std::vector<int> &path, int &minDist, int currentDist) const;

    static const int MAXVER = 30;// 适当修改最大顶点数
};

map Mymap;// 全局地图
#endif