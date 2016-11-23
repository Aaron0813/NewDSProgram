//
// Created by Aaron on 2016/11/14.
//

#ifndef NEWDSPROGRAM_PREDEFINE_H
#define NEWDSPROGRAM_PREDEFINE_H

#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include "graph.h"
using namespace std;

#define INFINITY 32767
#define MAX_VERTEX_NUM 30


//辅助排序算法的结构体
struct SortNode {
    int value;
    string name;
};

//展示菜单目录
void ShowMenu(Graph &graph);

//加载图的信息
void LoadGraph(Graph &graph);


//输出一个邻接矩阵
void OutputAdjMatrix(Graph &graph);


//输出导游路线图
void CreateTourSortGraph(Graph &graph);




//查找一个图中的所有节点的入度数
void FindInDegree(Graph graph, int indegree[]);

//根据深度优先遍历的结果创建一个图--暂时不写
void CreateTourGraph(Graph &graph, Graph &tour_graph, string tour_map[]);

//查找一张图中是否有回路
void FindLoop(Graph &graph);

//求两个景点之间的最短路径及其距离
void MiniDistance(Graph &graph);


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

//输出排序结果的函数
void OutputSortResult(Graph &graph, SortNode sortNodes[]);

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

//新的KMP前缀创建
void get_next(char *t, int next[]);

//KMP主算法
int KMP(char *s, char *t);



#endif //NEWDSPROGRAM_PREDEFINE_H
