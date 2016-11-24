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
            cout << edge << endl;
            j = edge->dest;
            a[i][j] = edge->distance;
//            cout<<i<<endl;
        }
    graph.adj_matrix = a;
    delete[]edge;
}

/**
 * 获取节点v的第一个邻接顶点
 * @param graph
 * @param v
 * @return 存在返回位置，否则返回-1
 */
int GetFirstNeighbor(Graph &graph, int v) {
    if (v != -1) {
        Edge *p = graph.node_table[v].adj;
        //只要节点存在就返回其目的地
        if (p != NULL)
            return p->dest;
    }
    return -1;//节点不存在则返回-1
}

/**
 * 获取graph中节点v排在w后面的下一个邻接顶点
 * @param graph
 * @param v
 * @param w
 * @return 存在返回位置，否则返回-1
 */
int GetNextNeighbor(Graph &graph, int v, int w) {
    if (v != -1) {
        Edge *p = graph.node_table[v].adj;
        while (p != NULL) {
            //如果当前节点是w并且下一个节点不为空
            if (p->dest == w && p->link != NULL)
                //返回下一个邻接节点在邻接表中的位置
                return p->link->dest;
            else
                //继续寻找节点w
                p = p->link;
        }
    }
    return -1;//没有找到下一个邻接顶点---返回-1
}

/**
 * 判断graph中的v1,v2两个顶点之间是否有直接相邻的边
 * @param graph
 * @param v1
 * @param v2
 * @return
 */
bool IsEdge(Graph graph, string v1, string v2) {
    //获取顶点v1在邻接表中的坐标位置
    int i = GetVertexPos(graph, v1);
    //获取顶点v2在邻接表中的坐标位置
    int j = GetVertexPos(graph, v2);
    for (Edge *edge = graph.node_table[i].adj; edge; edge = edge->link) {
        if (j == edge->dest)
            return true;
//        else{
//            edge = edge->link;
//        }
    }
    return false;
}