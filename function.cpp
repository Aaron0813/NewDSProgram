//
// Created by Aaron on 2016/11/14.
//

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

    for(int j=0;j<i;j++)
        cout<<(graph.node_table[j].name)<<" "<<(graph.node_table[j].description)<<endl;
    */


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

    //输出邻接矩阵的信息
    for (int i = 0; i < num_vertices; ++i)//打印第一行
        cout << "\t" << graph.node_table[i].name;
    cout << endl;

    for (i = 0; i < num_vertices; i++) {
        cout << graph.node_table[i].name << "\t";//打印左侧的表头
        for (j = 0; j < num_vertices; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
    delete[]edge;
}

//输出导游路线图
void CreateTourSortGraph(Graph &graph, Graph &tour_graph) {
    string *vex = DFSTraverse(graph);

    /**
     * 测试深度优先遍历结果
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
        cout << "IsEdge(graph," << vex[i] << "," << vex[i + 1] << ") " << IsEdge(graph, vex[i], vex[i + 1]) << "  "
             << "i=  " << i << endl;
        if (IsEdge(graph, vex[i], vex[i + 1])) {//如果两个顶点之间有边，那么直接将这两个顶点存入路线数组中
            if (i != graph.num_vertices - 2) {
                tour_map[n++] = vex[i];

            } else {
                tour_map[n++] = vex[i];
                tour_map[n++] = vex[i + 1];
                cout << "vex[i+1]" << vex[i + 1] << endl;

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