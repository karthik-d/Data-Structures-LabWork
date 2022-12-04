#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};
typedef struct node Node;

struct queue{
    int size;
    Node *front;
    Node *rear;
};
typedef struct queue Queue;

Node* createSentinelNode(){
    Node* handle = (Node*)malloc(sizeof(Node));
    handle->next = NULL;
    return handle;
}

Node* createDataNode(int value){
    Node* handle = (Node*)malloc(sizeof(Node));
    handle->next = NULL;
    handle->data = value;
    return handle;
}

Queue* createEmptyQueue(){
    Queue *handle = (Queue*)malloc(sizeof(Queue));
    handle->front = createSentinelNode();
    handle->rear = createSentinelNode();
    handle->size = 0;
    return handle;
}

short isEmpty(Queue *Q){
    return (Q->front->next==NULL && Q->rear->next==NULL);
}

void enqueue(Node *node, Queue *Q){
    if(isEmpty(Q)){
        Q->front->next = node;
        Q->rear->next = node;
    }
    else{
        Q->rear->next->next = node;
        Q->rear->next = node;
    }
    Q->size++;
}

int dequeue(Queue *Q, int *exit_status){
    if(isEmpty(Q)){
        *exit_status = -1;
        return 0;
    }
    else{
        Node* del_node = Q->front->next;
        int value = Q->front->next->data;
        Q->front->next = Q->front->next->next;
        if(Q->front->next==NULL){    // Queue is now empty
            Q->rear->next = NULL;
        }
        free(del_node);
        Q->size--;
        *exit_status = 0;
        return value;
    }
}

int findJospehusWinner(int num_players, int n){
    Queue *playerQ = createEmptyQueue();
    // Add all players
    for(int i=0;i<num_players;i++){
        enqueue(createDataNode(i+1), playerQ);
    }
    // Play Game
    int lost, status;
    while(playerQ->size!=1){
        for(int i=1;i<n;i++){
            enqueue(createDataNode(dequeue(playerQ, &status)), playerQ);
        }
        lost = dequeue(playerQ, &status);
        printf("\nPLAYER %d HAS LOST", lost);
    }
    return dequeue(playerQ, &status);
}

void main(){
    printf("\nWINNER : %d", findJospehusWinner(6, 4));
}
