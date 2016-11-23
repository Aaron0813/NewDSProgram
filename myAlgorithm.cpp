//
// Created by Aaron on 2016/11/23.
//
#include <cstring>
#include "myAlgorithm.h"

//深度优先遍历算法-递归的入口函数---找了半天错误，居然发现是因为routes.txt文件多了一个空行。。。
string *DFSTraverse(Graph &graph) {
    //用来标记相应的节点是否已经被访问
    int *visited = new int[graph.num_vertices];
    string *vertex = new string[graph.num_vertices];
    int num = 0;
    //初始化所有节点为未访问的状态
    for (int i = 0; i < graph.num_vertices; i++)
        visited[i] = 0;
    DFS(graph, 0, visited, vertex, num);
    //释放空间
    delete[]visited;
//    cout<<"num 的大小为"<<num<<endl;
    return vertex;
}

/**
 * 深度优先遍历算法--递归
 * @param graph
 * @param v 待访问的节点
 * @param visited 用来标记哪些节点已经被访问的数组
 */

void DFS(Graph &graph, int v, int visited[], string *vertex, int &num) {
    //访问节点v
//    cout<<graph.node_table[v].name<<"-->";
    vertex[num++] = graph.node_table[v].name;
//    cout<<vertex[num]<<"  "<<num<<endl;
//    num++;
    //标记该节点已经被访问
    visited[v] = 1;
    //获取v的第一个邻接顶点
    int w = GetFirstNeighbor(graph, v);
    //若节点w存在
    while (w != -1) {
        //并且没有被访问
        if (!visited[w])
            DFS(graph, w, visited, vertex, num);//访问节点w
        //获取排在节点w后面的下一个节点
        w = GetNextNeighbor(graph, v, w);
    }
}

void Dijkstra(Graph &graph, int v, int w) {
    //获取图的节点数
    int num_vertices = graph.num_vertices;
    //最短路径长度数组---v到该节点的目前最短路径长度
    int dist[num_vertices];
    //当前节点的前一个节点
    int path[num_vertices];
    //最短路径顶点集---标志已经找到最短路径的顶点集
    int s[num_vertices];

    //更新邻接矩阵信息
    ConvertToMatrix(graph);
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = (int) graph.adj_matrix[v][i];
        s[i] = 0;
        //只要两点之间不是不可达，暂记其余顶点的前一个顶点为v
        if (i != v && dist[i] < INFINITY)
            path[i] = v;
        else
            path[i] = -1;
    }
    //顶点v加入顶点集合
    s[v] = 1;
    dist[v] = 0;
    //选择当前不在集合S中具有最短路径的顶点u
    for (int i = 0; i < num_vertices - 1; i++) {
        int min = INFINITY;
        int u = v;
        //找一个当前所有可达路径中花费最小的顶点u
        for (int j = 0; j < num_vertices; j++)
            if (!s[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        //将顶点u加入集合s
        s[u] = 1;
        for (int k = 0; k < num_vertices; k++)//修改
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
    cout << "结束" << endl;
    cout << endl << "最短距离为  " << dist[w] << endl;

}

//使用Prim算法生成最小生成树
void Prim(Graph &graph, int v) {
    //图中的顶点数
    int num_vertices = graph.num_vertices;
    //记录最小花费
    int *low_cost = new int[num_vertices];
    //记录顶点的相邻节点
    int *near_vex = new int[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        //记录顶点v到各点的代价
        if (i != v) {
            low_cost[i] = graph.adj_matrix[v][i];
            near_vex[i] = 0;
        }

    }
    //顶点v加到生成树顶点集合
    near_vex[v] = -1;
    low_cost[v] = 0;
//    cout<<"near_vex[v]=-1;";
    //定义一个最小生成树结点作为辅助单元
    MSTEdgeNode e;
    //存储生成树边的数组
    MSTEdgeNode *edgeNode = new MSTEdgeNode[num_vertices - 1];
    for (int i = 1; i < num_vertices; i++) {
        //循环num_vertices-1次，加入num_vertices-1边
        int min = INFINITY;
        int temp = 0;
        for (int j = 0; j < num_vertices; j++)
            if (near_vex[j] != -1 && low_cost[j] < min) {
                temp = j;
                min = low_cost[j];
            }
        //求生成树以外的顶点到生成树内部的顶点所具有的最小权值的边，temp是当前具有最小权值边的位置
        if (temp) {//temp==0表示再也找不到符合要求的顶点了
            e.tail = near_vex[temp];
            e.head = temp;
            e.cost = low_cost[temp];
            edgeNode[i - 1] = e;//将选出的边加入生成树中
            near_vex[temp] = -1;//将改变标记已经加入到生成树中
            for (int j = 1; j < num_vertices; j++)
                if (near_vex[j] != -1 && graph.adj_matrix[temp][j] < low_cost[j]) {//如果边不在生成树中则需要进行修改
                    low_cost[j] = graph.adj_matrix[temp][j];
                    near_vex[j] = temp;
                }
        }
    }


    //输出最小生成树的结果
//    cout<<"输出最小生成树的结果";
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
        cout << "从   " << start << "\t" << "修一条到    " << departure << "\t" << "的道路 " << endl;
    }
    cout << "修建路程的总代价为   " << total_cost << endl;

}

//冒泡排序---形参改一下，改成名称和权值的数组---》没必要，数组下标代表景点名称
void BubbleSort(SortNode sortNodes[], int size) {

    cout << "size= " << size << endl;

    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if (sortNodes[j].value < sortNodes[j + 1].value) {
                Swap(sortNodes[j], sortNodes[j + 1]);
            }

}

//快速排序
void QuickSort(SortNode sortNode[], int left, int right) {
    if (left < right) {
        //划分
        int pivot = Partition(sortNode, left, right);
        //在左自取件递归进行快速排序
        QuickSort(sortNode, left, pivot - 1);
        //在右子区间递归进行快速排序
        QuickSort(sortNode, pivot + 1, right);
    }
}

//快速排序的辅助函数
int Partition(SortNode sortNode[], int left, int right) {
    //取最左边的数为排序的基准
    int pivot = left;
    Swap(sortNode[left], sortNode[(left + right) / 2]);
    SortNode standard = sortNode[left];
    for (int i = left + 1; i <= right; i++)
        if (sortNode[i].value > standard.value && ++pivot != i)
            Swap(sortNode[pivot], sortNode[i]);
    Swap(sortNode[left], sortNode[pivot]);
    return pivot;
}

//交换两个数
void Swap(SortNode &node1, SortNode &node2) {
    SortNode temp = node2;
    node2 = node1;
    node1 = temp;
}

//归并排序
void MergeSort(int popular_degree[][2], int size) {

}

//使用KMP算法进行查找关键字的查找
int KMPSearch(char target[], char pattern[]) {
    int prefix[256];
    int target_length = 0;
    int pattern_length = 0;

//    cout<<"进入KMP主算法"<<endl;
    //计算两个数组的长度
    while ('\0' != target[target_length])
        target_length++;
    while ('\0' != pattern[pattern_length])
        pattern_length++;

    //计算关键字的前缀数组
    CptPfFunc(pattern, prefix);

    //已经匹配的字符个数
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

//计算模式串前缀的函数
void CptPfFunc(char pattern[], int prefix[]) {
    int length_pattern = 0;
    //计算模式串的长度
    while ('\0' != pattern[length_pattern])
        length_pattern++;

    int length_longest_prefix = 0;
    //prefix数组下标从0开始，因为已经匹配个字符串没有任何意义
    prefix[1] = 0;
    //nocm表示匹配的字符串长度
    for (int nocm = 2; nocm < length_pattern + 1; nocm++) {
        while (length_longest_prefix > 0 && (pattern[length_longest_prefix] != pattern[nocm - 1]))
            length_longest_prefix = prefix[length_longest_prefix];
        if (pattern[length_longest_prefix] == pattern[nocm - 1])
            length_longest_prefix++;
        prefix[nocm] = length_longest_prefix;
    }
}


//新的KMP前缀创建
void get_next(char *t, int next[]) {
    int t_len = strlen(t);
    int i = 0;         //求解每个next[i]
    next[0] = -1; //递推基本条件,然后求解next[i+1]
    int j = -1;     //向后递推位置下标
    /*
    next[i]=k =>T0...Tk-1=Ti-k...Ti-1
       求解next[i+1]
    1> 如果T0..Tk-1Tk=Ti-k...Ti-1Ti=>next[i+1]=k+1=next[i]+1;
    2>Tk<>Ti,next[k]=k', 如果Ti=Tk'=>next[i+1]=k'+1=next[k]+1=next[next[i]]+1;
    3>依次递推 最后情况next[i+1]=next[0]+1=0,即
    */
    while (i < t_len) {
        if (j == -1 || t[i] == t[j])  //j==-1证明已经与t[0]不匹配了，此时next[i+1]=0
        {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

//KMP主算法
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