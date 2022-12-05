// ADJACENCY LIST - NON CIRCULAR - INDEPENDENT VERTEX AND VERTEX_NODE

#include<stdio.h>
#include<stdlib.h>

#include<limits.h>

#define STARTER_SIZE 1
#define INFINITY INT_MAX

// WRAP ALL GRAPH CONTENTS ALONG WITH THE LATEST INDEX INTO A GRAPH STRUCTURE
// THEN USED STATIC INT to HANDLE INDICES


// BOTH GRAPH start and edges are NON-SENTINAL
struct node{
    int v_index;
    struct node *next;
};
typedef struct node Node;

struct vertex{
    int index;
    int label;
    Node *edges;
    struct vertex *next;
};
typedef struct vertex Vertex;

struct graph{
    Vertex *start;
    int num_vertices;
};
typedef struct graph Graph;

struct table{
    short known;
    int distance;
    int predecessor_index;    // -1 is unknown
};
typedef struct table Table;

struct stack_node{
    Vertex *data;
    struct stack_node *next;
};
typedef struct stack_node StackNode;

struct queue_node{
    Vertex *data;
    int num;  // For Toposort
    struct queue_node *next;
};
typedef struct queue_node QueueNode;

StackNode* createSentinelStackNode(){
    StackNode *handle = (StackNode*)malloc(sizeof(StackNode));
    handle->next = NULL;
    return handle;
}

StackNode* createDataStackNode(Vertex *vertex){
    StackNode *handle = (StackNode*)malloc(sizeof(StackNode));
    handle->data = vertex;
    handle->next = NULL;
    return handle;
}

short isStackEmpty(StackNode *top){
    return (top->next==NULL);
}

void push(StackNode* top, StackNode *node){
    node->next = top->next;
    top->next = node;
}

Vertex* pop(StackNode *top){
    if(isStackEmpty(top)){
        return NULL;
    }
    Vertex *data = top->next->data;
    StackNode *del_node = top->next;
    top->next = top->next->next;
    free(del_node);
    return data;
}

void displayStack(StackNode *top){
    StackNode *handle = top;
    printf("\n");
    while(handle->next!=NULL){
        handle = handle->next;
        printf("%d, ", handle->data->index);
    }
    printf("\n");
}


// QUEUE FUNCTIONS

QueueNode* createSentinelQueueNode(){
    QueueNode *handle = (QueueNode*)malloc(sizeof(QueueNode));
    handle->next = NULL;
    return handle;
}

QueueNode* createDataQueueNode(Vertex *vertex){
    QueueNode *handle = (QueueNode*)malloc(sizeof(QueueNode));
    handle->data = vertex;
    handle->next = NULL;
    return handle;
}

QueueNode* createIntQueueNode(int value){
    QueueNode *handle = (QueueNode*)malloc(sizeof(QueueNode));
    handle->data = NULL;
    handle->num = value;
    handle->next = NULL;
    return handle;
}

short isQueueEmpty(QueueNode *front){
    return (front->next==NULL);
}

void enqueue(QueueNode* front, QueueNode *node){
    QueueNode *handle = front;
    while(handle->next!=NULL){
        handle = handle->next;
    }
    handle->next = node;
}

Vertex* dequeue(QueueNode *front){
    if(isQueueEmpty(front)){
        return NULL;
    }
    Vertex *data = front->next->data;
    QueueNode *del_node = front->next;
    front->next = front->next->next;
    free(del_node);
    return data;
}

int dequeueInt(QueueNode *front){
    if(isQueueEmpty(front)){
        return NULL;
    }
    int data = front->next->num;
    QueueNode *del_node = front->next;
    front->next = front->next->next;
    free(del_node);
    return data;
}

// GRAPH FUNCTIONS //

Node* createNewNode(int v_index){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->v_index = v_index;
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

void addEdge(Graph *graph, int from, int to){
    Vertex *source = getVertexFromLabel(graph, from);
    Node *destn = createNewNode(getVertexFromLabel(graph, to)->index);
    destn->next = source->edges;      // Insert new edge at beginning of Edges List
    source->edges = destn;
}

void DepthFirstSearch(Graph *graph, int start_label, short isAlpha){
    if(graph==NULL){
        printf("\nEmpty Graph");
        return;
    }
    Vertex *start = getVertexFromLabel(graph, start_label);
    if(start==NULL){
        printf("\nInvalid Start Node Label");
        return;
    }

    StackNode *stack = createSentinelStackNode();
    int visited[graph->num_vertices];
    for(int i=0;i<graph->num_vertices;i++){
        visited[i] = 0;
    }

    Vertex *current, *temp;
    Node *edgeParser;
    push(stack, createDataStackNode(start));
    do{
        current = pop(stack);
        if(!visited[current->index]){
            if(isAlpha){
                printf("\nINDEX %d : %c", current->index, current->label);
            }
            else{
                printf("\nINDEX %d : %d", current->index, current->label);
            }
            visited[current->index] = 1;
            edgeParser = current->edges;
            while(edgeParser!=NULL){
                if(!visited[edgeParser->v_index]){
                    push(stack, createDataStackNode(getVertexFromIndex(graph, edgeParser->v_index)));
                }
                edgeParser = edgeParser->next;
            }
        }
    }while(!isStackEmpty(stack));
}

void BreadthFirstSearch(Graph *graph, int start_label, int isAlpha){
    if(graph==NULL){
        printf("\nEmpty Graph");
    }
    Vertex *start = getVertexFromLabel(graph, start_label);
    if(start==NULL){
        printf("\nInvalid Start Label");
    }

    QueueNode *queue = createSentinelQueueNode();
    int visited[graph->num_vertices];
    for(int i=0;i<graph->num_vertices;i++){
        visited[i] = 0;
    }

    Vertex *current;
    Node *edgeParser;
    enqueue(queue, createDataQueueNode(start));
    do{
        current = dequeue(queue);
        if(!visited[current->index]){
            if(isAlpha){
                printf("\nINDEX %d : %c", current->index, current->label);
            }
            else{
                printf("\nINDEX %d : %d", current->index, current->label);
            }
            visited[current->index] = 1;
            edgeParser = current->edges;
            while(edgeParser!=NULL){
                if(!visited[edgeParser->v_index]){
                    enqueue(queue, createDataQueueNode(getVertexFromIndex(graph, edgeParser->v_index)));
                }
                edgeParser = edgeParser->next;
            }
        }
    }while(!isQueueEmpty(queue));
}

void TopoSort(Graph* graph){
    // Find In-Degrees
    QueueNode *queue = createSentinelQueueNode();

    Vertex *vertex = graph->start;
    int indegree[graph->num_vertices];
    while(vertex!=NULL){
        indegree[vertex->index] = 0;
        vertex = vertex->next;
    }

    vertex = graph->start;
    Node *edgeParser = NULL;
    while(vertex!=NULL){
        edgeParser = vertex->edges;
        while(edgeParser!=NULL){
            indegree[edgeParser->v_index]++;
            edgeParser = edgeParser->next;
        }
        vertex = vertex->next;
    }

    vertex = graph->start;
    while(vertex!=NULL){
        if(indegree[vertex->index] == 0){
            enqueue(queue, createIntQueueNode(vertex->index));
        }
        vertex = vertex->next;
    }

    Vertex *curr;
    int vertex_ctr = 0;
    int *adj_array;
    while(!isQueueEmpty(queue)){
        curr = getVertexFromIndex(graph, dequeueInt(queue));
        vertex_ctr++;
        printf("\nINDEX %d", curr->index+1);

        edgeParser = curr->edges;
        while(edgeParser!=NULL){
            indegree[edgeParser->v_index]--;
            if(indegree[edgeParser->v_index]==0){
                enqueue(queue, createIntQueueNode(edgeParser->v_index));
            }
            edgeParser = edgeParser->next;
        }
    }//
    if(vertex_ctr!=graph->num_vertices){
        printf("\nCyclic Graph");
    }
}

void main(){
    Graph *graph1 = createNewGraph();
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

    printf("GRAPH 1\n\nDEPTH FIRST SEARCH");
    DepthFirstSearch(graph1, 'A', 1);
    printf("\n\nBREADTH FIRST SEARCH");
    BreadthFirstSearch(graph1, 'A', 1);

    Graph *graph2 = createNewGraph();
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

    printf("\n\nGRAPH 2\n\nDEPTH FIRST SEARCH");
    DepthFirstSearch(graph2, 0, 0);
    printf("\n\nBREADTH FIRST SEARCH");
    BreadthFirstSearch(graph2, 0, 0);

    Graph *graph3 = createNewGraph();
    addVertex(graph3, 'A');
    addVertex(graph3, 'B');
    addVertex(graph3, 'C');
    addVertex(graph3, 'D');
    addVertex(graph3, 'E');
    addVertex(graph3, 'F');
    addVertex(graph3, 'G');
    addVertex(graph3, 'H');
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

    Graph *graph4 = createNewGraph();
    addVertex(graph4, 1);
    addVertex(graph4, 2);
    addVertex(graph4, 3);
    addVertex(graph4, 4);
    addVertex(graph4, 5);
    addVertex(graph4, 6);
    addVertex(graph4, 7);
    addEdge(graph4, 1, 3);
    addEdge(graph4, 1, 4);
    addEdge(graph4, 1, 2);
    addEdge(graph4, 2, 4);
    addEdge(graph4, 2, 5);
    addEdge(graph4, 3, 6);
    addEdge(graph4, 4, 3);
    addEdge(graph4, 4, 5);
    addEdge(graph4, 4, 6);
    addEdge(graph4, 4, 7);
    addEdge(graph4, 5, 7);
    //addEdge(graph4, 6, 4);
    addEdge(graph4, 7, 6);
    printf("\n");
    TopoSort(graph4);
}
