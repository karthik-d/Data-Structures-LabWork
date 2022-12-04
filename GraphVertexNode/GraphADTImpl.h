#include<stdio.h>
#include<stdlib.h>

// STACK_HANDLE FUNCTIONS

short isStackEmpty(Stack *stack){
  return (stack->size==0);
}

StackNode* createSentinelStackNode(){
  StackNode *handle = (StackNode*)malloc(sizeof(StackNode));
  handle->next = NULL;
  handle->node = NULL;
  return handle;
}

StackNode* createDataStackNode(Vertex *node){
  StackNode *handle = (StackNode*)malloc(sizeof(StackNode));
  handle->node = node;
  handle->next = NULL;
  return handle;
}

Stack* createStack(){
  Stack *handle = (Stack*)malloc(sizeof(Stack));
  handle->top = createSentinelStackNode();
  handle->size = 0;
  return handle;
}

void push(Vertex *node, Stack *stack){
  StackNode *new_node = createDataStackNode(node);
  new_node->next = stack->top->next;
  stack->top->next = stack->top->next = new_node;
  stack->size++;
}

Vertex* pop(Stack *stack){
  if(stack->size==0){
    return NULL;
  }
  Vertex* retval = stack->top->next->node;
  stack->top->next = stack->top->next->next;
  stack->size--;
  return retval;
}

// QUEUE-HANDLE FUNCTIONS

short isQueueEmpty(Queue *queue){
  return (queue->size==0);
}

QueueNode* createSentinelQueueNode(){
  QueueNode *handle = (QueueNode*)malloc(sizeof(QueueNode));
  handle->next = NULL;
  handle->node = NULL;
  return handle;
}

QueueNode* createDataQueueNode(Vertex *node){
  QueueNode *handle = (QueueNode*)malloc(sizeof(QueueNode));
  handle->node = node;
  handle->next = NULL;
  return handle;
}

Queue* createQueue(){
  Queue *handle = (Queue*)malloc(sizeof(Queue));
  handle->front = createSentinelQueueNode();
  handle->rear = createSentinelQueueNode();
  handle->size = 0;
  return handle;
}

void enqueue(Vertex *node, Queue *queue){
  QueueNode *new_node = createDataQueueNode(node);
  if(queue->size==0){
    queue->front->next = new_node;   // Front and Rear are sentinel
    queue->rear->next = new_node;
  }
  else{
    queue->rear->next->next = new_node;
    queue->rear->next = new_node;
  }
  queue->size++;
}

Vertex* dequeue(Queue *queue){
  if(queue->size==0){
    return NULL;
  }
  Vertex *retval = queue->front->next->node;
  queue->front->next = queue->front->next->next;
  queue->size--;
  if(queue->front->next==NULL){
    queue->rear->next = NULL;
  }
  return retval;
}

// GRAPH-HANDLE FUNCTIONS

Neighbor *wrapNeighbor(Vertex *vertex){
  Neighbor *handle = (Neighbor*)malloc(sizeof(Neighbor));
  handle->vertex = vertex;
  handle->next = NULL;
  return handle;
}

Graph* createGraph(){
  Graph *handle = (Graph*)malloc(sizeof(Graph));
  handle->vertex = NULL;     // NOT SENTINEL
  handle->num_vertices = 0;
  return handle;
}

void addVertex(Graph *graph, int label){
  Vertex *new_vertex = (Vertex*)malloc(sizeof(Vertex));
  new_vertex->index = graph->num_vertices;
  new_vertex->label = label;
  new_vertex->neighbors = NULL;
  //INSERTION
  new_vertex->next = graph->vertex;   // NON-SENTINEL ADDITION
  graph->vertex = new_vertex;
  graph->num_vertices++;
}

Vertex* findVertexByLabel(int label, Graph *graph){
  Vertex *handle = graph->vertex;
  while(handle!=NULL){
    if(handle->label==label){
      return handle;
    }
    handle = handle->next;
  }
  return NULL;   // NOT FOUND
}

void addEdge(Graph *graph, int from_label, int to_label){
  Vertex *source = findVertexByLabel(from_label, graph);
  Neighbor *new_neighbor = wrapNeighbor(findVertexByLabel(to_label, graph));
  new_neighbor->next = source->neighbors;
  source->neighbors = new_neighbor;
}

void BFS(Graph *graph, int start_label){
  int visited[graph->num_vertices];   // 0 if specific index of graph is not visited
  for(int i=0;i<graph->num_vertices;i++){
    visited[i] = 0;
  }

  Queue *queue = createQueue();
  Vertex *curr = findVertexByLabel(start_label, graph);
  Neighbor *neighbor_parser;
  enqueue(curr, queue);
  while(!isQueueEmpty(queue)){
    curr = dequeue(queue);
    if(!visited[curr->index]){
      printf("INDEX: %d, LABEL: %d\n", curr->index, curr->label);
      visited[curr->index] = 1;
      neighbor_parser = curr->neighbors;
      while(neighbor_parser!=NULL){
        if(!visited[neighbor_parser->vertex->index]){
          enqueue(neighbor_parser->vertex, queue);
        }
        neighbor_parser = neighbor_parser->next;
      }
    }
  }
}

void DFS(Graph *graph, int start_label){
  int visited[graph->num_vertices];
  for(int i=0;i<graph->num_vertices;i++){
    visited[i] = 0;
  }

  Stack *stack = createStack();
  Vertex *curr = findVertexByLabel(start_label, graph);
  Neighbor *neighbor_parser;
  push(curr, stack);
  while(!isStackEmpty(stack)){
    curr = pop(stack);
    if(!visited[curr->index]){
      printf("INDEX: %d, LABEL: %d\n", curr->index, curr->label);
      visited[curr->index] = 1;
      neighbor_parser = curr->neighbors;
      while(neighbor_parser!=NULL){
        if(!visited[neighbor_parser->vertex->index]){
          push(neighbor_parser->vertex, stack);
        }
        neighbor_parser = neighbor_parser->next;
      }
    }
  }
}

void BFS_Recursive(Graph *graph, Vertex *curr, Queue *queue, int visited[]){
  if(!visited[curr->index]){
    printf("INDEX: %d, LABEL: %d\n", curr->index, curr->label);
    visited[curr->index] = 1;
    Neighbor *neighbor_parser = curr->neighbors;
    while(neighbor_parser!=NULL){
      if(!visited[neighbor_parser->vertex->index]){
        enqueue(neighbor_parser->vertex, queue);
      }
      neighbor_parser = neighbor_parser->next;
    }
  }
  if(isQueueEmpty(queue)){
    return;
  }
  else{
    BFS_Recursive(graph, dequeue(queue), queue, visited);
  }
}

void BFS_Driver(Graph *graph, int start_label){
  int visited[graph->num_vertices];
  for(int i=0;i<graph->num_vertices;i++){
    visited[i] = 0;
  }
  Queue *queue = createQueue();
  Vertex *curr = findVertexByLabel(start_label, graph);
  BFS_Recursive(graph, curr, queue, visited);
}
