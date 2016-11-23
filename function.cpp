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
        cout << "    欢迎使用景区管理系统    " << endl;
        cout << "       **请选择菜单**       " << endl;
        cout << "============================" << endl;
        cout << "1.创建景区景点分布图" << endl;
        cout << "2.输出景区景点分布图" << endl;
        cout << "3.输出导游线路图" << endl;
        cout << "4.输出导游线路图中的回路" << endl;
        cout << "5.求两个景点间最短路径和最短距离" << endl;
        cout << "6.输出道路修建规划图" << endl;
        cout << "7.景点排序" << endl;
        cout << "8.景点搜索" << endl;
        cout << "9.停车场管理" << endl;
        cout << "10.退出系统" << endl;
        cin >> choose;
        if ("1" == choose) {
            LoadGraph(graph);
        } else if ("2" == choose) {
            if (graph.is_created == true) {
                OutputAdjMatrix(graph);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }

        } else if ("3" == choose) {
            if (graph.is_created == true) {
                CreateTourSortGraph(graph);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }

        } else if ("4" == choose) {
            if (graph.is_created == true) {
                FindLoop(new_tour_graph);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }

        } else if ("5" == choose) {
            if (graph.is_created == true) {
                MiniDistance(graph);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }

        } else if ("6" == choose) {
            if (graph.is_created == true) {
                MiniSpanTree(graph, "北门");
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }

        } else if ("7" == choose) {
            if (graph.is_created == true) {
                Sort(graph);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }
        } else if ("8" == choose) {
            if (graph.is_created == true) {
                Search(graph);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }
        } else if ("9" == choose) {
            Park();
        } else if ("10" == choose) {
            cout << "成功退出程序" << endl;
            exit(0);
        } else {
            cout << "输入错误，请重新输入" << endl;
//            cout<<"按下任意键继续"<<endl;
//            cin>>choose;
        }
    }
}

/**
 * 加载图的相关信息
 * @param graph
 */
void LoadGraph(Graph &graph) {
    //存入节点信息
    string filename = "vertexes.txt";
//    string filename = "new_vertexes.txt";
    ifstream inf1(filename.c_str());
    int i = 0, j;
    while (inf1.good()) {
        ////不能够直接通过引用写入数据，待查---已改正，数组越界
        inf1 >> graph.node_table[i].name >> graph.node_table[i].description >> graph.node_table[i].popular_degree
             >> graph.node_table[i].is_toilet >> graph.node_table[i].is_rest;
        i++;
    }
//    graph.num_vertices=i+1;
    inf1.close();

    /**
     * 测试节点信息是否存入正确*/
    cout << "景点信息录入成功:" << endl;
    for (int m = 0; m < i; m++) {
        cout << m << "\t" << (graph.node_table[m].name) << "\t" << (graph.node_table[m].description) << "\t" << endl;
    }

    //存入路径信息
    filename = "routes.txt";
//    filename = "new_routes.txt";
    ifstream inf2(filename.c_str());
    string from, to;
    int timeFee = 0, distance = 0;
    while (inf2.good()) {
        inf2 >> from >> to >> distance >> timeFee;

        //查找顶点所在数组中的位置
        i = GetVertexPos(graph, from);
        j = GetVertexPos(graph, to);
        //创建边信息并赋值
        Edge *P = new Edge(j, distance, timeFee);
        Edge *Q = new Edge(i, distance, timeFee);
        P->link = graph.node_table[i].adj;//第一次P被复制为NULL，但后面几次就会不断的加到结点的前面
        graph.node_table[i].adj = P;

        Q->link = graph.node_table[j].adj;
        graph.node_table[j].adj = Q;
        graph.num_edges++;
    }

    inf2.close();


    /**
      * 测试路径信息是否存入正确--应该是正确的-----一定要注意相关的编码要统一啊*/
    cout << endl << endl << "路径信息录入成功,以下为相邻景点的信息:" << endl;
//    for (int m = 0; m < graph.num_vertices; m++) {
//        cout << (graph.node_table[m].adj->dest) << " " << (graph.node_table[m].adj->distance) << endl;
//        }

//    cout << "111  num vertexes   " << graph.num_vertices << endl;
    int num_vertices = graph.num_vertices;
    Edge *edge;
    for (i = 0; i < num_vertices; i++) {
        cout << graph.node_table[i].name << "\t";
        for (edge = graph.node_table[i].adj; edge; edge = edge->link) {//遍历某一个节点的所有邻接节点信息
            cout << graph.node_table[edge->dest].name << "\t";
        }
        cout<<endl;
    }
    ///////////////////////////////////////////////
//    cout<<graph.node_table[5].name<<endl;
//    Edge *edge;
//    for(edge=graph.node_table[5].adj;edge;edge=edge->link){//遍历某一个节点的所有邻接节点信息
//            cout<<graph.node_table[edge->dest].name<<"  ";
//        }
//    cout<<"end"<<endl;

    //标记图已经被成功创建
    graph.is_created = true;
    cout << endl << endl << "图已经创建成功" << endl;

}


//输出邻接矩阵的信息
void OutputAdjMatrix(Graph &graph) {

    ConvertToMatrix(graph);
    int num_vertices = graph.num_vertices;
    /**
     * 测试输出邻接矩阵的信息是否正确*/

    for (int i = 0; i < num_vertices; ++i)//打印第一行
        cout << "\t" << graph.node_table[i].name;
    cout << endl;

    for (int i = 0; i < num_vertices; i++) {
        cout << graph.node_table[i].name << "\t";//打印左侧的表头
        for (int j = 0; j < num_vertices; j++)
            cout << graph.adj_matrix[i][j] << "\t";
        cout << endl;
    }
}



//输出导游路线图
void CreateTourSortGraph(Graph &graph) {
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
    int n = 0;
    //建立导游路线图
    for (int i = 0; i < graph.num_vertices - 1; i++) {
        if (IsEdge(graph, vex[i], vex[i + 1])) {//如果两个顶点之间有边，那么直接将这两个顶点存入路线数组中
            if (i != graph.num_vertices - 2) {
                tour_map[n++] = vex[i];

            } else {
                tour_map[n++] = vex[i];
                tour_map[n++] = vex[i + 1];
            }
        } else {
            int temp_i = i;
            //存入仙武湖
            tour_map[n++] = vex[i];
            while (!IsEdge(graph, vex[--temp_i], vex[i + 1])) {//只要两个顶点之间没有边
                tour_map[n++] = vex[temp_i];//将前一个顶点加入到导游了路线图中
            }
            tour_map[n++] = vex[temp_i];
        }
    }

    /**
     * 测试导游路线图是否正确*/

//    cout << "运行结束,n=" << n << endl;
    cout << "导游路线图结果" << endl;
    for (int m = 0; m < n; m++) {
        cout << tour_map[m] << "->";
    }
    cout << "结束" << endl << endl << endl;
//    CreateTourGraph(graph, tour_graph, tour_map);

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


    cout << "找出回路成功" << endl;
}

void MiniDistance(Graph &graph) {
    string start_view, end_view;
    cout << "请输入要查找的两个景点名称" << endl;

    int v, w;
    while (true) {
        cout << "请输入起点名称" << endl;
        cin >> start_view;
        v = GetVertexPos(graph, start_view);
        if (v == -1)
            cout << "起点不存在，请重新输入" << endl;
        else
            break;
    }
    while (true) {
        cout << "请输入终点名称" << endl;
        cin >> end_view;
        w = GetVertexPos(graph, end_view);
        if (w == -1)
            cout << "终点不存在，请重新输入" << endl;
        else
            break;
    }
    //运用Dijkstra算法计算两点之间的最短路径及其距离花费
    if (v == w) {
        cout << "起点与终点相同，均为" << start_view << endl;
    } else
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

//生成最小生成树
void MiniSpanTree(Graph &graph, string u) {
    //获取起始点在图中链表的位置
    int v = GetVertexPos(graph, u);
//    cout<<" 最小生成树的起点"<<v<<endl;
    //更新邻接矩阵信息---该算法要求邻接矩阵必须先被创建，否则不能执行程序
    ConvertToMatrix(graph);
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

//排序功能的主函数入口
void Sort(Graph &graph) {
    bool flag = true;
    string choose;
    while (flag) {
        cout << "1.根据景点欢迎度排序" << endl;
        cout << "2.根据景点岔路数排序" << endl;
        cout << "3.返回主菜单" << endl;
        cout << "      请选择" << endl;
        cin >> choose;
        if ("1" == choose) {
            SortByPopularDegree(graph);
        } else if ("2" == choose) {
            SortByForks(graph);
        } else if ("3" == choose) {
            flag = false;
            ShowMenu(graph);
        } else {
            cout << "输入有误，请重新输入" << endl;
        }
    }
}

//根据欢迎度排序
void SortByPopularDegree(Graph &graph) {
    //获取图中欢迎度的数据及其下标
    SortNode sortNodes[graph.num_vertices];
    for (int i = 0; i < graph.num_vertices; i++) {
        sortNodes[i].value = graph.node_table[i].popular_degree;
        sortNodes[i].name = graph.node_table[i].name;
    }

    string choose;
    cout << "1.冒泡排序" << endl;
    cout << "2.快速排序" << endl;
//    cout << "3.归并排序" << endl;
    cout << "  请选择" << endl;
    cin >> choose;
    if ("1" == choose) {
        BubbleSort(sortNodes, graph.num_vertices);
        cout << "针对景点受欢迎程度进行冒泡排序的结果为：" << endl;
        OutputSortResult(graph, sortNodes);
    } else if ("2" == choose) {
        QuickSort(sortNodes, 0, 11);
        cout << "针对景点受欢迎程度进行冒泡排序的结果为：" << endl;
        OutputSortResult(graph, sortNodes);
    }
// else if("3"==choose){
//        MergeSort(popular_degree);
//    }
    else {
        cout << "输入有误，请重新输入" << endl;
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

    string choose;
    cout << "1.冒泡排序" << endl;
    cout << "2.快速排序" << endl;
//    cout << "3.归并排序" << endl;
    cout << "  请选择" << endl;
    cin >> choose;
    if ("1" == choose) {
        BubbleSort(sortNodes, graph.num_vertices);
        cout << "针对景点岔路数进行快速排序的结果为：" << endl;
        OutputSortResult(graph, sortNodes);
    } else if ("2" == choose) {
        QuickSort(sortNodes, 0, 11);
        cout << "针对景点岔路数进行快速排序的结果为：" << endl;
        OutputSortResult(graph, sortNodes);
    }
// else if("3"==choose){
//        MergeSort(popular_degree);
//    }
    else {
        cout << "输入有误，请重新输入" << endl;
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


void OutputSortResult(Graph &graph, SortNode sortNodes[]) {
    cout << "景点名称\t" << "景点岔路数\t" << endl;
    for (int i = 0; i < graph.num_vertices; i++)
        cout << sortNodes[i].name << "\t\t" << sortNodes[i].value << endl;
}

//查找的主函数---输入一个字符串，使用KMP分别遍历景点的名称以及景点的描述
void Search(Graph &graph) {
    string key_word;
    char target[2048];
    memset(target, 0, 2048);
    char pattern[2048];
    memset(pattern, 0, 2048);
    cout << "请输入要查找的关键字" << endl;
    cin >> key_word;
    /**
     * 原来的程序*/

    strcpy(pattern, key_word.c_str());

    //遍历所有景点的名称以及其简介
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
        cout << "未查找到所要信息，请重新输入" << endl;



    /**
     * 新的代码
     */
//    cout<<"pattern 为"<<pattern<<endl;
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
//        cout << "未查找到所要信息，请重新输入" << endl;

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


