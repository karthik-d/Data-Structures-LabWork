#include<stdio.h>
#include<stdlib.h>

// GRAPH FUNCTIONS //

Node* createNewNode(int v_index){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->v_index = v_index;
    handle->weight = 0;
    handle->next = NULL;
    return handle;
}

Graph* createNewGraph(){
    Graph *handle = (Graph*)malloc(sizeof(Graph));
    handle->start = NULL;
    handle->num_vertices = 0;
    return handle;
}

void addVertex(Graph *graph, int label){
    Vertex *handle = (Vertex*)malloc(sizeof(Vertex));
    handle->index = graph->num_vertices;
    handle->label = label;
    handle->edges = NULL;   // List of Edges (each is a Node)
    handle->next = graph->start;
    graph->start = handle;
    graph->num_vertices++;
}

Vertex* getVertexFromLabel(Graph *graph, int label){
    Vertex *handle = graph->start;
    while(handle!=NULL){
        if(handle->label==label){
            return handle;
        }
        handle = handle->next;
    }
    return NULL;
}

Vertex* getVertexFromIndex(Graph *graph, int index){
    Vertex *handle = graph->start;
    while(handle!=NULL){
        if(handle->index==index){
            return handle;
        }
        handle = handle->next;
    }
    return NULL;
}

void addEdge(Graph *graph, int from, int to, int weight){
    Vertex *source = getVertexFromLabel(graph, from);
    Node *destn = createNewNode(getVertexFromLabel(graph, to)->index);
    destn->weight = weight;
    destn->next = source->edges;      // Insert new edge at beginning of Edges List
    source->edges = destn;
}

// Dijkstra's Algorithm

Table* initializeTable(Graph *graph, int start_label){
    Table *pathtable = (Table*)malloc(sizeof(Table)*graph->num_vertices);
    for(int i=0;i<graph->num_vertices;i++){
        (*(pathtable+i)).known = 0;
        (*(pathtable+i)).distance = INFINITY;
        (*(pathtable+i)).predecessor_index = -1; // Unknown
    }
    (*(pathtable+(getVertexFromLabel(graph, start_label)->index))).distance = 0;
    return pathtable;
}

int findUnvisitedNearest(Table *pathtable, int size){
    int ret = -1;
    int min = INFINITY;
    for(int i=0;i<size;i++){
        if(!(*(pathtable+i)).known){
            if((*(pathtable+i)).distance<min){
                min = (*(pathtable+i)).distance;
                ret = i;
            }
        }
    }
    return ret;
}

void displayTable(Table *pathtable, Graph *graph, short isChar){
    printf("\nVertex Distance Path");
    for(int i=0;i<graph->num_vertices;i++){
        if(isChar){
            if((*(pathtable+i)).predecessor_index==-1){
                printf("\n%3c%8d      -", getVertexFromIndex(graph,i)->label, (*(pathtable+i)).distance);
                continue;
            }
            printf("\n%3c%8d%7c", getVertexFromIndex(graph,i)->label, (*(pathtable+i)).distance, getVertexFromIndex(graph,(*(pathtable+i)).predecessor_index)->label);
        }
        else{
            if((*(pathtable+i)).predecessor_index==-1){
                printf("\n%3d%8d      -", getVertexFromIndex(graph,i)->label, (*(pathtable+i)).distance);
                continue;
            }
            printf("\n%3d%8d%7d", getVertexFromIndex(graph,i)->label, (*(pathtable+i)).distance, getVertexFromIndex(graph,(*(pathtable+i)).predecessor_index)->label);
        }
    }
}

Table* performDijkstra(Graph *graph, int start_label, short isChar){
    Table *pathtable = initializeTable(graph, start_label);
    Vertex *current = getVertexFromLabel(graph, start_label);
    Node *neighbor;
    int newDist, next_ind;
    while(current!=NULL){
        // Set as visited
        (*(pathtable+current->index)).known = 1;

        neighbor = current->edges;
        while(neighbor!=NULL){
            newDist = (*(pathtable+current->index)).distance + neighbor->weight;
            if(newDist < (*(pathtable+neighbor->v_index)).distance){
                (*(pathtable+neighbor->v_index)).distance = newDist;
                (*(pathtable+neighbor->v_index)).predecessor_index = current->index;
            }
            neighbor = neighbor->next;
        }
        next_ind = findUnvisitedNearest(pathtable, graph->num_vertices);
        if(next_ind==-1){
            break;   // All Vertices Visited
        }
        current = getVertexFromIndex(graph, next_ind);
    }
    displayTable(pathtable, graph, isChar);
    return pathtable;
}
