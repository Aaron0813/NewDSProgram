//
// Created by Aaron on 2016/11/14.
//

#ifndef NEWDSPROGRAM_PREDEFINE_H
#define NEWDSPROGRAM_PREDEFINE_H

#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include "myAlgorithm.h"
#include "graph.h"
#include "park.h"

using namespace std;

#define INFINITY 32767
#define MAX_VERTEX_NUM 30


//展示菜单目录
void ShowMenu(Graph &graph);

//加载图的信息
void LoadGraph(Graph &graph, string vertex_txt, string route_txt);

//输出存储之后的节点信息
void OutputLoadNodeInfo(Graph &graph, int n);

//输出存储之后的路径信息
void OutputLoadRouteInfo(Graph &graph);

//求两个景点之间的最短路径及其距离
void MiniDistance(Graph &graph);

//输出一个邻接矩阵
void OutputAdjMatrix(Graph &graph);

//输出排序结果的函数
void OutputSortResult(Graph &graph, SortNode sortNodes[]);

//创建导游路线图
string *CreateTourSortGraph(Graph &graph, int &count);

//输出导游路线图
void OutputTourGraph(string tour_map[], int n);

//根据深度优先遍历的结果创建一个图--暂时不写
void CreateTourGraph(Graph &graph, Graph &tour_graph, string tour_map[]);

//排序功能的主函数入口
void Sort(Graph &graph);

//根据欢迎度排序
void SortByPopularDegree(Graph &graph);

//根据岔路数排序
void SortByForks(Graph &graph);

//查找的主函数---输入一个字符串，使用KMP分别遍历景点的名称以及景点的描述
void Search(Graph &graph);

//停车场程序入口函数
void Park();


#endif //NEWDSPROGRAM_PREDEFINE_H
