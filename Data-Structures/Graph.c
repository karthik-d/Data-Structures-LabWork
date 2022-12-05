// USING MATRIX

#define STARTER_SIZE 1

#include<stdio.h>
#include<stdlib.h>

struct vertex{
    int index;
    int label;
    struct vertex *next;
};
typedef struct vertex Vertex;

struct graph{
    Vertex *start;
    int num_vertices;
    int **adj_matrix;
    int matrix_size;
};
typedef struct graph Graph;

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

// UTILITY

void expandMatrix(Graph *graph){
    int orig_size = graph->matrix_size;
    graph->matrix_size *= 2;
    graph->adj_matrix = (int**)realloc(graph->adj_matrix, sizeof(int*)*graph->matrix_size);
    for(int i=0;i<graph->matrix_size;i++){
        *(graph->adj_matrix+i) = (int*)malloc(sizeof(int)*STARTER_SIZE);
        for(int j=0;j<graph->matrix_size;j++){
            if(i>=orig_size && j>=orig_size){
                *(*(graph->adj_matrix+i)+j) = 0;  // Initialize to 0
            }
        }
    }
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

// IF THERE ISN't ENOUGH TIME, DON't WIRTE THE INCREMENTING SIZE OF MATRIX
Graph* makeGraph(){
    Graph *handle = (Graph*)malloc(sizeof(Graph));
    handle->start = NULL;
    handle->num_vertices = 0;
    handle->matrix_size = STARTER_SIZE;
    handle->adj_matrix = (int**)malloc(sizeof(int*)*STARTER_SIZE);
    for(int i=0;i<STARTER_SIZE;i++){
        *(handle->adj_matrix+i) = (int*)malloc(sizeof(int)*STARTER_SIZE);
        for(int j=0;j<STARTER_SIZE;j++){
            *(*(handle->adj_matrix+i)+j) = 0;  // Initialize to 0
        }
    }
    return handle;
}

// ADDS TO BEGINNING OF GRAPH
Vertex* addVertex(Graph *graph, int label){
    if(graph->num_vertices==graph->matrix_size){
        expandMatrix(graph);
    }
    Vertex *handle = (Vertex*)malloc(sizeof(Vertex));
    handle->index = graph->num_vertices;
    handle->label = label;
    handle->next = graph->start;
    graph->start = handle;
    graph->num_vertices++;
    return handle;
}

void addEdge(Graph *graph, int from, int to){
    // from AND to are LABELS
    int from_ind = getVertexFromLabel(graph, from)->index;
    int to_ind = getVertexFromLabel(graph, to)->index;
    *(*(graph->adj_matrix+from_ind)+to_ind) = 1;  // Row is 'from'
}

void DFS(Graph *graph, int start_label){
    if(graph->start==NULL){
        printf("\nEmpty Graph");
        return;
    }

    Vertex *start = getVertexFromLabel(graph, start_label);
    if(start==NULL){
        printf("\nInvalid Start Label");
        return;
    }

    int visited[graph->num_vertices];
    for(int i=0;i<graph->num_vertices;i++){
        visited[i] = 0;
    }

    StackNode* stack = createSentinelStackNode();
    Vertex *curr, *neighbor;
    int *adj_array;
    push(stack, createDataStackNode(start));
    do{
        curr = pop(stack);
        if(!visited[curr->index]){
            printf("\nINDEX %d : %d", curr->index, curr->label);
            visited[curr->index]++;  // Set to 1
            adj_array = *(graph->adj_matrix+curr->index);
            for(int i=0;i<graph->num_vertices;i++){
                if(*(adj_array+i) && !visited[i]){
                    push(stack, createDataStackNode(getVertexFromIndex(graph, i)));
                }
            }
        }
    }while(!isStackEmpty(stack));
}

void BFS(Graph *graph, int start_label){
    if(graph->start==NULL){
        printf("\nEmpty Graph");
        return;
    }

    Vertex *start = getVertexFromLabel(graph, start_label);
    if(start==NULL){
        printf("\nInvalid Start Label");
        return;
    }

    int visited[graph->num_vertices];
    for(int i=0;i<graph->num_vertices;i++){
        visited[i] = 0;
    }

    QueueNode* queue = createSentinelQueueNode();
    Vertex *curr, *neighbor;
    int *adj_array;
    enqueue(queue, createDataQueueNode(start));
    do{
        curr = dequeue(queue);
        if(!visited[curr->index]){
            printf("\nINDEX %d : %d", curr->index, curr->label);
            visited[curr->index]++;  // Set to 1
            adj_array = *(graph->adj_matrix+curr->index);
            for(int i=0;i<graph->num_vertices;i++){
                if(*(adj_array+i) && !visited[i]){
                    enqueue(queue, createDataQueueNode(getVertexFromIndex(graph, i)));
                }
            }
        }
    }while(!isQueueEmpty(queue));
}

void TopoSort(Graph* graph){
    // Find In-Degrees
    QueueNode *queue = createSentinelQueueNode();
    int indegree[graph->num_vertices];
    for(int j=0;j<graph->num_vertices;j++){
        indegree[j] = 0;
        for(int i=0;i<graph->num_vertices;i++){
            indegree[j] += *(*(graph->adj_matrix+i)+j);  // Column Sums
        }
        if(indegree[j]==0){
            enqueue(queue, createIntQueueNode(j));
        }
    }

    int curr;
    int vertex_ctr = 0;
    int *adj_array;
    while(!isQueueEmpty(queue)){
        curr = dequeueInt(queue);
        vertex_ctr++;
        printf("\nINDEX %d", getVertexFromIndex(graph, curr)->index+1);

        adj_array = *(graph->adj_matrix+curr);
        for(int i=0;i<graph->num_vertices;i++){
            if(*(adj_array+i)){
                indegree[i]--;
                if(indegree[i]==0){
                    enqueue(queue, createIntQueueNode(i));
                }
            }
        }
    }//*/
    if(vertex_ctr!=graph->num_vertices){
        printf("\nCyclic Graph");
    }
}

void main(){
    /*Graph *graph = makeGraph();
    addVertex(graph, 0);
    addVertex(graph, 1);
    addVertex(graph, 2);
    addVertex(graph, 3);
    addVertex(graph, 4);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 0);
    addEdge(graph, 4, 2);
    DFS(graph, 0);
    printf("\n");
    BFS(graph, 0);*/

    Graph *graph = makeGraph();
  addVertex(graph, 145);
  addVertex(graph, 203);
  addVertex(graph, 202);
  addVertex(graph,135);
  addVertex(graph, 215);
  addVertex(graph, 123);
  addEdge(graph, 145, 203);
  addEdge(graph, 203, 202);
  addEdge(graph, 202, 215);
  addEdge(graph, 202, 135);
  addEdge(graph, 123, 202);
  addEdge(graph, 123, 145);
  DFS(graph, 145);

    Graph *graph2 = makeGraph();
    addVertex(graph2, 1);
    addVertex(graph2, 2);
    addVertex(graph2, 3);
    addVertex(graph2, 4);
    addVertex(graph2, 5);
    addVertex(graph2, 6);
    addVertex(graph2, 7);
    addEdge(graph2, 1, 3);
    addEdge(graph2, 1, 4);
    addEdge(graph2, 1, 2);
    addEdge(graph2, 2, 4);
    addEdge(graph2, 2, 5);
    addEdge(graph2, 3, 6);
    addEdge(graph2, 4, 3);
    addEdge(graph2, 4, 5);
    addEdge(graph2, 4, 6);
    addEdge(graph2, 4, 7);
    addEdge(graph2, 5, 7);
    //addEdge(graph2, 6, 4);
    addEdge(graph2, 7, 6);
    printf("\n");
    TopoSort(graph2);
}
