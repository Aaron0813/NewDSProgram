//
// Created by Aaron on 2016/11/14.
//

#include <cstring>
#include "preDefine.h"

void ShowMenu() {
    cout << "============================" << endl;
    cout << "    欢迎使用景区管理系统    " << endl;
    cout << "       **请选择菜单**       " << endl;
    cout << "============================" << endl;
    cout << "1.创建景区景点分布图" << endl;
    cout << "2.输出景区景点分布图" << endl;
    cout << "3.输出导游线路图" << endl;
    cout << "4.输出导游线路图中的回路" << endl;
    cout << "5.求两个景点间最短路径和最短距离" << endl;
    cout << "6.输出道路修建规划图" << endl;
    cout << "7.停车场车辆进出信息" << endl;
    cout << "8.退出系统" << endl;
}

//加载图的相关信息
void LoadGraph(Graph &graph) {
    //存入节点信息
    string filename = "vertexes.txt";
    ifstream inf1(filename.c_str());
    string name, description;
    int popular_degree = 0, is_toilet = 0, is_rest = 0;
    int i = 0, j;
    while (inf1.good()) {
        //不能够直接通过引用写入数据，待查
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
     * 测试节点信息是否存入正确

    for (int m = 0; m < i; m++) {
        cout << m << "  " << (graph.node_table[m].name) << " " << (graph.node_table[m].description) << endl;
    }
*/
//        cout<<j<<"  "<<(graph.node_table[j].name)<<" "<<(graph.node_table[j].description)<<endl;



    //存入路径信息
    filename = "routes.txt";
    ifstream inf2(filename.c_str());
    string from, to;
    int timeFee = 0, distance = 0;
    while (inf2.good()) {
        inf2 >> from >> to >> distance >> timeFee;
//        cout<<from<<"  "<<to<<"  "<<distance<<"  "<<timeFee<<endl;
        //查找顶点所在数组中的位置
        i = GetVertexPos(graph, from);
        j = GetVertexPos(graph, to);
        //创建边信息并赋值
        Edge *P = new Edge(j, distance, timeFee);
        Edge *Q = new Edge(i, distance, timeFee);
        P->link = graph.node_table[i].adj;//第一次P被复制为NULL，但后面几次就会不断的加到纠结点的前面
        graph.node_table[i].adj = P;

        Q->link = graph.node_table[j].adj;
        graph.node_table[j].adj = Q;
        graph.num_edges++;
    }
//    cout<<"边数为  "<<graph.num_edges<<endl;
    inf2.close();
    /**
      * 测试路径信息是否存入正确--应该是正确的-----一定要注意相关的编码要统一啊
        for(int m=0;m<graph.num_vertices;m++)
        cout<<(graph.node_table[m].adj->dest)<<" "<<(graph.node_table[m].adj->distance)<<endl;

    int num_vertices=graph.num_vertices;
    Edge *edge;
    for(i=0;i<num_vertices;i++){
        cout<<graph.node_table[i].name<<"  ";
        for(edge=graph.node_table[i].adj;edge;edge=edge->link){//遍历某一个节点的所有邻接节点信息
            cout<<graph.node_table[edge->dest].name<<"  ";
        }
        cout<<endl;
    }
    cout<<"end"<<endl;
 */
}

int GetVertexPos(Graph &graph, string &name) {
    for (int i = 0; i < graph.num_vertices; i++)
        if (name == graph.node_table[i].name)//找到了要查找的顶点
            return i;
    return -1;//没找到，返回-1
}

void OutputAdjMatrix(Graph &graph) {
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
//    cout<<"转换成功"<<endl;


    /**
     * 测试输出邻接矩阵的信息是否正确

    for (int i = 0; i < num_vertices; ++i)//打印第一行
        cout << "\t" << graph.node_table[i].name;
    cout << endl;

    for (i = 0; i < num_vertices; i++) {
        cout << graph.node_table[i].name << "\t";//打印左侧的表头
        for (j = 0; j < num_vertices; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
     */
    delete[]edge;
}

//输出导游路线图
void CreateTourSortGraph(Graph &graph, Graph &tour_graph) {
    string *vex = DFSTraverse(graph);

    /**
     * 测试深度优先遍历结果
    cout<<"深度优先边路结果"<<endl;
    for (int i = 0; i < graph.num_vertices; i++) {
        cout << vex[i] << "->";
    }
    cout << endl;
    cout<<"深度优先遍历结束"<<endl;
*/
    string tour_map[2 * graph.num_vertices];
//    cout<<"size 大小为"<<tour_map->size()<<endl;//size返回的到底是什么
//    tour_map[0]="1";
//    tour_map[1]="2";
//    tour_map[2]="3";
//    tour_map[3]="4";
//    tour_map[4]="5";
//    tour_map[5]="6";
//    cout<<"size 大小为"<<tour_map->size()<<endl;

    int n = 0;

    //建立导游路线图
    for (int i = 0; i < graph.num_vertices - 1; i++) {
//        cout << "IsEdge(graph," << vex[i] << "," << vex[i + 1] << ") " << IsEdge(graph, vex[i], vex[i + 1]) << "  "
//             << "i=  " << i << endl;
        if (IsEdge(graph, vex[i], vex[i + 1])) {//如果两个顶点之间有边，那么直接将这两个顶点存入路线数组中
            if (i != graph.num_vertices - 2) {
                tour_map[n++] = vex[i];

            } else {
                tour_map[n++] = vex[i];
                tour_map[n++] = vex[i + 1];
//                cout << "vex[i+1]" << vex[i + 1] << endl;

            }
        } else {
            int temp_i = i;
            //存入仙武湖
            tour_map[n++] = vex[i];
            while (!IsEdge(graph, vex[--temp_i], vex[i + 1])) {//只要两个顶点之间没有边
                tour_map[n++] = vex[temp_i];//将前一个顶点加入到导游了路线图中
//                cout<<"temp_i  "<<temp_i<<"    "<<vex[temp_i]<<endl;
            }
            tour_map[n++] = vex[temp_i];
//            cout<<"temp_i->"<<temp_i<<endl;
        }
    }

    /**
     * 测试导游路线图是否正确

    cout << "运行结束,n=" <<n<< endl;
    cout<<"导游路线图结果"<<endl;
    for (int m = 0; m < n; m++) {
        cout<<tour_map[m]<<"->";
    }
*/
    CreateTourGraph(graph, tour_graph, tour_map);

}

void CreateTourGraph(Graph &graph, Graph &tour_graph, string tour_map[]) {
    //初始化导游图
    for (int i = 0; i < graph.num_vertices; i++) {
        tour_graph.node_table[i].name = graph.node_table[i].name;
        tour_graph.node_table[i].adj = NULL;
    }
    int tour_edges = 0;
//    for()
}

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

//查找一张图所有节点的入度数
void FindInDegree(Graph graph, int indegree[]) {
    Edge *edge = new Edge;
    for (int i = 0; i < graph.num_vertices; i++)
        for (edge = graph.node_table[i].adj; edge; edge = edge->link)
            indegree[edge->dest]++;
    delete edge;
}

//查找一张图中是否有回路
void FindLoop(Graph &graph) {

}

void MiniDistance(Graph &graph) {
    string start_view, end_view;
    cout << "请输入要查找的两个景点名称" << endl;
    cin >> start_view >> end_view;
    int v = GetVertexPos(graph, start_view);
    int w = GetVertexPos(graph, end_view);
    //运用Dijkstra算法计算两点之间的最短路径及其距离花费
    Dijkstra(graph, v, w);
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
    cout << endl << "最短距离为  " << dist[w] << endl;

}

//生成最小生成树
void MiniSpanTree(Graph &graph, string u) {
    //获取起始点在图中链表的位置
    int v = GetVertexPos(graph, u);
//    cout<<" 最小生成树的起点"<<v<<endl;
    Prim(graph, v);

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
    for (int i = 0; i < num_vertices - 1; i++) {
        e = edgeNode[i];
        start = graph.node_table[e.head].name;
        departure = graph.node_table[e.tail].name;
//        cout << e.head << "->" << e.tail << "->" << e.cost << endl;

//        start=(graph.node_table[e.head].name);
        cout << "从  " << start << "  修一条到  " << departure << "的道路  " << endl;
    }

}

//排序功能的主函数入口
void Sort(Graph &graph) {
    int choose;
    cout << "1.根据景点欢迎度排序" << endl;
    cout << "2.根据景点岔路数排序" << endl;
    cout << "      请选择" << endl;
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

//根据欢迎度排序
void SortByPopularDegree(Graph &graph) {
    //获取图中欢迎度的数据及其下标
//    int popular_degree[graph.num_vertices][2];
    SortNode sortNodes[graph.num_vertices];
    for (int i = 0; i < graph.num_vertices; i++) {
//        popular_degree[i][0] = graph.node_table[i].popular_degree;
//        popular_degree[i][1] = i;
        sortNodes[i].value = graph.node_table[i].popular_degree;
        sortNodes[i].name = graph.node_table[i].name;
    }

    int choose;
    cout << "1.冒泡排序" << endl;
    cout << "2.快速排序" << endl;
    cout << "3.归并排序" << endl;
    cout << "  请选择" << endl;
    cin >> choose;
    switch (choose) {
        case 1:
            BubbleSort(sortNodes, graph.num_vertices);
            cout << "针对景点受欢迎程度进行冒泡排序的结果为：" << endl;
            cout << "景点名称\t" << "景点受欢迎度\t" << endl;
            for (int i = 0; i < graph.num_vertices; i++)
                cout << sortNodes[i].name << "\t\t" << sortNodes[i].value << endl;
            break;
        case 2:
            QuickSort(sortNodes, 0, 11);
            cout << "针对景点受欢迎程度进行冒泡排序的结果为：" << endl;
            cout << "景点名称\t" << "景点受欢迎度\t" << endl;
            for (int i = 0; i < graph.num_vertices; i++)
                cout << sortNodes[i].name << "\t\t" << sortNodes[i].value << endl;
            break;
        case 3:
//            MergeSort(popular_degree);
            break;
    }

}

//根据岔路数排序
void SortByForks(Graph &graph) {
    SortNode sortNodes[graph.num_vertices];
    for (int i = 0; i < graph.num_vertices; i++) {
        int j = 0;
        for (Edge *edge = graph.node_table[i].adj; edge; edge = edge->link)
            j++;//记录当前节点的岔路数
        sortNodes[i].value = j;
        sortNodes[i].name = graph.node_table[i].name;
    }


    int choose;
    cout << "1.冒泡排序" << endl;
    cout << "2.快速排序" << endl;
    cout << "3.归并排序" << endl;
    cout << "  请选择" << endl;
    cin >> choose;
    switch (choose) {
        case 1:
            BubbleSort(sortNodes, graph.num_vertices);
            cout << "针对景点岔路数进行快速排序的结果为：" << endl;
            cout << "景点名称\t" << "景点岔路数\t" << endl;
            for (int i = 0; i < graph.num_vertices; i++)
                cout << sortNodes[i].name << "\t\t" << sortNodes[i].value << endl;
            break;
        case 2:
            QuickSort(sortNodes, 0, 11);
            cout << "针对景点岔路数进行快速排序的结果为：" << endl;
            cout << "景点名称\t" << "景点岔路数\t" << endl;
            for (int i = 0; i < graph.num_vertices; i++)
                cout << sortNodes[i].name << "\t\t" << sortNodes[i].value << endl;
            break;
        case 3:
//            MergeSort(popular_degree);
            break;
    }

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

//查找的主函数---输入一个字符串，使用KMP分别遍历景点的名称以及景点的描述
void Search(Graph &graph) {
    string key_word;
    char target[2048];
    memset(target, 0, 2048);
    char pattern[2048];
    memset(pattern, 0, 2048);
//    char pattern2[2014];
    cout << "请输入要查找的关键字" << endl;
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
    //遍历所有景点的名称以及其简介
    int i = 0;
    for (; i < graph.num_vertices; i++) {

        strcpy(pattern, graph.node_table[i].name.c_str());
//        //////////////////////////////////////////
//        int m=0;cout<<"景点名称为 is";
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
//        m=0;cout<<"景点简介为 is";
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
        cout << "未查找到所要信息，请重新输入" << endl;

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

//    cout<<"target_length  "<<target_length<<"   pattern_length  "<<pattern_length<<endl;
//    //////////////////////////////
//    int m=0;cout<<"pattern 的内容 is  ";
//    while('\0'!=pattern[m]){
//        cout<<pattern[m];
//        m++;
//    }


    /////////////////////////////
    //计算关键字的前缀数组
    CptPfFunc(pattern, prefix);
    /////////////////////////////
//     m=1;cout<<"前缀函数 is  ";
//    while('\0'!=prefix[m]){
//        cout<<prefix[m];
//        m++;
//    }
    ////////////////////////
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
//    ///////////////////////////
//    int m=0;cout<<"CptPfFunc   pattern 的内容 is  ";
//    while('\0'!=pattern[m]){
//        cout<<pattern[m];
//        m++;
//    }
//    cout<<"length_pattern is "<<length_pattern<<endl;
    ///////////////////////////////
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

