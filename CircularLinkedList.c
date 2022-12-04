#include<stdio.h>
#include<stdlib.h>

short isEmpty(Node *head){
    return (head->next==head);
}

int GetListLength(Node* head){
    Node *handle = head;
    if(isEmpty(head)){
        return -1;
    }
    else{
        int ctr = 0;
        while(handle->next!=head){
            handle = handle->next;
            ctr++;
        }
        return ctr;
    }
}

int FindMinMax(Node* head, int *max, int *min){
    Node *handle = head;
    if(isEmpty(head)){
        return -1;   // Error
    }
    else{
        *min = head->data;
        *max = head->data;
        int check;
        while(handle->next!=head){
            handle = handle->next;
            check = handle->data;
            if(check>max){
                *max = check;
            }
            if(check<min){
                *min = check;
            }
        }
        return 0;
    }
}
