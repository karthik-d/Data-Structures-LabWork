#include<stdio.h>
#include<stdlib.h>

// NODE Control Functions //

Node* createSentinelNode(){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->next = NULL;
    return handle;
}

Node* createDataNode(char *job_num, int cpu_time){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->next = NULL;
    handle->job_num = job_num;
    handle->burst_time = cpu_time;
    return handle;
}

// QUEUE Control Functions //

short isEmpty(Queue *Q){
    if(Q->front->next==NULL && Q->rear->next==NULL){
        return 1;
    }
    return 0;
}

Queue* initializeQueue(){
    Queue *handle = (Queue*)malloc(sizeof(Queue));
    handle->front = createSentinelNode();
    handle->rear = createSentinelNode();
    return handle;
}

void enqueue(Queue *Q, Node *node){
    if(isEmpty(Q)){
        Q->front->next = node;
        Q->rear->next = node;
    }
    else{
        Q->rear->next->next = node;
        Q->rear->next = node;
    }
}

char* dequeue(Queue *Q, int *exit_status){
    if(isEmpty(Q)){
        *exit_status = -1;    // Empty Queue
        return NULL;
    }
    Node* del_node = Q->front->next;
    char *job_num = del_node->job_num;
    if(Q->front->next==Q->rear->next){
        Q->front->next = NULL;
        Q->rear->next = NULL;
    }
    else{
        Q->front->next = Q->front->next->next;
    }
    free(del_node);
    *exit_status = 0;        // DEQUEUE Successful
    return job_num;
}

void display(Queue *Q){
    if(isEmpty(Q)){
        printf("\nEmpty Queue\n");
        return;
    }
    int process_time = 0;
    Node *handle = Q->front;
    printf("\nFRONT\n-----------------");
    do{
        handle = handle->next;
        printf("\nJob %s - %d ms", handle->job_num, handle->burst_time);
        process_time += handle->burst_time;
    }while(handle!=Q->rear->next);
    printf("\n-----------------\nREAR\n");
    printf("Total Process Time: %d ms", process_time);
}

// APPLICATION Functions //

int getWaitingTime(Queue *Q){
    if(isEmpty(Q)){
        return 0;
    }
    int wait_time = 0;
    Node *handle = Q->front;
    do{
        handle = handle->next;
        wait_time += handle->burst_time;
    }while(handle!=Q->rear->next);
    return wait_time;
}

Queue* getFasterQueue(Queue* Q1, Queue* Q2, int *diff){
    *diff = getWaitingTime(Q1) - getWaitingTime(Q2);
    if(*diff<=0){
        return Q1;
    }
    else{
        return Q2;
    }
}
