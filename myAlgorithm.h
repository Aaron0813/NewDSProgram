//
// Created by Aaron on 2016/11/23.
//

#ifndef NEWDSPROGRAM_MYALGORITHM_H
#define NEWDSPROGRAM_MYALGORITHM_H

#include "graph.h"
#include <string>

using namespace std;
//辅助排序算法的结构体
struct SortNode {
    int value;
    string name;
};

//查找一个图中的所有节点的入度数
void FindInDegree(Graph graph, int indegree[]);

//查找一张图中是否有回路
void FindLoop(Graph &graph);


//具体计算顶点v与w之间的最短路径及距离的算法---DIJKSTRA
void Dijkstra(Graph &graph, int v, int w);

//深度优先遍历算法-递归的入口函数---找了半天错误，居然发现是因为routes.txt文件多了一个空行。。。
string *DFSTraverse(Graph &graph);

//深度优先遍历算法--递归
void DFS(Graph &graph, int v, int visited[], string *vertex, int &num);

//生成最小生成树的算法
void MiniSpanTree(Graph &graph, string u);

//使用Prim生成最小生成树
void Prim(Graph &graph, int v);

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

//使用KMP算法进行查找关键字的查找
int KMPSearch(char target[], char pattern[]);

//计算模式串前缀的函数
void CptPfFunc(char pattern[], int prefix[]);

//新的KMP前缀创建
void get_next(char *t, int next[]);

//KMP主算法
int KMP(char *s, char *t);

#endif //NEWDSPROGRAM_MYALGORITHM_H
