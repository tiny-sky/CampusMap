#ifndef MAP_H_
#define MAP_H_

#include <list>
#include <memory>
#include <string>
#include <vector>

class EdgeNode {
private:
    /**Coordinate number*/
    int adjvex;
    /**distance*/
    int length;

public:
    /**
     * @brief Initialize EdgeNode.
    */
    EdgeNode(int adjvex_ = 0, int length_ = 0) : adjvex(adjvex_), length(length_){};

    /** @return the adjvex member of the EdgeNode structure*/
    auto getadjvex() -> const int & { return this->adjvex; }

    /** @return the length member of the EdgeNode structure*/
    auto getlength() -> const int & { return this->length; }

    ~EdgeNode() = default;
};

class VertexNode : public EdgeNode {
private:
    /**address name*/
    std::string name;
    /**Head pointer of edge node*/
    std::list<EdgeNode> FirstEdge;

public:
    /**
     * @brief Initialize VertexNode.
    */
    VertexNode() = default;
    VertexNode(std::string name_) : name(name_) {}

    /** @return the name member of the VertexNode structure*/
    auto getname() -> const std::string & { return this->name; }

    void setname(std::string &name_) { this->name = name_; }
    void setname(std::istream &is) { is >> this->name; }

    void addEdges(EdgeNode node) { FirstEdge.push_back(node); }

    ~VertexNode() = default;
};

class map : public VertexNode {
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
    map() = default;
    map(int numVertexes_, int numEdges_) : numVertexes(numVertexes_), numEdges(numEdges_){};

    /**
    * @brief Destroys the map.
   */
    ~map() = default;

    /** Maximum number of vertices.*/
    static const int MAXVER = 30;

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
    auto map::getNameByIndex(int index) -> std::string { return Map[index].getname(); };

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
};

#endif