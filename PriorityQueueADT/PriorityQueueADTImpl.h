// MAX-HEAP

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Employee makeEmployee(int id, char *name, int salary){
    Employee handle;
    handle.id = id;
    strcpy(handle.name, name);
    handle.salary = salary;
    return handle;
}

PriorityQ* createEmptyQueue(int capacity){
    PriorityQ *handle = (PriorityQ*)malloc(sizeof(PriorityQ));
    handle->employees = (Employee*)malloc(sizeof(Employee)*(capacity+1));   // SINCE INDEXING STARTS AT 1
    handle->size = 0;
    handle->capacity = capacity;
    return handle;
}

short isFull(PriorityQ *queue){
    return (queue->capacity==queue->size);
}

short isEmpty(PriorityQ *queue){
    return (queue->size==0);
}

void expandQueue(PriorityQ *queue){
    queue->capacity *= 2;
    queue->employees = (Employee*)realloc(queue->employees, sizeof(Employee)*(queue->capacity+1));
}

int enqueue(PriorityQ *queue, Employee value){
    int status;
    if(isFull(queue)){
        expandQueue(queue);
        status = 1;              // Non-fatal error to indicate that queue has expanded
    }
    else{
        status = 0;
    }
    int ind = queue->size+1;   // Index starts from 1
    *(queue->employees+ind) = value;


    // Percolate Up
    while(ind>1 && (*((queue->employees)+(ind/2))).salary<value.salary){
        *((queue->employees)+ind) = *(queue->employees+(ind/2));
        *((queue->employees)+(ind/2)) = value;
        ind /= 2;
    }

    queue->size++;
    return status;  // Successful
}

Employee dequeue(PriorityQ *queue, int *exit_status){
    Employee retval;
    if(isEmpty(queue)){
        *exit_status = -1;
        return retval;    // Empty Queue, Dummy Employee
    }
    int ind = 1;
    Employee last_leaf = *(queue->employees+queue->size);
    retval = *(queue->employees+ind);
    *(queue->employees+ind) = last_leaf;
    queue->size--;

    // Percolate Down
    ind *= 2;
    ind += ((*(queue->employees+ind)).salary>=(*(queue->employees+ind+1)).salary ? 0 : 1);  // Larger child
    // Value at (ind+1) will NEVER BE UNDEFINED because the last leaf was at this position and size has been decremented already. Hence a cushion of 1 block
    // However the condition below ensures that it is not compared with this deleted node
    while(ind<=queue->size && (*(queue->employees+ind)).salary<last_leaf.salary){
        *((queue->employees)+(ind/2)) = *(queue->employees+ind);
        *(queue->employees+ind) = last_leaf;
        ind *= 2;
        ind += ((*(queue->employees+ind)).salary>=(*(queue->employees+ind+1)).salary ? 0 : 1);
    }

    *exit_status = 0;   // Success;
    return retval;
}

void displayEmployee(Employee employee){
    printf("\nID: %d", employee.id);
    printf("\nNAME: %s", employee.name);
    printf("\nSALARY: Rs.%d", employee.salary);
}

void display(PriorityQ *queue){
    if(isEmpty(queue)){
        printf("\nEmpty Queue\n");
        return;
    }
    printf("\nQUEUE STATUS\n");
    for(int i=1;i<=queue->size;i++){  // '<=' because index starts from 1
        displayEmployee(*(queue->employees+i));
        printf("\n");
    }
    printf("\n");
}
