#include<stdio.h>
#include<stdlib.h>

struct queue{
    int capacity;
    int size;
    int front;
    int rear;
    int *data;
};
typedef struct queue Queue;

Queue* createEmptyQueue(int capacity){
    Queue *handle = (Queue*)malloc(sizeof(Queue));
    handle->capacity = capacity;
    handle->size = 0;
    handle->front = 0;
    handle->rear = capacity-1;   // MUST BE THIS VALUE. AFTER FIRST ENQUEUE IT BECOMES 0
    handle->data = (int*)malloc(sizeof(int)*capacity);
}

short checkOverflow(Queue *Q){
    return Q->size==Q->capacity;
}

short checkUnderflow(Queue *Q){
    return Q->size==0;
}

int enqueue(int value, Queue *Q){
    if(checkOverflow(Q)){
        return -1; // Overflow
    }
    else{
        Q->rear = (Q->rear+1)%Q->capacity;
        Q->data[Q->rear] = value;
        Q->size++;
        return 0;   // Success
    }
}

int dequeue(Queue *Q, int *exit_status){
    if(checkUnderflow(Q)){
        *exit_status = -1;   // Underflow
        return -1;
    }
    else{
        int value = Q->data[Q->front];
        Q->front = (Q->front+1)%Q->capacity;
        Q->size--;
        *exit_status = 0;   // Success
        return value;
    }
}

void display(Queue *Q){
    if(checkUnderflow(Q)){
        printf("\nEmpty Queue\n");
    }
    else if(Q->front<=Q->rear){
        for(int i=Q->front;i<=Q->rear;i++){
            printf(" %d ", Q->data[i]);
        }
    }
    else{
        for(int i=Q->front;i<Q->capacity;i++){
            printf(" %d ", Q->data[i]);
        }
        printf(" <> ");
        for(int i=0;i<=Q->rear;i++){
            printf(" %d ", Q->data[i]);
        }
    }
}

void main(){
    Queue *Q = createEmptyQueue(5);
    int response;
    printf("%d", enqueue(10, Q));
    printf("%d", enqueue(20, Q));
    printf("%d", enqueue(30, Q));
    printf("%d", enqueue(40, Q));
    printf("%d", enqueue(50, Q));
    printf("%d", dequeue(Q, &response));
    printf("%d", enqueue(60, Q));
    printf("%d", dequeue(Q, &response));
    printf("%d", dequeue(Q, &response));
    printf("%d", dequeue(Q, &response));
    printf("%d", dequeue(Q, &response));
    printf("%d", dequeue(Q, &response));
    printf("%d", dequeue(Q, &response));
    printf("%d", dequeue(Q, &response));
    printf("\n\n");
    display(Q);
}
