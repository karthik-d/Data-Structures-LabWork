#include "CircularQueue.h"
#include "CircularQueueImpl.h"

void main(){
    Queue *Q1 = initializeQueue();
    Queue *Q2 = initializeQueue();
    Queue *queue;
    char job_nums[][3] = {"J1", "J2", "J3", "J4", "J5", "J6", "J7", "J8", "J9", "J10"};
    int burst_times[] = {2, 4, 8, 5, 2, 7, 4, 3, 6, 6};
    int status, response, cpu_time, time_diff;
    for(int i=0;i<10;i++){
        queue = getFasterQueue(Q1, Q2, &time_diff);
        enqueue(queue, createDataNode(job_nums[i], burst_times[i]));
        printf("\nJob %s", job_nums[i]);
        if(time_diff<0){
            printf("\nAdded to Process Queue 1\nIt is %d ms faster than Queue 2\n", -time_diff);
        }
        else if(time_diff>0){
            printf("\nAdded to Process Queue 2\nIt is %d ms faster than Queue 1\n", time_diff);
        }
        else{
            printf("\nAdded to Queue 1\nIt has the same waiting time as Queue 2\n");
        }
    }
    printf("\nPROCESS QUEUE 1 STATUS\n");
    display(Q1);
    printf("\n\nPROCESS QUEUE 2 STATUS\n");
    display(Q2);
    printf("\n");
}
