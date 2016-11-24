//
// Created by Aaron on 2016/11/21.
//
#include "graph.h"

//���ݶ����ֵ�ҵ���λ��
int GetVertexPos(Graph &graph, string &name) {
    for (int i = 0; i < graph.num_vertices; i++)
        if (name == graph.node_table[i].name)//�ҵ���Ҫ���ҵĶ���
            return i;
    return -1;//û�ҵ�������-1
}

//���ڽ�����ת��Ϊ�ڽӾ���
void ConvertToMatrix(Graph &graph) {
    int i, j, num_vertices = graph.num_vertices;
    //����һ����ά���������洢�ڽӾ������Ϣ
    double **a = new double *[num_vertices];
    for (i = 0; i < num_vertices; i++)
        a[i] = new double[num_vertices];

    //��ʼ��������Ϣ
    for (i = 0; i < num_vertices; i++)
        for (j = 0; j < num_vertices; j++)
            if (i != j)
                a[i][j] = INFINITY;
            else
                a[i][j] = 0;
//    cout<<"�����ʼ���ɹ�"<<endl;

    //���ڽ�����ת��Ϊ�ڽӾ���
    Edge *edge = new Edge;
    for (i = 0; i < num_vertices; i++)
        for (edge = graph.node_table[i].adj; edge; edge = edge->link) {//����ĳһ���ڵ�������ڽӽڵ���Ϣ
            cout << edge << endl;
            j = edge->dest;
            a[i][j] = edge->distance;
//            cout<<i<<endl;
        }
    graph.adj_matrix = a;
    delete[]edge;
}

/**
 * ��ȡ�ڵ�v�ĵ�һ���ڽӶ���
 * @param graph
 * @param v
 * @return ���ڷ���λ�ã����򷵻�-1
 */
int GetFirstNeighbor(Graph &graph, int v) {
    if (v != -1) {
        Edge *p = graph.node_table[v].adj;
        //ֻҪ�ڵ���ھͷ�����Ŀ�ĵ�
        if (p != NULL)
            return p->dest;
    }
    return -1;//�ڵ㲻�����򷵻�-1
}

/**
 * ��ȡgraph�нڵ�v����w�������һ���ڽӶ���
 * @param graph
 * @param v
 * @param w
 * @return ���ڷ���λ�ã����򷵻�-1
 */
int GetNextNeighbor(Graph &graph, int v, int w) {
    if (v != -1) {
        Edge *p = graph.node_table[v].adj;
        while (p != NULL) {
            //�����ǰ�ڵ���w������һ���ڵ㲻Ϊ��
            if (p->dest == w && p->link != NULL)
                //������һ���ڽӽڵ����ڽӱ��е�λ��
                return p->link->dest;
            else
                //����Ѱ�ҽڵ�w
                p = p->link;
        }
    }
    return -1;//û���ҵ���һ���ڽӶ���---����-1
}

/**
 * �ж�graph�е�v1,v2��������֮���Ƿ���ֱ�����ڵı�
 * @param graph
 * @param v1
 * @param v2
 * @return
 */
bool IsEdge(Graph graph, string v1, string v2) {
    //��ȡ����v1���ڽӱ��е�����λ��
    int i = GetVertexPos(graph, v1);
    //��ȡ����v2���ڽӱ��е�����λ��
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