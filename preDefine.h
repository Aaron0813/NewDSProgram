//
// Created by Aaron on 2016/11/14.
//

#ifndef NEWDSPROGRAM_PREDEFINE_H
#define NEWDSPROGRAM_PREDEFINE_H

#include <string>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

#define INFINITY 32767
#define MAX_VERTEX_NUM 30

//边定义，其中边中的link是为邻接链表做准备
struct Edge {

    //边的目的地--存的是点在数组中的位置
    int dest;
    //边的长度---即两点之间的距离
    int distance;
    //景点之间需要的时间
    int time_consume;
    //链表存储其他边
    Edge *link;

    //默认两点之间的不可达
    Edge() : distance(INFINITY), link(NULL) {}

    Edge(int d, int dis, int t, Edge *edge) : dest(d), distance(dis), time_consume(t), link(edge) {}

    Edge(int d, int dis, int t) : dest(d), distance(dis), time_consume(t), link(NULL) {}

    int operator!=(Edge &E) const { return dest != E.dest; }
};

//顶点定义
struct Vertex {

    string name;
    string description;
    int popular_degree;
    //0表示没有，1表示有
    int is_toilet;
    int is_rest;
    //点持有边的指针，这样可以创建邻接链表
    Edge *adj;
};

struct Graph {
    //节点的数量
    int num_vertices;
    //边的数量
    int num_edges;
    //图的邻接链表
    Vertex *node_table;
    //图的邻接矩阵
    double **adj_matrix;

    Graph(int sz) {
        if (sz != 0 && sz < MAX_VERTEX_NUM) {
            num_vertices = sz;
            num_edges = 0;
            node_table = new Vertex[num_vertices];
        } else
            cout << "初始化错误，节点数过大" << endl;
//        cout << "Initial Ok" << node_table[0].name << endl;
    }
//    ~Graph();
};

//最小生成树边结点的结构体定义
struct MSTEdgeNode {
    int head, tail;  //生成树各边的两个顶点
    int cost;       //生成树各边的代价
};

//辅助排序算法的结构体
struct SortNode {
    int value;
    string name;
};

//展示菜单目录
void ShowMenu();

//加载图的信息
void LoadGraph(Graph &graph);

//根据顶点的值找到其位置
int GetVertexPos(Graph &graph, string &name);

//输出一个邻接矩阵
void OutputAdjMatrix(Graph &graph);

//输出导游路线图
void CreateTourSortGraph(Graph &graph, Graph &tour_graph);

//深度优先遍历算法-递归的入口函数
string *DFSTraverse(Graph &graph);

//深度优先遍历算法--递归
void DFS(Graph &graph, int v, int visited[], string *vertex, int &num);

//获取节点v的第一个邻接顶点
int GetFirstNeighbor(Graph &graph, int v);

//获取节点v排在w后面的下一个邻接顶点
int GetNextNeighbor(Graph &graph, int v, int w);

//判断要查的这两个顶点之间是否有直接相连的边
bool IsEdge(Graph graph, string v1, string v2);

//查找一个图中的所有节点的入度数
void FindInDegree(Graph graph, int indegree[]);

//根据深度优先遍历的结果创建一个图--暂时不写
void CreateTourGraph(Graph &graph, Graph &tour_graph, string tour_map[]);

//查找一张图中是否有回路
void FindLoop(Graph &graph);

//求两个景点之间的最短路径及其距离
void MiniDistance(Graph &graph);

//具体计算顶点v与w之间的最短路径及距离的算法---DIJKSTRA
void Dijkstra(Graph &graph, int v, int w);

//生成最小生成树的算法
void MiniSpanTree(Graph &graph, string u);

//使用Prim生成最小生成树
void Prim(Graph &graph, int v);

//排序功能的主函数入口
void Sort(Graph &graph);

//根据欢迎度排序
void SortByPopularDegree(Graph &graph);

//根据岔路数排序
void SortByForks(Graph &graph);

//冒泡排序
void BubbleSort(SortNode sortNode[], int size);

//快速排序
void QuickSort(SortNode sortNode[], int left, int right);

//快速排序的辅助函数
int Partition(SortNode sortNode[], int left, int right);

//交换两个二维数组
//void Swap(int a[1][2], int b[1][2]);
void Swap(SortNode &a, SortNode &b);
//归并排序
void MergeSort(int popular_degree[][2], int size);

//查找的主函数---输入一个字符串，使用KMP分别遍历景点的名称以及景点的描述
void Search(Graph &graph);

//使用KMP算法进行查找关键字的查找
int KMPSearch(char target[], char pattern[]);

//计算模式串前缀的函数
void CptPfFunc(char pattern[], int prefix[]);




////判断图是否为空
//int GraphEmpty(Graph & graph)const {return graph.num_vertices==0;}
////判断图的节点数是否已经达到最大上限
//int GraphFull(Graph & graph)const { return graph.num_vertices==MAX_VERTEX_NUM;}
////返回指定节点的名称
//string GetNodeName(Graph & graph,int i)
//{return i>=0&&i<graph.num_vertices?graph.node_table[i].name:NULL;}



#endif //NEWDSPROGRAM_PREDEFINE_H
