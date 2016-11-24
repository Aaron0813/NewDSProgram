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


//չʾ�˵�Ŀ¼
void ShowMenu(Graph &graph);

//����ͼ����Ϣ
void LoadGraph(Graph &graph, string vertex_txt, string route_txt);

//����洢֮��Ľڵ���Ϣ
void OutputLoadNodeInfo(Graph &graph, int n);

//����洢֮���·����Ϣ
void OutputLoadRouteInfo(Graph &graph);

//����������֮������·���������
void MiniDistance(Graph &graph);

//���һ���ڽӾ���
void OutputAdjMatrix(Graph &graph);

//����������ĺ���
void OutputSortResult(Graph &graph, SortNode sortNodes[]);

//��������·��ͼ
string *CreateTourSortGraph(Graph &graph, int &count);

//�������·��ͼ
void OutputTourGraph(string tour_map[], int n);

//����������ȱ����Ľ������һ��ͼ--��ʱ��д
void CreateTourGraph(Graph &graph, Graph &tour_graph, string tour_map[]);

//�����ܵ����������
void Sort(Graph &graph);

//���ݻ�ӭ������
void SortByPopularDegree(Graph &graph);

//���ݲ�·������
void SortByForks(Graph &graph);

//���ҵ�������---����һ���ַ�����ʹ��KMP�ֱ��������������Լ����������
void Search(Graph &graph);

//ͣ����������ں���
void Park();


#endif //NEWDSPROGRAM_PREDEFINE_H
