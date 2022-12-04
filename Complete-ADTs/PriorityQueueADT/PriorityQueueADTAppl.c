#include "PriorityQueueADT.h"
#include "PriorityQueueADTImpl.h"

void main(){
    char names[][10] = {"Adam", "Benjamin", "Eve", "Claire", "Dane"};
    int salaries[] = {20000, 30000, 80000, 65000, 35000};
    int ids[] = {1, 4, 2, 3, 5};

    PriorityQ *queue = createEmptyQueue(1);
    int response;
    for(int i=0;i<5;i++){
        response = enqueue(queue, makeEmployee(ids[i], names[i], salaries[i]));
        if(response==0){
            printf("\nEmployee with ID '%d' inserted\n", ids[i]);
            display(queue);
        }
        else if(response==1){
            printf("\nQueue was expanded\nEmployee with ID '%d' inserted\n", ids[i]);
            display(queue);
        }
    }

    Employee emp;
    emp = dequeue(queue, &response);
    if(response==-1){
        printf("\nEmpty Queue\n");
    }
    else{
        displayEmployee(emp);
        printf("\n(This employee was removed)\n");
    }

    display(queue);

}
