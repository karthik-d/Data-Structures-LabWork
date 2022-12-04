#include "GraphADT.h"
#include "GraphADTImpl.h"

void main(){
    Vertex *graph1 = NULL;
    graph1 = addVertex(graph1, 'A');
    graph1 = addVertex(graph1, 'B');
    graph1 = addVertex(graph1, 'C');
    graph1 = addVertex(graph1, 'D');
    graph1 = addVertex(graph1, 'E');
    addEdge(graph1, 'A', 'B');
    addEdge(graph1, 'B', 'A');
    addEdge(graph1, 'A', 'C');
    addEdge(graph1, 'C', 'A');
    addEdge(graph1, 'A', 'E');
    addEdge(graph1, 'E', 'A');
    addEdge(graph1, 'B', 'E');
    addEdge(graph1, 'E', 'B');
    addEdge(graph1, 'B', 'D');
    addEdge(graph1, 'D', 'B');

    printf("GRAPH 1\n\nDEPTH FIRST SEARCH");
    DepthFirstSearch(graph1, 'A', 1);
    printf("\n\nBREADTH FIRST SEARCH");
    BreadthFirstSearch(graph1, 'A', 1);

    Vertex *graph2 = NULL;
    graph2 = addVertex(graph2, 0);
    graph2 = addVertex(graph2, 1);
    graph2 = addVertex(graph2, 2);
    graph2 = addVertex(graph2, 3);
    graph2 = addVertex(graph2, 4);
    addEdge(graph2, 0, 1);
    addEdge(graph2, 1, 2);
    addEdge(graph2, 2, 4);
    addEdge(graph2, 2, 3);
    addEdge(graph2, 3, 0);
    addEdge(graph2, 4, 2);

    printf("\n\nGRAPH 2\n\nDEPTH FIRST SEARCH");
    DepthFirstSearch(graph2, 0, 0);
    printf("\n\nBREADTH FIRST SEARCH");
    BreadthFirstSearch(graph2, 0, 0);

    Vertex *graph3 = NULL;
    graph3 = addVertex(graph3, 'A');
    graph3 = addVertex(graph3, 'B');
    graph3 = addVertex(graph3, 'C');
    graph3 = addVertex(graph3, 'D');
    graph3 = addVertex(graph3, 'E');
    graph3 = addVertex(graph3, 'F');
    graph3 = addVertex(graph3, 'G');
    graph3 = addVertex(graph3, 'H');
    addEdge(graph3, 'A', 'D');
    addEdge(graph3, 'A', 'C');    
    addEdge(graph3, 'A', 'B');
    addEdge(graph3, 'B', 'E');
    addEdge(graph3, 'B', 'C');
    addEdge(graph3, 'C', 'E');
    addEdge(graph3, 'D', 'F');
    addEdge(graph3, 'D', 'C');
    addEdge(graph3, 'E', 'A');
    addEdge(graph3, 'F', 'C');
    addEdge(graph3, 'G', 'H');
    addEdge(graph3, 'G', 'F');
    addEdge(graph3, 'G', 'D');
    addEdge(graph3, 'H', 'C');

    printf("\n\nGRAPH 3\n\nDEPTH FIRST SEARCH");
    DepthFirstSearch(graph3, 'A', 1);
    printf("\n\nBREADTH FIRST SEARCH");
    BreadthFirstSearch(graph3, 'A', 1);
}
