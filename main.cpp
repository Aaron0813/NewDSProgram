#include <iostream>
#include "preDefine.h"
int main() {
    Graph graph(12), tour_graph(12);
    ShowMenu();
    LoadGraph(graph);
    OutputAdjMatrix(graph);
    CreateTourSortGraph(graph, tour_graph);
    SortByPopularDegree(graph);
//    MiniDistance(graph);
//    MiniSpanTree(graph,"����");

//    cout<<"size ��СΪ"<<vex->size()<<endl;//Ϊʲôsize��СΪ4
//    for(int i=0;i<graph.num_vertices;i++)
//        cout<<vex[i]<<"-->";
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}