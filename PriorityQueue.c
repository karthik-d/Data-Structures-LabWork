// MIN-HEAP

#include<stdio.h>
#include<stdlib.h>

struct priority_q{
    int *data;
    int size;
    int capacity;
};
typedef struct priority_q PriorityQ;

PriorityQ* makeQueue(int capacity){
    PriorityQ *handle = (PriorityQ*)malloc(sizeof(PriorityQ));
    handle->data = (int*)malloc(sizeof(int)*capacity);
    handle->size = 0;
    handle->capacity = capacity;
    return handle;
}

int enqueue(PriorityQ *queue, int value){
    if(queue->size==queue->capacity){
        return -1; // Queue is full
    }
    int ind = queue->size+1;   // Index starts from 1
    *(queue->data+ind) = value;

    // Percolate Up
    while(ind>1 && *((queue->data)+(ind/2))>value){
        *((queue->data)+ind) = *(queue->data+(ind/2));
        *((queue->data)+(ind/2)) = value;
        ind /= 2;
    }
    queue->size++;

    return 0;  // Successful
}

int dequeue(PriorityQ *queue, int *exit_status){
    if(queue->size==0){
        *exit_status = -1;
        return -1;    // Empty Queue
    }
    int ind = 1;
    int retval = *(queue->data+ind);
    int last_leaf = *(queue->data+queue->size);
    *(queue->data+ind) = last_leaf;
    queue->size--;

    // Percolate Down
    ind *= 2;
    ind += (*(queue->data+ind)<=*(queue->data+ind+1) ? 0 : 1);  // Smaller child
    // Value at (ind+1) will NEVER BE UNDEFINED because the last leaf was at this position and size has been decremented already. Hence a cushion of 1 block
    // However the condition below ensures that it is not compared with this deleted node
    printf("%d ", ind);
    while(ind<=queue->size && *(queue->data+ind)<last_leaf){
        *((queue->data)+(ind/2)) = *(queue->data+ind);
        *(queue->data+ind) = last_leaf;
        ind *= 2;
    }

    *exit_status = 0;   // Success;
    return retval;
}

void display(PriorityQ *queue){
    printf("\n");
    for(int i=1;i<=queue->size;i++){  // <= because index starts from 1
        printf("%d, ", *(queue->data+i));
    }
    printf("\n");
}

void main(){
    int response;
    PriorityQ *queue = makeQueue(10);
    enqueue(queue, 10);
    enqueue(queue, 5);
    enqueue(queue, 3);
    enqueue(queue, 2);
    enqueue(queue, 4);

    display(queue);
    dequeue(queue, &response);
    display(queue);
}
