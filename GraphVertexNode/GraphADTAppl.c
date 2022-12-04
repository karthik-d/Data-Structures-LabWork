#include "GraphADT.h"
#include "GraphADTImpl.h"

void main(){
  Graph *graph1 = createGraph();
  addVertex(graph1, 'A');
  addVertex(graph1, 'B');
  addVertex(graph1, 'C');
  addVertex(graph1, 'D');
  addVertex(graph1, 'E');
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

  printf("GRAPH 1\n\nDEPTH FIRST SEARCHn");
  DFS(graph1, 'A');
  printf("\n\nBREADTH FIRST SEARCH\n");
  BFS_Driver(graph1, 'A');

  Graph *graph2 = createGraph();
  addVertex(graph2, 0);
  addVertex(graph2, 1);
  addVertex(graph2, 2);
  addVertex(graph2, 3);
  addVertex(graph2, 4);
  addEdge(graph2, 0, 1);
  addEdge(graph2, 1, 2);
  addEdge(graph2, 2, 4);
  addEdge(graph2, 2, 3);
  addEdge(graph2, 3, 0);
  addEdge(graph2, 4, 2);

  printf("\n\nGRAPH 2\n\nDEPTH FIRST SEARCHn");
  DFS(graph2, 0);
  printf("\n\nBREADTH FIRST SEARCHn");
  BFS(graph2, 0);
}
