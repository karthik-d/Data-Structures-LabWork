#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};
typedef struct node Node;

short isEmpty(Node *head){
    return (head->next==NULL);
}

Node* createSentinelNode(){
    Node *sentinel = (Node*)malloc(sizeof(Node));
    sentinel->next = NULL;
    sentinel->data = 0;
    return sentinel;
}

Node* createNewNode(int value){
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = value;
    return node;
}

void insertStart(Node *head, Node *node){
    if(isEmpty(head)){
        head->next = node;
        node->next = head;
    }
    else{
        node->next = head->next;
        head->next = node;
    }
}

void insertEnd(Node *head, Node *node){
    if(isEmpty(head)){
        head->next = node;
        node->next = head;
    }
    else{
        Node *handle = head;
        while(handle->next!=head){
            handle = handle->next;
        }
        handle->next = node;
        node->next = head;
    }
}

int insertAt(Node *head, Node *node, int posn){   // Push the existing element at that position ahead
    Node *handle = head;
    int ctr = 1;
    while(posn>ctr && handle->next!=head){
        handle = handle->next;
        ctr++;
    }
    // handle is now the previous element from given posn
    if(posn==ctr){
        node->next = handle->next;
        handle->next = node;
    }
    else if(handle->next==head){
        insertEnd(head, node);
    }
    return 0;
}



int deleteStart(Node *head){
    if(isEmpty(head)){
        return -1; // Empty List
    }
    Node *temp = head->next;
    int data = temp->data;
    head->next = head->next->next;
    free(temp);
    if(head==head->next){
        head->next = NULL;
    }
    return data;
}

int deleteEnd(Node *head){
    if(isEmpty(head)){
        return -1; // Empty List
    }
    Node *handle = head;
    while(handle->next->next!=head){
        handle = handle->next;
    }
    Node *temp = handle->next;
    int data = temp->data;
    handle->next = head;
    if(head->next==head){
        head->next = NULL;
    }
    return data;
}

void display(Node *head){
    if(isEmpty(head)){
        printf("\nEmpty List\n");
        return;
    }
    printf("\n");
    Node *handle = head;
    while(handle->next!=head){
        handle = handle->next;
        printf("-> %d ", handle->data);
    }
}

void main(){
    Node *head = createSentinelNode();
    display(head);
    insertStart(head, createNewNode(5));
    insertStart(head, createNewNode(6));
    insertEnd(head, createNewNode(7));
    insertEnd(head, createNewNode(8));
    deleteEnd(head);
    deleteStart(head);
    insertStart(head, createNewNode(9));
    display(head);
    insertAt(head, createNewNode(11), 100);
    insertAt(head, createNewNode(22), 1);
    insertAt(head, createNewNode(62), 6);
    display(head);
}
