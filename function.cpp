//
// Created by Aaron on 2016/11/14.
//

#include <cstring>
#include "preDefine.h"

void ShowMenu() {
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
    cout << "7.ͣ��������������Ϣ" << endl;
    cout << "8.�˳�ϵͳ" << endl;
}

//����ͼ�������Ϣ
void LoadGraph(Graph &graph) {
    //����ڵ���Ϣ
    string filename = "vertexes.txt";
    ifstream inf1(filename.c_str());
    string name, description;
    int popular_degree = 0, is_toilet = 0, is_rest = 0;
    int i = 0, j;
    while (inf1.good()) {
        //���ܹ�ֱ��ͨ������д�����ݣ�����
//        inf1>>graph.node_table[i++].name>>graph.node_table[i++].description>>graph.node_table[i++].popular_degree
//            >>graph.node_table[i++].is_toilet>>graph.node_table[i++].is_rest;

        inf1 >> name >> description >> popular_degree
             >> is_toilet >> is_rest;
        graph.node_table[i].name = name;
        graph.node_table[i].description = description;
        graph.node_table[i].popular_degree = popular_degree;
        graph.node_table[i].is_toilet = is_toilet;
        graph.node_table[i].is_rest = is_rest;
        i++;
    }
    inf1.close();

    /**
     * ���Խڵ���Ϣ�Ƿ������ȷ

    for (int m = 0; m < i; m++) {
        cout << m << "  " << (graph.node_table[m].name) << " " << (graph.node_table[m].description) << endl;
    }
*/
//        cout<<j<<"  "<<(graph.node_table[j].name)<<" "<<(graph.node_table[j].description)<<endl;



    //����·����Ϣ
    filename = "routes.txt";
    ifstream inf2(filename.c_str());
    string from, to;
    int timeFee = 0, distance = 0;
    while (inf2.good()) {
        inf2 >> from >> to >> distance >> timeFee;
//        cout<<from<<"  "<<to<<"  "<<distance<<"  "<<timeFee<<endl;
        //���Ҷ������������е�λ��
        i = GetVertexPos(graph, from);
        j = GetVertexPos(graph, to);
        //��������Ϣ����ֵ
        Edge *P = new Edge(j, distance, timeFee);
        Edge *Q = new Edge(i, distance, timeFee);
        P->link = graph.node_table[i].adj;//��һ��P������ΪNULL�������漸�ξͻ᲻�ϵļӵ�������ǰ��
        graph.node_table[i].adj = P;

        Q->link = graph.node_table[j].adj;
        graph.node_table[j].adj = Q;
        graph.num_edges++;
    }
//    cout<<"����Ϊ  "<<graph.num_edges<<endl;
    inf2.close();
    /**
      * ����·����Ϣ�Ƿ������ȷ--Ӧ������ȷ��-----һ��Ҫע����صı���Ҫͳһ��
        for(int m=0;m<graph.num_vertices;m++)
        cout<<(graph.node_table[m].adj->dest)<<" "<<(graph.node_table[m].adj->distance)<<endl;

    int num_vertices=graph.num_vertices;
    Edge *edge;
    for(i=0;i<num_vertices;i++){
        cout<<graph.node_table[i].name<<"  ";
        for(edge=graph.node_table[i].adj;edge;edge=edge->link){//����ĳһ���ڵ�������ڽӽڵ���Ϣ
            cout<<graph.node_table[edge->dest].name<<"  ";
        }
        cout<<endl;
    }
    cout<<"end"<<endl;
 */
}

int GetVertexPos(Graph &graph, string &name) {
    for (int i = 0; i < graph.num_vertices; i++)
        if (name == graph.node_table[i].name)//�ҵ���Ҫ���ҵĶ���
            return i;
    return -1;//û�ҵ�������-1
}

void OutputAdjMatrix(Graph &graph) {
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
            j = edge->dest;
            a[i][j] = edge->distance;
//            cout<<i<<endl;
        }
    graph.adj_matrix = a;
//    cout<<"ת���ɹ�"<<endl;


    /**
     * ��������ڽӾ������Ϣ�Ƿ���ȷ

    for (int i = 0; i < num_vertices; ++i)//��ӡ��һ��
        cout << "\t" << graph.node_table[i].name;
    cout << endl;

    for (i = 0; i < num_vertices; i++) {
        cout << graph.node_table[i].name << "\t";//��ӡ���ı�ͷ
        for (j = 0; j < num_vertices; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
     */
    delete[]edge;
}

//�������·��ͼ
void CreateTourSortGraph(Graph &graph, Graph &tour_graph) {
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
//    cout<<"size ��СΪ"<<tour_map->size()<<endl;//size���صĵ�����ʲô
//    tour_map[0]="1";
//    tour_map[1]="2";
//    tour_map[2]="3";
//    tour_map[3]="4";
//    tour_map[4]="5";
//    tour_map[5]="6";
//    cout<<"size ��СΪ"<<tour_map->size()<<endl;

    int n = 0;

    //��������·��ͼ
    for (int i = 0; i < graph.num_vertices - 1; i++) {
//        cout << "IsEdge(graph," << vex[i] << "," << vex[i + 1] << ") " << IsEdge(graph, vex[i], vex[i + 1]) << "  "
//             << "i=  " << i << endl;
        if (IsEdge(graph, vex[i], vex[i + 1])) {//�����������֮���бߣ���ôֱ�ӽ��������������·��������
            if (i != graph.num_vertices - 2) {
                tour_map[n++] = vex[i];

            } else {
                tour_map[n++] = vex[i];
                tour_map[n++] = vex[i + 1];
//                cout << "vex[i+1]" << vex[i + 1] << endl;

            }
        } else {
            int temp_i = i;
            //���������
            tour_map[n++] = vex[i];
            while (!IsEdge(graph, vex[--temp_i], vex[i + 1])) {//ֻҪ��������֮��û�б�
                tour_map[n++] = vex[temp_i];//��ǰһ��������뵽������·��ͼ��
//                cout<<"temp_i  "<<temp_i<<"    "<<vex[temp_i]<<endl;
            }
            tour_map[n++] = vex[temp_i];
//            cout<<"temp_i->"<<temp_i<<endl;
        }
    }

    /**
     * ���Ե���·��ͼ�Ƿ���ȷ

    cout << "���н���,n=" <<n<< endl;
    cout<<"����·��ͼ���"<<endl;
    for (int m = 0; m < n; m++) {
        cout<<tour_map[m]<<"->";
    }
*/
    CreateTourGraph(graph, tour_graph, tour_map);

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

}

void MiniDistance(Graph &graph) {
    string start_view, end_view;
    cout << "������Ҫ���ҵ�������������" << endl;
    cin >> start_view >> end_view;
    int v = GetVertexPos(graph, start_view);
    int w = GetVertexPos(graph, end_view);
    //����Dijkstra�㷨��������֮������·��������뻨��
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
//    int m=0;
//    int tour_path[num_vertices];
//    while(v!=temp){
//        temp_stack.push(temp);
//        temp=path[temp];
//    }
//    cout<<path[w]<<" "<<path[path[w]];
//    for(int i=0;i<num_vertices;i++)
//        cout<<path[i]<<"->";
//    cout<<endl;
//    cout<<

    while (!temp_stack.empty()) {
        temp = temp_stack.top();
        cout << graph.node_table[temp].name << "-->";
        temp_stack.pop();
    }
    cout << endl << "��̾���Ϊ  " << dist[w] << endl;

}

//������С������
void MiniSpanTree(Graph &graph, string u) {
    //��ȡ��ʼ����ͼ�������λ��
    int v = GetVertexPos(graph, u);
//    cout<<" ��С�����������"<<v<<endl;
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
    for (int i = 0; i < num_vertices - 1; i++) {
        e = edgeNode[i];
        start = graph.node_table[e.head].name;
        departure = graph.node_table[e.tail].name;
//        cout << e.head << "->" << e.tail << "->" << e.cost << endl;

//        start=(graph.node_table[e.head].name);
        cout << "��  " << start << "  ��һ����  " << departure << "�ĵ�·  " << endl;
    }

}

//�����ܵ����������
void Sort(Graph &graph) {
    int choose;
    cout << "1.���ݾ��㻶ӭ������" << endl;
    cout << "2.���ݾ����·������" << endl;
    cout << "      ��ѡ��" << endl;
    cin >> choose;
    switch (choose) {
        case 1:
            SortByPopularDegree(graph);
            break;
        case 2:
            SortByForks(graph);
            break;
    }

}

//���ݻ�ӭ������
void SortByPopularDegree(Graph &graph) {
    //��ȡͼ�л�ӭ�ȵ����ݼ����±�
//    int popular_degree[graph.num_vertices][2];
    SortNode sortNodes[graph.num_vertices];
    for (int i = 0; i < graph.num_vertices; i++) {
//        popular_degree[i][0] = graph.node_table[i].popular_degree;
//        popular_degree[i][1] = i;
        sortNodes[i].value = graph.node_table[i].popular_degree;
        sortNodes[i].name = graph.node_table[i].name;
    }

    int choose;
    cout << "1.ð������" << endl;
    cout << "2.��������" << endl;
    cout << "3.�鲢����" << endl;
    cout << "  ��ѡ��" << endl;
    cin >> choose;
    switch (choose) {
        case 1:
            BubbleSort(sortNodes, graph.num_vertices);
            cout << "��Ծ����ܻ�ӭ�̶Ƚ���ð������Ľ��Ϊ��" << endl;
            cout << "��������\t" << "�����ܻ�ӭ��\t" << endl;
            for (int i = 0; i < graph.num_vertices; i++)
                cout << sortNodes[i].name << "\t\t" << sortNodes[i].value << endl;
            break;
        case 2:
            QuickSort(sortNodes, 0, 11);
            cout << "��Ծ����ܻ�ӭ�̶Ƚ���ð������Ľ��Ϊ��" << endl;
            cout << "��������\t" << "�����ܻ�ӭ��\t" << endl;
            for (int i = 0; i < graph.num_vertices; i++)
                cout << sortNodes[i].name << "\t\t" << sortNodes[i].value << endl;
            break;
        case 3:
//            MergeSort(popular_degree);
            break;
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


    int choose;
    cout << "1.ð������" << endl;
    cout << "2.��������" << endl;
    cout << "3.�鲢����" << endl;
    cout << "  ��ѡ��" << endl;
    cin >> choose;
    switch (choose) {
        case 1:
            BubbleSort(sortNodes, graph.num_vertices);
            cout << "��Ծ����·�����п�������Ľ��Ϊ��" << endl;
            cout << "��������\t" << "�����·��\t" << endl;
            for (int i = 0; i < graph.num_vertices; i++)
                cout << sortNodes[i].name << "\t\t" << sortNodes[i].value << endl;
            break;
        case 2:
            QuickSort(sortNodes, 0, 11);
            cout << "��Ծ����·�����п�������Ľ��Ϊ��" << endl;
            cout << "��������\t" << "�����·��\t" << endl;
            for (int i = 0; i < graph.num_vertices; i++)
                cout << sortNodes[i].name << "\t\t" << sortNodes[i].value << endl;
            break;
        case 3:
//            MergeSort(popular_degree);
            break;
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

//���ҵ�������---����һ���ַ�����ʹ��KMP�ֱ��������������Լ����������
void Search(Graph &graph) {
    string key_word;
    char target[2048];
    memset(target, 0, 2048);
    char pattern[2048];
    memset(pattern, 0, 2048);
//    char pattern2[2014];
    cout << "������Ҫ���ҵĹؼ���" << endl;
    cin >> key_word;

//    key_word.
    strcpy(target, key_word.c_str());
    /////////////////////////////////////////
//    int m=0;
//    while('\0'!=target[m]){
//        cout<<target[m];
//        m++;
//    }
    /////////////////////////////////////
    //�������о���������Լ�����
    int i = 0;
    for (; i < graph.num_vertices; i++) {

        strcpy(pattern, graph.node_table[i].name.c_str());
//        //////////////////////////////////////////
//        int m=0;cout<<"��������Ϊ is";
//        while('\0'!=pattern[m]){
//            cout<<pattern[m];
//            m++;
//        }
//

        ////////////////////////////////////////////
        if (KMPSearch(target, pattern) == 1) {
            cout << graph.node_table[i].description << endl;
            break;
        }
        memset(pattern, 0, 2048);
        strcpy(pattern, graph.node_table[i].description.c_str());
        ///////////////////////////////////////
//        m=0;cout<<"������Ϊ is";
//        while('\0'!=pattern[m]){
//            cout<<pattern[m];
//            m++;
//        }
        //////////////////////////////////////
        if (KMPSearch(target, pattern) == 1) {
            cout << graph.node_table[i].description << endl;
            break;
        }
    }
    if (i == graph.num_vertices)
        cout << "δ���ҵ���Ҫ��Ϣ������������" << endl;

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

//    cout<<"target_length  "<<target_length<<"   pattern_length  "<<pattern_length<<endl;
//    //////////////////////////////
//    int m=0;cout<<"pattern ������ is  ";
//    while('\0'!=pattern[m]){
//        cout<<pattern[m];
//        m++;
//    }


    /////////////////////////////
    //����ؼ��ֵ�ǰ׺����
    CptPfFunc(pattern, prefix);
    /////////////////////////////
//     m=1;cout<<"ǰ׺���� is  ";
//    while('\0'!=prefix[m]){
//        cout<<prefix[m];
//        m++;
//    }
    ////////////////////////
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
//    ///////////////////////////
//    int m=0;cout<<"CptPfFunc   pattern ������ is  ";
//    while('\0'!=pattern[m]){
//        cout<<pattern[m];
//        m++;
//    }
//    cout<<"length_pattern is "<<length_pattern<<endl;
    ///////////////////////////////
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

