#include<stdio.h>
#include<stdlib.h>

void DisplayReverse(Node* head, Node* tail){
    Node* handle = tail;
    while(handle->prev!=head){
        handle = handle->prev;
        printf(" %d", handle->data);
    }
}

void ReverseList(Node* head, Node* tail){
    Node* handle = head;
    Node* temp = NULL;

    //Switching Elements
    while(handle->next!=tail){
        handle = handle->next;
        temp = handle->next;
        handle->next = handle->prev;
        handle->prev = temp;
    }

    // Switching head and tail
    head->prev = head->next;
    head->next = NULL;
    tail->next = tail->prev;
    tail->prev = NULL;

    temp = head;
    head = tail;
    tail = temp;
}
