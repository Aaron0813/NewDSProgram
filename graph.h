//
// Created by Aaron on 2016/11/21.
//

#ifndef NEWDSPROGRAM_GRAPH_H
#define NEWDSPROGRAM_GRAPH_H

#include <string>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

#define INFINITY 32767
#define MAX_VERTEX_NUM 30

//�߶��壬���б��е�link��Ϊ�ڽ�������׼��
struct Edge {

    //�ߵ�Ŀ�ĵ�--����ǵ��������е�λ��
    int dest;
    //�ߵĳ���---������֮��ľ���
    int distance;
    //����֮����Ҫ��ʱ��
    int time_consume;
    //����洢������
    Edge *link;

    //Ĭ������֮��Ĳ��ɴ�
    Edge() : distance(INFINITY), link(NULL) {}

    Edge(int d, int dis, int t, Edge *edge) : dest(d), distance(dis), time_consume(t), link(edge) {}

    Edge(int d, int dis, int t) : dest(d), distance(dis), time_consume(t), link(NULL) {}

    int operator!=(Edge &E) const { return dest != E.dest; }
};

//���㶨��
struct Vertex {

    string name;
    string description;
    int popular_degree;
    //0��ʾû�У�1��ʾ��
    int is_toilet;
    int is_rest;
    //����бߵ�ָ�룬�������Դ����ڽ�����
    Edge *adj;
};

struct Graph {
    bool is_created;
    //�ڵ������
    int num_vertices;
    //�ߵ�����
    int num_edges;
    //ͼ���ڽ�����
    Vertex *node_table;
    //ͼ���ڽӾ���
    double **adj_matrix;

    Graph(int sz) {
        if (sz != 0 && sz < MAX_VERTEX_NUM) {
            num_vertices = sz;
            num_edges = 0;
            node_table = new Vertex[num_vertices];
            is_created = false;
        } else
            cout << "��ʼ�����󣬽ڵ�������" << endl;
//        cout << "Initial Ok" << node_table[0].name << endl;
    }
//    ~Graph();
};


//��С�������߽��Ľṹ�嶨��
struct MSTEdgeNode {
    int head, tail;  //���������ߵ���������
    int cost;       //���������ߵĴ���
};

//���ݶ����ֵ�ҵ���λ��
int GetVertexPos(Graph &graph, string &name);

//���ڽ�����ת��Ϊ�ڽӾ���
void ConvertToMatrix(Graph &graph);

//��ȡ�ڵ�v�ĵ�һ���ڽӶ���
int GetFirstNeighbor(Graph &graph, int v);

//��ȡ�ڵ�v����w�������һ���ڽӶ���
int GetNextNeighbor(Graph &graph, int v, int w);

//�ж�Ҫ�������������֮���Ƿ���ֱ�������ı�
bool IsEdge(Graph graph, string v1, string v2);


#endif //NEWDSPROGRAM_GRAPH_H
