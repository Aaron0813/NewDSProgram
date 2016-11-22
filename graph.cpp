//
// Created by Aaron on 2016/11/21.
//
#include "graph.h"

//根据顶点的值找到其位置
int GetVertexPos(Graph &graph, string &name) {
    for (int i = 0; i < graph.num_vertices; i++)
        if (name == graph.node_table[i].name)//找到了要查找的顶点
            return i;
    return -1;//没找到，返回-1
}

//将邻接链表转换为邻接矩阵
void ConvertToMatrix(Graph &graph) {
    int i, j, num_vertices = graph.num_vertices;
    //创建一个二维数组用来存储邻接矩阵的信息
    double **a = new double *[num_vertices];
    for (i = 0; i < num_vertices; i++)
        a[i] = new double[num_vertices];

    //初始化矩阵信息
    for (i = 0; i < num_vertices; i++)
        for (j = 0; j < num_vertices; j++)
            if (i != j)
                a[i][j] = INFINITY;
            else
                a[i][j] = 0;
//    cout<<"矩阵初始化成功"<<endl;

    //将邻接链表转存为邻接矩阵
    Edge *edge = new Edge;
    for (i = 0; i < num_vertices; i++)
        for (edge = graph.node_table[i].adj; edge; edge = edge->link) {//遍历某一个节点的所有邻接节点信息
            j = edge->dest;
            a[i][j] = edge->distance;
//            cout<<i<<endl;
        }
    graph.adj_matrix = a;
    delete[]edge;
}