#include <iostream>
#include "preDefine.h"

int main() {
    Graph graph(12), tour_graph(12);
//    ShowMenu();
    LoadGraph(graph);
    OutputAdjMatrix(graph);
    CreateTourSortGraph(graph, tour_graph);
//    SortByPopularDegree(graph);
//    MiniDistance(graph);
//    MiniSpanTree(graph,"±±√≈");
//    SortByForks(graph);

    Search(graph);
    return 0;
}