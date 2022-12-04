#include "GraphADT.h"
#include "GraphADTImpl.h"

void main(){
    Graph *graph1 = createNewGraph();
    addVertex(graph1, 'A');
    addVertex(graph1, 'B');
    addVertex(graph1, 'C');
    addVertex(graph1, 'D');
    addVertex(graph1, 'E');
    addVertex(graph1, 'F');
    addVertex(graph1, 'G');
    addEdge(graph1, 'A', 'B', 2);
    addEdge(graph1, 'A', 'D', 1);
    addEdge(graph1, 'B', 'D', 3);
    addEdge(graph1, 'B', 'E', 10);
    addEdge(graph1, 'C', 'A', 4);
    addEdge(graph1, 'C', 'F', 5);
    addEdge(graph1, 'D', 'C', 2);
    addEdge(graph1, 'D', 'E', 2);
    addEdge(graph1, 'D', 'F', 8);
    addEdge(graph1, 'D', 'G', 4);
    addEdge(graph1, 'E', 'G', 6);
    addEdge(graph1, 'G', 'F', 1);
    printf("\nGRAPH 1: Distance Table");
    performDijkstra(graph1, 'A', 1);

    Graph *graph2 = createNewGraph();
    addVertex(graph2, 1);
    addVertex(graph2, 2);
    addVertex(graph2, 3);
    addVertex(graph2, 4);
    addVertex(graph2, 5);
    addVertex(graph2, 6);
    addEdge(graph2, 1, 2, 5);
    addEdge(graph2, 2, 1, 5);
    addEdge(graph2, 1, 4, 6);
    addEdge(graph2, 4, 1, 6);
    addEdge(graph2, 1, 5, 10);
    addEdge(graph2, 5, 1, 10);
    addEdge(graph2, 2, 3, 1);
    addEdge(graph2, 3, 2, 1);
    addEdge(graph2, 2, 6, 7);
    addEdge(graph2, 6, 2, 7);
    addEdge(graph2, 2, 5, 2);
    addEdge(graph2, 5, 2, 2);
    addEdge(graph2, 3, 6, 8);
    addEdge(graph2, 6, 3, 8);
    addEdge(graph2, 4, 5, 3);
    addEdge(graph2, 5, 4, 3);
    addEdge(graph2, 5, 6, 4);
    addEdge(graph2, 6, 5, 4);
    printf("\n\nGRAPH 2: Distance Table");
    performDijkstra(graph2, 1, 0);
    printf("\n");
}
