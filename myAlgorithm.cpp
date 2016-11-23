//
// Created by Aaron on 2016/11/23.
//
#include <cstring>
#include "myAlgorithm.h"

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