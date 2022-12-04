#include<stdio.h>
#include<stdlib.h>

// STACK FUNCTIONS

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

// GRAPH FUNCTIONS //

Node* createNewNode(int v_index){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->v_index = v_index;
    handle->next = NULL;
    return handle;
}

Vertex* addVertex(Vertex* graph, int label){
    static int index;
    Vertex *handle = (Vertex*)malloc(sizeof(Vertex));
    if(graph==NULL){
        index = 0;
    }
    else{
        index++;    // The highest index is at the first position
    }
    handle->index = index;
    handle->label = label;
    handle->edges = NULL;   // List of Edges (each is a Node)
    handle->next = graph;
    graph = handle;
    return graph;
}

Vertex* getVertexFromLabel(Vertex *graph, int label){
    Vertex *handle = graph;
    while(handle!=NULL){
        if(handle->label==label){
            return handle;
        }
        handle = handle->next;
    }
    return NULL;
}

Vertex* getVertexFromIndex(Vertex *graph, int index){
    Vertex *handle = graph;
    while(handle!=NULL){
        if(handle->index==index){
            return handle;
        }
        handle = handle->next;
    }
    return NULL;
}

void addEdge(Vertex *graph, int from, int to){
    Vertex *source = getVertexFromLabel(graph, from);
    Node *destn = createNewNode(getVertexFromLabel(graph, to)->index);
    destn->next = source->edges;      // Insert new edge at beginning of Edges List
    source->edges = destn;
}

void DepthFirstSearch(Vertex *graph, int start_label, short isAlpha){
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
    int visited[graph->index+1];
    for(int i=0;i<graph->index+1;i++){
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

void BreadthFirstSearch(Vertex *graph, int start_label, int isAlpha){
    if(graph==NULL){
        printf("\nEmpty Graph");
    }
    Vertex *start = getVertexFromLabel(graph, start_label);
    if(start==NULL){
        printf("\nInvalid Start Label");
    }

    QueueNode *queue = createSentinelQueueNode();
    int visited[graph->index+1];
    for(int i=0;i<graph->index+1;i++){
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
