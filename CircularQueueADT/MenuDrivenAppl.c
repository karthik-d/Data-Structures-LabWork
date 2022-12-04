#include "CircularQueue.h"
#include "CircularQueueImpl.h"

void main(){
    Queue *Q1 = initializeQueue();
    Queue *Q2 = initializeQueue();
    Queue *queue;
    char ch = 'y';
    int oper, status, response, job_num, cpu_time, time_diff;
    while(ch!='n'){
        printf("\n1-Add Job\n2-Finish Job\n3-Display Waiting Jobs\nEnter Choice: ");
        scanf(" %d", &oper);
        if(oper==1){
            printf("\nEnter Job Number: ");
            scanf(" %d", &job_num);
            printf("Enter CPU Burst Time: ");
            scanf(" %d", &cpu_time);
            queue = getFasterQueue(Q1, Q2, &time_diff);
            enqueue(queue, createDataNode(job_num, cpu_time));
            if(time_diff<0){
                printf("\nJob added to Process Queue 1\nIt is %d ms faster than Queue 2\n", -time_diff);
            }
            else if(time_diff>0){
                printf("\nJob added to Process Queue 2\nIt is %d ms faster than Queue 1\n", time_diff);
            }
            else{
                printf("\nJob added to Queue 1\nIt has the same waiting time as Queue 2\n");
            }
        }
        else if(oper==2){
            printf("\n1-From Process Queue 1\n2-From Process Queue 2\nEnter Choice: ");
            scanf(" %d", &response);
            if(response==1){
                job_num = dequeue(Q1, &status);
            }
            else{
                job_num = dequeue(Q2, &status);
            }
            if(status==-1){
                printf("\nProcess Queue Empty\n");
            }
            else{
                printf("\nJob J%d was completed\nRemoved from Process Queue\n", job_num);
            }
        }
        else if(oper==3){
            printf("\nPROCESS QUEUE 1 STATUS\n");
            display(Q1);
            printf("\n\nPROCESS QUEUE 2 STATUS\n");
            display(Q2);
            printf("\n");
        }
        else{
            printf("\nInvalid Choice\n");
        }
        printf("\nMore Operations? (y/n): ");
        scanf(" %c", &ch);
    }
}
