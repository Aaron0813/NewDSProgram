//
// Created by Aaron on 2016/11/14.
//

#include <cstring>
#include <windows.h>
#include <stdio.h>
#include "function.h"


void ShowMenu(Graph &graph) {
//    Graph tour_graph(12);
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
            LoadGraph(graph, "vertexes.txt", "routes.txt");
            OutputLoadNodeInfo(graph, graph.num_vertices);
            OutputLoadRouteInfo(graph);
//            LoadGraph(graph,"new_vertexes.txt","new_routes.txt");
        } else if ("2" == choose) {
            if (graph.is_created) {
                OutputAdjMatrix(graph);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }

        } else if ("3" == choose) {
            if (graph.is_created) {
                int count = 0;
                string *final_tour_map = CreateTourSortGraph(graph, count);
                OutputTourGraph(final_tour_map, count);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }

        } else if ("4" == choose) {
            if (graph.is_created) {
                FindLoop(new_tour_graph);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }

        } else if ("5" == choose) {
            if (graph.is_created) {
                MiniDistance(graph);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }

        } else if ("6" == choose) {
            if (graph.is_created) {
                MiniSpanTree(graph, "北门");
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }

        } else if ("7" == choose) {
            if (graph.is_created) {
                Sort(graph);
            } else {
                cout << "景区信息还没有录入，请录入后再做操作" << endl;
            }
        } else if ("8" == choose) {
            if (graph.is_created) {
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
void LoadGraph(Graph &graph, string vertex_txt, string route_txt) {
    //存入节点信息
    ifstream inf1(vertex_txt.c_str());
    int i = 0, j;
    while (inf1.good()) {
        ////不能够直接通过引用写入数据，待查---已改正，数组越界
        inf1 >> graph.node_table[i].name >> graph.node_table[i].description >> graph.node_table[i].popular_degree
             >> graph.node_table[i].is_toilet >> graph.node_table[i].is_rest;
        //困扰了很久，原来是因为一开始地址没有对其进行初始化
        graph.node_table[i].adj = NULL;
        i++;
    }
    inf1.close();

    /**
     * 测试节点信息是否存入正确*/


    //存入路径信息
//    filename = "routes.txt";
//    filename = "new_routes.txt";
    ifstream inf2(route_txt.c_str());
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
        /**段错误的缘由应该在这里
         * */
        P->link = graph.node_table[i].adj;//第一次P被复制为NULL，但后面几次就会不断的加到结点的前面
        graph.node_table[i].adj = P;

        Q->link = graph.node_table[j].adj;
        graph.node_table[j].adj = Q;
        graph.num_edges++;
    }

    inf2.close();
}

//输出存储之后的节点信息
void OutputLoadNodeInfo(Graph &graph, int n) {
    cout << "景点信息录入成功:" << endl;
    for (int m = 0; m < n; m++) {
        cout << m << "\t" << (graph.node_table[m].name) << "\t" << (graph.node_table[m].description) << "\t" << endl;
    }
}

//输出存储之后的路径信息
void OutputLoadRouteInfo(Graph &graph) {
    cout << endl << endl << "路径信息录入成功,以下为相邻景点的信息:" << endl;
    int num_vertices = graph.num_vertices;
    Edge *edge;
    int temp;
    for (int i = 0; i < num_vertices; i++) {
        cout << graph.node_table[i].name << "\t";
        for (edge = graph.node_table[i].adj; edge->link != NULL; edge = edge->link) {//遍历某一个节点的所有邻接节点信息
            temp = edge->dest;
            cout << graph.node_table[temp].name << "\t";
        }
        cout << endl;

    }
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
string *CreateTourSortGraph(Graph &graph, int &count) {
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
//     count = 0;
    //建立导游路线图
    for (int i = 0; i < graph.num_vertices - 1; i++) {
        if (IsEdge(graph, vex[i], vex[i + 1])) {//如果两个顶点之间有边，那么直接将这两个顶点存入路线数组中
            if (i != graph.num_vertices - 2) {
                tour_map[count++] = vex[i];

            } else {
                tour_map[count++] = vex[i];
                tour_map[count++] = vex[i + 1];
            }
        } else {
            int temp_i = i;
            //存入仙武湖
            tour_map[count++] = vex[i];
            while (!IsEdge(graph, vex[--temp_i], vex[i + 1])) {//只要两个顶点之间没有边
                tour_map[count++] = vex[temp_i];//将前一个顶点加入到导游了路线图中
            }
            tour_map[count++] = vex[temp_i];
        }
    }
    string *final_tour_map = new string[count];
    for (int i = 0; i < count; i++)
        final_tour_map[i] = tour_map[i];
    /* 输出导游路线图*/

//    cout<<"新数组大小为：  "<<count<<endl;
    return final_tour_map;

}

//输出导游路线图
void OutputTourGraph(string tour_map[], int n) {
    cout << "导游路线图结果" << endl;
    for (int m = 0; m < n; m++) {
        cout << tour_map[m] << "->";
    }
    cout << "结束" << endl << endl << endl;
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
    //加载新图
    LoadGraph(graph, "new_vertexes.txt", "new_routes.txt");
    int count = 0;
    string *final_tour_map = CreateTourSortGraph(graph, count);
    for (int i = 0; i < count; i++)
        cout << final_tour_map[i] << "->";
    cout << "结束" << endl;
    stack<string> temp;
    for (int j = 1; j < count - 1; j++) {
        if (final_tour_map[j - 1] == final_tour_map[j + 1]) {
            string start = final_tour_map[j];
            temp.push(start);
            for (int m = j + 1; m < count; m++) {
                string endView = final_tour_map[m];
                if (IsEdge(graph, start, endView)) {
                    temp.push(endView);
                }
            }
        }
    }
    cout << "回路为 ：" << endl << endl;
    while (!temp.empty()) {
        cout << temp.top() << "   ";
        temp.pop();
    }
    cout << endl;
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


//生成最小生成树
void MiniSpanTree(Graph &graph, string u) {
    //获取起始点在图中链表的位置
    int v = GetVertexPos(graph, u);
//    cout<<" 最小生成树的起点"<<v<<endl;
    //更新邻接矩阵信息---该算法要求邻接矩阵必须先被创建，否则不能执行程序
    ConvertToMatrix(graph);
    Prim(graph, v);

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
}

void Park() {
    CarStack parking_stack, temp_parking_stack;
    CarQueue waiting_queue;
    StackInit(parking_stack);
    StackInit(temp_parking_stack);
    QueueInit(waiting_queue);
    bool flag = true;
    while (flag) {
        string choose;
        cout << "**             ** 停车场管理程序                 **" << endl;
        cout << "===================================================" << endl;
        cout << "**                                               **" << endl;
        cout << "**   A --- 汽车 进 车场   D --- 汽车 出 车场     **" << endl;
        cout << "**                                               **" << endl;
        cout << "**           E --- 退出   程序                   **" << endl;
        cout << "===================================================" << endl;
        cout << "请选择 :(A,D,E): ";
        cin >> choose;
        if ("A" == choose) {
            EnterParking(parking_stack, waiting_queue);
        } else if ("D" == choose) {
            DepartParking(parking_stack, temp_parking_stack, waiting_queue);
        } else if ("E" == choose) {
            flag = false;
        } else {
            cout << "输入有误，请重新输入" << endl;
        }
    }
}


