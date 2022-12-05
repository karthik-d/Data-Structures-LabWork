#include<stdio.h>
#include<stdlib.h>

struct node{
    int exp;
    int coeff;
    struct node *next;
};
typedef struct node Node;

short isEmpty(Node *head){
    return (head->next==NULL);
}

Node* createSentinelNode(){
    Node *sentinel = (Node*)malloc(sizeof(Node));
    sentinel->next = NULL;
    sentinel->exp = 0;
    sentinel->coeff = 0;
    return sentinel;
}

Node* createNewNode(int coeff, int exp){
    Node *term = (Node*)malloc(sizeof(Node));
    term->exp = exp;
    term->coeff = coeff;
    term->next = NULL;
    return term;
}

int insertInSortedList(Node *head, Node *node){
    Node *handle = head;
    if(node->coeff==0){
        return 1;   // Zero Term
    }
    while(handle->next!=NULL){
        handle = handle->next;
        if(handle->exp < node->exp){
            node->next = handle->next;
            handle->next = node;
            return 0;
        }
        else if(handle->exp == node->exp){
            handle->coeff += node->coeff;
            return 0;
        }
    }
    node->next = handle->next;  // At end
    handle->next = node;
    return 0;    // No Error
}

void display(Node *head){
    if(isEmpty(head)){
        printf("0");
        return;
    }
    Node *handle = head;
    while(handle->next!=NULL){
        handle = handle->next;
        printf("%dx^%d + ", handle->coeff, handle->exp);
    }
    printf("\b\b\n");
}

Node* addPolynomials(Node *A, Node *B){
    Node *C = createSentinelNode();
    int num;
    A = A->next;
    B = B->next;   // Skip the sentinel nodes
    while(A!=NULL && B!=NULL){
        if(A->exp > B->exp){
            insertInSortedList(C, createNewNode(A->coeff, A->exp));
            A = A->next;
        }
        else if(A->exp < B->exp){
            insertInSortedList(C, createNewNode(B->coeff, B->exp));
            B = B->next;
        }
        else{
            // Must be equal
            num = A->coeff+B->coeff;
            if(num!=0){
                insertInSortedList(C, createNewNode(num, A->exp));
            }
            A = A->next;
            B = B->next;
        }
    }
    while(A!=NULL){
        insertInSortedList(C, A);
        A = A->next;
    }
    while(B!=NULL){
        insertInSortedList(C, B);
        B = B->next;
    }
    return C;
}

Node* multiplyPolynomials(Node *A, Node *B){
    Node *C = createSentinelNode();
    Node *B_handle = B->next;
    int num;
    A = A->next;    // Skip the sentinel nodes
    while(A!=NULL){
        B_handle = B->next;
        while(B_handle!=NULL){
            insertInSortedList(C, createNewNode(A->coeff*B_handle->coeff, A->exp+B_handle->exp));
            B_handle = B_handle->next;
        }
        A = A->next;
    }
    return C;
}

void main(){
    Node *A = createSentinelNode();
    Node *B = createSentinelNode();
    Node *C;

    insertInSortedList(A, createNewNode(3, 3));
    insertInSortedList(A, createNewNode(6, 1));
    insertInSortedList(A, createNewNode(9, 0));

    insertInSortedList(B, createNewNode(9, 3));
    insertInSortedList(B, createNewNode(8, 2));
    insertInSortedList(B, createNewNode(7, 1));
    insertInSortedList(B, createNewNode(2, 0));

    display(A);
    display(B);
    printf("\nPRODUCT\n");
    C = multiplyPolynomials(A, B);
    display(C);
    printf("\nSUM\n");
    C = addPolynomials(A, B);
    display(C);

}
