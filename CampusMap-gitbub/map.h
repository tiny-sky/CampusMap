#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;

#define CLEAR system("clear");
#define WAIT {cin.get(); cin.get();};
const string DIR_ACCOUNT = "user/";
const string DIR_ADMINISTER = "administer/";
const int MAXVEX = 20;

struct EdgeNode {
    int adjvex;  //标号
    int length;  //距离
    struct EdgeNode *next;
};

struct VertexNode {
    string name;  //名称
    EdgeNode *FirstEdge;
};

class SchoolMap {
private:
    vector<VertexNode> Map;  //邻接表
    int numVertexes;  //结点个数
    int numEdges;  //边个数
public:
    SchoolMap() {numVertexes = numEdges = 0;}; //map
    void menu() const;  //user登陆菜单
    void CreateMapFromFile();  //创建邻接表 map
    int findVertexNum(const string & str) const;  //寻找结点下标 map
    int info() const; //user
    void addPlace(); //admin
    void allPath() const;  //所有简单路径 user
    void dfs(const int start, const int end, vector<bool> visited, vector<int> path) const; //user
    void shortestPath() const;  //中转次数最少路径 //user
    void shortestPathDfs(const int start, const int end, vector<bool> visited, vector<int> & path, vector<int> & tmp, int & max, int len) const; //user
    void bestPath() const;  //最短路径 user
    void bestPathDfs(const int start, const int end, vector<bool> visited, vector<int> & path, vector<int> tmp, int & max, int len) const; //user
    void bestMap() const;  //最佳布网方案 //user
    void print() const; // map
    void menu_login();  //基础面板
    void login() const; //登陆 user
    void Register() const; //注册 user
    void administer_login(); //管理员 admin
    void menu_administer(); //管理员面板 admin
};