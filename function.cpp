//
// Created by Aaron on 2016/11/14.
//

#include <cstring>
#include <windows.h>
#include <stdio.h>
#include "preDefine.h"
#include "park.h"
#include "graph.h"

void ShowMenu(Graph &graph) {
    Graph tour_graph(12);
    Graph new_tour_graph(8);
    bool flag = true;
    string choose;
    while (flag) {
//        system("cls");
        fflush(stdin);
        cout << "============================" << endl;
        cout << "    ��ӭʹ�þ�������ϵͳ    " << endl;
        cout << "       **��ѡ��˵�**       " << endl;
        cout << "============================" << endl;
        cout << "1.������������ֲ�ͼ" << endl;
        cout << "2.�����������ֲ�ͼ" << endl;
        cout << "3.���������·ͼ" << endl;
        cout << "4.���������·ͼ�еĻ�·" << endl;
        cout << "5.��������������·������̾���" << endl;
        cout << "6.�����·�޽��滮ͼ" << endl;
        cout << "7.��������" << endl;
        cout << "8.��������" << endl;
        cout << "9.ͣ��������" << endl;
        cout << "10.�˳�ϵͳ" << endl;
        cin >> choose;
        if ("1" == choose) {
            LoadGraph(graph);
        } else if ("2" == choose) {
            if (graph.is_created == true) {
                OutputAdjMatrix(graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }

        } else if ("3" == choose) {
            if (graph.is_created == true) {
                CreateTourSortGraph(graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }

        } else if ("4" == choose) {
            if (graph.is_created == true) {
                FindLoop(new_tour_graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }

        } else if ("5" == choose) {
            if (graph.is_created == true) {
                MiniDistance(graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }

        } else if ("6" == choose) {
            if (graph.is_created == true) {
                MiniSpanTree(graph, "����");
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }

        } else if ("7" == choose) {
            if (graph.is_created == true) {
                Sort(graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }
        } else if ("8" == choose) {
            if (graph.is_created == true) {
                Search(graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }
        } else if ("9" == choose) {
            Park();
        } else if ("10" == choose) {
            cout << "�ɹ��˳�����" << endl;
            exit(0);
        } else {
            cout << "�����������������" << endl;
//            cout<<"�������������"<<endl;
//            cin>>choose;
        }
    }
}

/**
 * ����ͼ�������Ϣ
 * @param graph
 */
void LoadGraph(Graph &graph) {
    //����ڵ���Ϣ
    string filename = "vertexes.txt";
//    string filename = "new_vertexes.txt";
    ifstream inf1(filename.c_str());
    int i = 0, j;
    while (inf1.good()) {
        ////���ܹ�ֱ��ͨ������д�����ݣ�����---�Ѹ���������Խ��
        inf1 >> graph.node_table[i].name >> graph.node_table[i].description >> graph.node_table[i].popular_degree
             >> graph.node_table[i].is_toilet >> graph.node_table[i].is_rest;
        i++;
    }
//    graph.num_vertices=i+1;
    inf1.close();

    /**
     * ���Խڵ���Ϣ�Ƿ������ȷ*/
    cout << "������Ϣ¼��ɹ�:" << endl;
    for (int m = 0; m < i; m++) {
        cout << m << "\t" << (graph.node_table[m].name) << "\t" << (graph.node_table[m].description) << "\t" << endl;
    }

    //����·����Ϣ
    filename = "routes.txt";
//    filename = "new_routes.txt";
    ifstream inf2(filename.c_str());
    string from, to;
    int timeFee = 0, distance = 0;
    while (inf2.good()) {
        inf2 >> from >> to >> distance >> timeFee;

        //���Ҷ������������е�λ��
        i = GetVertexPos(graph, from);
        j = GetVertexPos(graph, to);
        //��������Ϣ����ֵ
        Edge *P = new Edge(j, distance, timeFee);
        Edge *Q = new Edge(i, distance, timeFee);
        P->link = graph.node_table[i].adj;//��һ��P������ΪNULL�������漸�ξͻ᲻�ϵļӵ�����ǰ��
        graph.node_table[i].adj = P;

        Q->link = graph.node_table[j].adj;
        graph.node_table[j].adj = Q;
        graph.num_edges++;
    }

    inf2.close();


    /**
      * ����·����Ϣ�Ƿ������ȷ--Ӧ������ȷ��-----һ��Ҫע����صı���Ҫͳһ��*/
    cout << endl << endl << "·����Ϣ¼��ɹ�,����Ϊ���ھ������Ϣ:" << endl;
//    for (int m = 0; m < graph.num_vertices; m++) {
//        cout << (graph.node_table[m].adj->dest) << " " << (graph.node_table[m].adj->distance) << endl;
//        }

//    cout << "111  num vertexes   " << graph.num_vertices << endl;
    int num_vertices = graph.num_vertices;
    Edge *edge;
    for (i = 0; i < num_vertices; i++) {
        cout << graph.node_table[i].name << "\t";
        for (edge = graph.node_table[i].adj; edge; edge = edge->link) {//����ĳһ���ڵ�������ڽӽڵ���Ϣ
            cout << graph.node_table[edge->dest].name << "\t";
        }
        cout<<endl;
    }
    ///////////////////////////////////////////////
//    cout<<graph.node_table[5].name<<endl;
//    Edge *edge;
//    for(edge=graph.node_table[5].adj;edge;edge=edge->link){//����ĳһ���ڵ�������ڽӽڵ���Ϣ
//            cout<<graph.node_table[edge->dest].name<<"  ";
//        }
//    cout<<"end"<<endl;

    //���ͼ�Ѿ����ɹ�����
    graph.is_created = true;
    cout << endl << endl << "ͼ�Ѿ������ɹ�" << endl;

}


//����ڽӾ������Ϣ
void OutputAdjMatrix(Graph &graph) {

    ConvertToMatrix(graph);
    int num_vertices = graph.num_vertices;
    /**
     * ��������ڽӾ������Ϣ�Ƿ���ȷ*/

    for (int i = 0; i < num_vertices; ++i)//��ӡ��һ��
        cout << "\t" << graph.node_table[i].name;
    cout << endl;

    for (int i = 0; i < num_vertices; i++) {
        cout << graph.node_table[i].name << "\t";//��ӡ���ı�ͷ
        for (int j = 0; j < num_vertices; j++)
            cout << graph.adj_matrix[i][j] << "\t";
        cout << endl;
    }
}



//�������·��ͼ
void CreateTourSortGraph(Graph &graph) {
    string *vex = DFSTraverse(graph);

    /**
     * ����������ȱ������
    cout<<"������ȱ�·���"<<endl;
    for (int i = 0; i < graph.num_vertices; i++) {
        cout << vex[i] << "->";
    }
    cout << endl;
    cout<<"������ȱ�������"<<endl;
*/
    string tour_map[2 * graph.num_vertices];
    int n = 0;
    //��������·��ͼ
    for (int i = 0; i < graph.num_vertices - 1; i++) {
        if (IsEdge(graph, vex[i], vex[i + 1])) {//�����������֮���бߣ���ôֱ�ӽ��������������·��������
            if (i != graph.num_vertices - 2) {
                tour_map[n++] = vex[i];

            } else {
                tour_map[n++] = vex[i];
                tour_map[n++] = vex[i + 1];
            }
        } else {
            int temp_i = i;
            //���������
            tour_map[n++] = vex[i];
            while (!IsEdge(graph, vex[--temp_i], vex[i + 1])) {//ֻҪ��������֮��û�б�
                tour_map[n++] = vex[temp_i];//��ǰһ��������뵽������·��ͼ��
            }
            tour_map[n++] = vex[temp_i];
        }
    }

    /**
     * ���Ե���·��ͼ�Ƿ���ȷ*/

//    cout << "���н���,n=" << n << endl;
    cout << "����·��ͼ���" << endl;
    for (int m = 0; m < n; m++) {
        cout << tour_map[m] << "->";
    }
    cout << "����" << endl << endl << endl;
//    CreateTourGraph(graph, tour_graph, tour_map);

}

void CreateTourGraph(Graph &graph, Graph &tour_graph, string tour_map[]) {
    //��ʼ������ͼ
    for (int i = 0; i < graph.num_vertices; i++) {
        tour_graph.node_table[i].name = graph.node_table[i].name;
        tour_graph.node_table[i].adj = NULL;
    }
    int tour_edges = 0;
//    for()
}

//������ȱ����㷨-�ݹ����ں���---���˰�����󣬾�Ȼ��������Ϊroutes.txt�ļ�����һ�����С�����
string *DFSTraverse(Graph &graph) {
    //���������Ӧ�Ľڵ��Ƿ��Ѿ�������
    int *visited = new int[graph.num_vertices];
    string *vertex = new string[graph.num_vertices];
    int num = 0;
    //��ʼ�����нڵ�Ϊδ���ʵ�״̬
    for (int i = 0; i < graph.num_vertices; i++)
        visited[i] = 0;
    DFS(graph, 0, visited, vertex, num);
    //�ͷſռ�
    delete[]visited;
//    cout<<"num �Ĵ�СΪ"<<num<<endl;
    return vertex;
}

/**
 * ������ȱ����㷨--�ݹ�
 * @param graph
 * @param v �����ʵĽڵ�
 * @param visited ���������Щ�ڵ��Ѿ������ʵ�����
 */

void DFS(Graph &graph, int v, int visited[], string *vertex, int &num) {
    //���ʽڵ�v
//    cout<<graph.node_table[v].name<<"-->";
    vertex[num++] = graph.node_table[v].name;
//    cout<<vertex[num]<<"  "<<num<<endl;
//    num++;
    //��Ǹýڵ��Ѿ�������
    visited[v] = 1;
    //��ȡv�ĵ�һ���ڽӶ���
    int w = GetFirstNeighbor(graph, v);
    //���ڵ�w����
    while (w != -1) {
        //����û�б�����
        if (!visited[w])
            DFS(graph, w, visited, vertex, num);//���ʽڵ�w
        //��ȡ���ڽڵ�w�������һ���ڵ�
        w = GetNextNeighbor(graph, v, w);
    }
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

//����һ��ͼ���нڵ�������
void FindInDegree(Graph graph, int indegree[]) {
    Edge *edge = new Edge;
    for (int i = 0; i < graph.num_vertices; i++)
        for (edge = graph.node_table[i].adj; edge; edge = edge->link)
            indegree[edge->dest]++;
    delete edge;
}

//����һ��ͼ���Ƿ��л�·
void FindLoop(Graph &graph) {


    cout << "�ҳ���·�ɹ�" << endl;
}

void MiniDistance(Graph &graph) {
    string start_view, end_view;
    cout << "������Ҫ���ҵ�������������" << endl;

    int v, w;
    while (true) {
        cout << "�������������" << endl;
        cin >> start_view;
        v = GetVertexPos(graph, start_view);
        if (v == -1)
            cout << "��㲻���ڣ�����������" << endl;
        else
            break;
    }
    while (true) {
        cout << "�������յ�����" << endl;
        cin >> end_view;
        w = GetVertexPos(graph, end_view);
        if (w == -1)
            cout << "�յ㲻���ڣ�����������" << endl;
        else
            break;
    }
    //����Dijkstra�㷨��������֮������·��������뻨��
    if (v == w) {
        cout << "������յ���ͬ����Ϊ" << start_view << endl;
    } else
        Dijkstra(graph, v, w);
}

void Dijkstra(Graph &graph, int v, int w) {
    //��ȡͼ�Ľڵ���
    int num_vertices = graph.num_vertices;
    //���·����������---v���ýڵ��Ŀǰ���·������
    int dist[num_vertices];
    //��ǰ�ڵ��ǰһ���ڵ�
    int path[num_vertices];
    //���·�����㼯---��־�Ѿ��ҵ����·���Ķ��㼯
    int s[num_vertices];

    //�����ڽӾ�����Ϣ
    ConvertToMatrix(graph);
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = (int) graph.adj_matrix[v][i];
        s[i] = 0;
        //ֻҪ����֮�䲻�ǲ��ɴ�ݼ����ඥ���ǰһ������Ϊv
        if (i != v && dist[i] < INFINITY)
            path[i] = v;
        else
            path[i] = -1;
    }
    //����v���붥�㼯��
    s[v] = 1;
    dist[v] = 0;
    //ѡ��ǰ���ڼ���S�о������·���Ķ���u
    for (int i = 0; i < num_vertices - 1; i++) {
        int min = INFINITY;
        int u = v;
        //��һ����ǰ���пɴ�·���л�����С�Ķ���u
        for (int j = 0; j < num_vertices; j++)
            if (!s[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        //������u���뼯��s
        s[u] = 1;
        for (int k = 0; k < num_vertices; k++)//�޸�
            if (!s[k] && graph.adj_matrix[u][k] < INFINITY && dist[u] + graph.adj_matrix[u][k] < dist[k]) {
                dist[k] = (int) (dist[u] + graph.adj_matrix[u][k]);
                path[k] = u;
            }
    }
    stack<int> temp_stack;
    int temp = path[w];
    temp_stack.push(w);
    while (v != temp) {
        temp_stack.push(temp);
        temp = path[temp];
    }
    temp_stack.push(v);

    while (!temp_stack.empty()) {
        temp = temp_stack.top();
        cout << graph.node_table[temp].name << "-->";
        temp_stack.pop();
    }
    cout << "����" << endl;
    cout << endl << "��̾���Ϊ  " << dist[w] << endl;

}

//������С������
void MiniSpanTree(Graph &graph, string u) {
    //��ȡ��ʼ����ͼ�������λ��
    int v = GetVertexPos(graph, u);
//    cout<<" ��С�����������"<<v<<endl;
    //�����ڽӾ�����Ϣ---���㷨Ҫ���ڽӾ�������ȱ�������������ִ�г���
    ConvertToMatrix(graph);
    Prim(graph, v);

}

//ʹ��Prim�㷨������С������
void Prim(Graph &graph, int v) {
    //ͼ�еĶ�����
    int num_vertices = graph.num_vertices;
    //��¼��С����
    int *low_cost = new int[num_vertices];
    //��¼��������ڽڵ�
    int *near_vex = new int[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        //��¼����v������Ĵ���
        if (i != v) {
            low_cost[i] = graph.adj_matrix[v][i];
            near_vex[i] = 0;
        }

    }
    //����v�ӵ����������㼯��
    near_vex[v] = -1;
    low_cost[v] = 0;
//    cout<<"near_vex[v]=-1;";
    //����һ����С�����������Ϊ������Ԫ
    MSTEdgeNode e;
    //�洢�������ߵ�����
    MSTEdgeNode *edgeNode = new MSTEdgeNode[num_vertices - 1];
    for (int i = 1; i < num_vertices; i++) {
        //ѭ��num_vertices-1�Σ�����num_vertices-1��
        int min = INFINITY;
        int temp = 0;
        for (int j = 0; j < num_vertices; j++)
            if (near_vex[j] != -1 && low_cost[j] < min) {
                temp = j;
                min = low_cost[j];
            }
        //������������Ķ��㵽�������ڲ��Ķ��������е���СȨֵ�ıߣ�temp�ǵ�ǰ������СȨֵ�ߵ�λ��
        if (temp) {//temp==0��ʾ��Ҳ�Ҳ�������Ҫ��Ķ�����
            e.tail = near_vex[temp];
            e.head = temp;
            e.cost = low_cost[temp];
            edgeNode[i - 1] = e;//��ѡ���ı߼�����������
            near_vex[temp] = -1;//���ı����Ѿ����뵽��������
            for (int j = 1; j < num_vertices; j++)
                if (near_vex[j] != -1 && graph.adj_matrix[temp][j] < low_cost[j]) {//����߲���������������Ҫ�����޸�
                    low_cost[j] = graph.adj_matrix[temp][j];
                    near_vex[j] = temp;
                }
        }
    }


    //�����С�������Ľ��
//    cout<<"�����С�������Ľ��";
//    MSTEdgeNode e;
    string start;
    string departure;
    int total_cost = 0;
    for (int i = 0; i < num_vertices - 1; i++) {
        e = edgeNode[i];
        start = graph.node_table[e.head].name;
        departure = graph.node_table[e.tail].name;
        total_cost += e.cost;
//        cout << e.head << "->" << e.tail << "->" << e.cost << endl;

//        start=(graph.node_table[e.head].name);
        cout << "��   " << start << "\t" << "��һ����    " << departure << "\t" << "�ĵ�· " << endl;
    }
    cout << "�޽�·�̵��ܴ���Ϊ   " << total_cost << endl;

}

//�����ܵ����������
void Sort(Graph &graph) {
    bool flag = true;
    string choose;
    while (flag) {
        cout << "1.���ݾ��㻶ӭ������" << endl;
        cout << "2.���ݾ����·������" << endl;
        cout << "3.�������˵�" << endl;
        cout << "      ��ѡ��" << endl;
        cin >> choose;
        if ("1" == choose) {
            SortByPopularDegree(graph);
        } else if ("2" == choose) {
            SortByForks(graph);
        } else if ("3" == choose) {
            flag = false;
            ShowMenu(graph);
        } else {
            cout << "������������������" << endl;
        }
    }
}

//���ݻ�ӭ������
void SortByPopularDegree(Graph &graph) {
    //��ȡͼ�л�ӭ�ȵ����ݼ����±�
    SortNode sortNodes[graph.num_vertices];
    for (int i = 0; i < graph.num_vertices; i++) {
        sortNodes[i].value = graph.node_table[i].popular_degree;
        sortNodes[i].name = graph.node_table[i].name;
    }

    string choose;
    cout << "1.ð������" << endl;
    cout << "2.��������" << endl;
//    cout << "3.�鲢����" << endl;
    cout << "  ��ѡ��" << endl;
    cin >> choose;
    if ("1" == choose) {
        BubbleSort(sortNodes, graph.num_vertices);
        cout << "��Ծ����ܻ�ӭ�̶Ƚ���ð������Ľ��Ϊ��" << endl;
        OutputSortResult(graph, sortNodes);
    } else if ("2" == choose) {
        QuickSort(sortNodes, 0, 11);
        cout << "��Ծ����ܻ�ӭ�̶Ƚ���ð������Ľ��Ϊ��" << endl;
        OutputSortResult(graph, sortNodes);
    }
// else if("3"==choose){
//        MergeSort(popular_degree);
//    }
    else {
        cout << "������������������" << endl;
    }

}

//���ݲ�·������
void SortByForks(Graph &graph) {
    SortNode sortNodes[graph.num_vertices];
    for (int i = 0; i < graph.num_vertices; i++) {
        int j = 0;
        for (Edge *edge = graph.node_table[i].adj; edge; edge = edge->link)
            j++;//��¼��ǰ�ڵ�Ĳ�·��
        sortNodes[i].value = j;
        sortNodes[i].name = graph.node_table[i].name;
    }

    string choose;
    cout << "1.ð������" << endl;
    cout << "2.��������" << endl;
//    cout << "3.�鲢����" << endl;
    cout << "  ��ѡ��" << endl;
    cin >> choose;
    if ("1" == choose) {
        BubbleSort(sortNodes, graph.num_vertices);
        cout << "��Ծ����·�����п�������Ľ��Ϊ��" << endl;
        OutputSortResult(graph, sortNodes);
    } else if ("2" == choose) {
        QuickSort(sortNodes, 0, 11);
        cout << "��Ծ����·�����п�������Ľ��Ϊ��" << endl;
        OutputSortResult(graph, sortNodes);
    }
// else if("3"==choose){
//        MergeSort(popular_degree);
//    }
    else {
        cout << "������������������" << endl;
    }

}

//ð������---�βθ�һ�£��ĳ����ƺ�Ȩֵ������---��û��Ҫ�������±����������
void BubbleSort(SortNode sortNodes[], int size) {

    cout << "size= " << size << endl;

    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if (sortNodes[j].value < sortNodes[j + 1].value) {
                Swap(sortNodes[j], sortNodes[j + 1]);
            }

}

//��������
void QuickSort(SortNode sortNode[], int left, int right) {
    if (left < right) {
        //����
        int pivot = Partition(sortNode, left, right);
        //������ȡ���ݹ���п�������
        QuickSort(sortNode, left, pivot - 1);
        //����������ݹ���п�������
        QuickSort(sortNode, pivot + 1, right);
    }
}

//��������ĸ�������
int Partition(SortNode sortNode[], int left, int right) {
    //ȡ����ߵ���Ϊ����Ļ�׼
    int pivot = left;
    Swap(sortNode[left], sortNode[(left + right) / 2]);
    SortNode standard = sortNode[left];
    for (int i = left + 1; i <= right; i++)
        if (sortNode[i].value > standard.value && ++pivot != i)
            Swap(sortNode[pivot], sortNode[i]);
    Swap(sortNode[left], sortNode[pivot]);
    return pivot;
}

//����������
void Swap(SortNode &node1, SortNode &node2) {
    SortNode temp = node2;
    node2 = node1;
    node1 = temp;
}

//�鲢����
void MergeSort(int popular_degree[][2], int size) {

}


void OutputSortResult(Graph &graph, SortNode sortNodes[]) {
    cout << "��������\t" << "�����·��\t" << endl;
    for (int i = 0; i < graph.num_vertices; i++)
        cout << sortNodes[i].name << "\t\t" << sortNodes[i].value << endl;
}

//���ҵ�������---����һ���ַ�����ʹ��KMP�ֱ��������������Լ����������
void Search(Graph &graph) {
    string key_word;
    char target[2048];
    memset(target, 0, 2048);
    char pattern[2048];
    memset(pattern, 0, 2048);
    cout << "������Ҫ���ҵĹؼ���" << endl;
    cin >> key_word;
    /**
     * ԭ���ĳ���*/

    strcpy(pattern, key_word.c_str());

    //�������о���������Լ�����
    int i = 0;
    for (; i < graph.num_vertices; i++) {
        memset(target, 0, 2048);
        strcpy(target, graph.node_table[i].name.c_str());
//        cout<<"i= "<<i<<target<<endl;
        if (KMP(target, pattern) == 0) {
            cout << graph.node_table[i].description << endl;
            break;
        }
        memset(target, 0, 2048);
        strcpy(target, graph.node_table[i].description.c_str());

        if (KMP(target, pattern) == 0) {
            cout << graph.node_table[i].description << endl;
            break;
        }
    }
    if (i == graph.num_vertices)
        cout << "δ���ҵ���Ҫ��Ϣ������������" << endl;



    /**
     * �µĴ���
     */
//    cout<<"pattern Ϊ"<<pattern<<endl;
//    int i = 0;
//    for (; i < graph.num_vertices; i++) {
//
////        strcpy(pattern, graph.node_table[i].name.c_str());
//        strcpy(target,graph.node_table[i].name.c_str());
//
//        if (KMP(target, pattern) !=- 1) {
//            cout << graph.node_table[i].description << endl;
//            break;
//        }
//        memset(pattern, 0, 2048);
//        strcpy(pattern, graph.node_table[i].description.c_str());
//
//        if (KMP(target, pattern) != 1) {
//            cout << graph.node_table[i].description << endl;
//            break;
//        }
//    }
//    if (i == graph.num_vertices)
//        cout << "δ���ҵ���Ҫ��Ϣ������������" << endl;

}

//ʹ��KMP�㷨���в��ҹؼ��ֵĲ���
int KMPSearch(char target[], char pattern[]) {
    int prefix[256];
    int target_length = 0;
    int pattern_length = 0;

//    cout<<"����KMP���㷨"<<endl;
    //������������ĳ���
    while ('\0' != target[target_length])
        target_length++;
    while ('\0' != pattern[pattern_length])
        pattern_length++;

    //����ؼ��ֵ�ǰ׺����
    CptPfFunc(pattern, prefix);

    //�Ѿ�ƥ����ַ�����
    int nocm = 0;
    for (int i = 0; i < target_length; i++) {
        while (nocm > 0 && pattern[nocm] != target[i])
            nocm = prefix[nocm];
        if (pattern[nocm] == target[i])
            nocm++;
        if (nocm == pattern_length) {
            return 1;
        }
    }
    return 0;
}

//����ģʽ��ǰ׺�ĺ���
void CptPfFunc(char pattern[], int prefix[]) {
    int length_pattern = 0;
    //����ģʽ���ĳ���
    while ('\0' != pattern[length_pattern])
        length_pattern++;

    int length_longest_prefix = 0;
    //prefix�����±��0��ʼ����Ϊ�Ѿ�ƥ����ַ���û���κ�����
    prefix[1] = 0;
    //nocm��ʾƥ����ַ�������
    for (int nocm = 2; nocm < length_pattern + 1; nocm++) {
        while (length_longest_prefix > 0 && (pattern[length_longest_prefix] != pattern[nocm - 1]))
            length_longest_prefix = prefix[length_longest_prefix];
        if (pattern[length_longest_prefix] == pattern[nocm - 1])
            length_longest_prefix++;
        prefix[nocm] = length_longest_prefix;
    }
}


//�µ�KMPǰ׺����
void get_next(char *t, int next[]) {
    int t_len = strlen(t);
    int i = 0;         //���ÿ��next[i]
    next[0] = -1; //���ƻ�������,Ȼ�����next[i+1]
    int j = -1;     //������λ���±�
    /*
    next[i]=k =>T0...Tk-1=Ti-k...Ti-1
       ���next[i+1]
    1> ���T0..Tk-1Tk=Ti-k...Ti-1Ti=>next[i+1]=k+1=next[i]+1;
    2>Tk<>Ti,next[k]=k', ���Ti=Tk'=>next[i+1]=k'+1=next[k]+1=next[next[i]]+1;
    3>���ε��� ������next[i+1]=next[0]+1=0,��
    */
    while (i < t_len) {
        if (j == -1 || t[i] == t[j])  //j==-1֤���Ѿ���t[0]��ƥ���ˣ���ʱnext[i+1]=0
        {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

//KMP���㷨
int KMP(char *s, char *t) {
    int s_len = strlen(s);
    int t_len = strlen(t);
    int i = 0;
    int j = 0;
    int *next = new int[t_len];
    get_next(t, next);
    if (t_len > s_len) return -1;
    while (i < s_len && j < t_len) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }//end while
    if (j >= t_len)
        return 0;
    else
        return -1;
}


