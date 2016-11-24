//
// Created by Aaron on 2016/11/14.
//

#include <cstring>
#include <windows.h>
#include <stdio.h>
#include "function.h"


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
            LoadGraph(graph, "vertexes.txt", "routes.txt");
//            LoadGraph(graph,"new_vertexes.txt","new_routes.txt");
        } else if ("2" == choose) {
            if (graph.is_created) {
                OutputAdjMatrix(graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }

        } else if ("3" == choose) {
            if (graph.is_created) {
                CreateTourSortGraph(graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }

        } else if ("4" == choose) {
            if (graph.is_created) {
                FindLoop(new_tour_graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }

        } else if ("5" == choose) {
            if (graph.is_created) {
                MiniDistance(graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }

        } else if ("6" == choose) {
            if (graph.is_created) {
                MiniSpanTree(graph, "����");
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }

        } else if ("7" == choose) {
            if (graph.is_created) {
                Sort(graph);
            } else {
                cout << "������Ϣ��û��¼�룬��¼�����������" << endl;
            }
        } else if ("8" == choose) {
            if (graph.is_created) {
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
void LoadGraph(Graph &graph, string vertex_txt, string route_txt) {
    //����ڵ���Ϣ
//    string filename = "vertexes.txt";
//    string filename = "new_vertexes.txt";
    ifstream inf1(vertex_txt.c_str());
    int i = 0, j;
    while (inf1.good()) {
        ////���ܹ�ֱ��ͨ������д�����ݣ�����---�Ѹ���������Խ��
        inf1 >> graph.node_table[i].name >> graph.node_table[i].description >> graph.node_table[i].popular_degree
             >> graph.node_table[i].is_toilet >> graph.node_table[i].is_rest;
        //�����˺ܾã�ԭ������Ϊһ��ʼ��ַû�ж�����г�ʼ��
        graph.node_table[i].adj = NULL;
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
//    filename = "routes.txt";
//    filename = "new_routes.txt";
    ifstream inf2(route_txt.c_str());
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
        /**�δ����Ե��Ӧ��������
         * */
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
    int temp;
    for (i = 0; i < num_vertices; i++) {
        cout << graph.node_table[i].name << endl;
        for (edge = graph.node_table[i].adj; edge->link != NULL; edge = edge->link) {//����ĳһ���ڵ�������ڽӽڵ���Ϣ
//            cout<<"Just a test"<<endl;
            temp = edge->dest;
            cout << graph.node_table[temp].name << "\t";
        }
//        edge = graph.node_table[i].adj;
//        while(edge){
//            temp=edge->dest;
//            cout << graph.node_table[temp].name << "\t";
//            edge = edge->link;
//        }
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
    //������ͼ
    LoadGraph(graph, "new_vertexes.txt", "new_routes.txt");
    OutputAdjMatrix(graph);
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



//������С������
void MiniSpanTree(Graph &graph, string u) {
    //��ȡ��ʼ����ͼ�������λ��
    int v = GetVertexPos(graph, u);
//    cout<<" ��С�����������"<<v<<endl;
    //�����ڽӾ�����Ϣ---���㷨Ҫ���ڽӾ�������ȱ�������������ִ�г���
    ConvertToMatrix(graph);
    Prim(graph, v);

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
}




