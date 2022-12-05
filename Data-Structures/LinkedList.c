#include<stdio.h>
#include<stdlib.h>
#define STARTER_SIZE 1

struct node{
    int data;
    struct node *next;
};
typedef struct node Node;

Node* CreateHeadNode(){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->next = NULL;
    return handle;
}

Node* CreateNewNode(int value){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->data = value;
    handle->next = NULL;
    return handle;
}

Node* FindPreviousNode(int posn, Node *head, int *exit_status){
    if(posn<1){
        *exit_status = -2;  // Exit Status: Position below lower bound
        return NULL;
    }
    int ctr = 1;
    Node *handle = head;
    while(ctr<posn && handle->next){
        ctr++;
        handle = handle->next;
    }
    if(ctr==posn){
        *exit_status = 0;   // Exit Status: Position Valid
    }
    else{
        *exit_status = -1;  // Exit Status: Position out of upper bound
    }
    return handle; //Always returns valid node. LAST node if posn beyond limit
}

short isEmpty(Node *head){
    return (head->next==NULL);
}

void InsertNodeFirst(Node *node, Node *head){
    node->next = head->next;
    head->next = node;
}

void InsertNodeLast(Node *node, Node *head){
    Node *handle = head;
    while(handle->next){
        handle = handle->next;
    }
    node->next = handle->next; //NULL
    handle->next = node;
}

int InsertNodeAtPosn(int posn, Node *node, Node *head){
    int exit_status;
    Node *previous = FindPreviousNode(posn, head, &exit_status);
    if(exit_status==-2){         // Position below lower bound
        return exit_status;
    }
    else{
        node->next = previous->next;
        previous->next = node;  // Either case, procedure for addition of node is the same
        return exit_status;
    }
}

int DeleteFirstNode(Node *head, int *data){
    if(!isEmpty(head)){
        Node *del_node = head->next;
        head->next = head->next->next;
        *data = del_node->data;
        free(del_node);
        return 0;  // Exit Status: Successful
    }
    else{
        data = NULL;
        return 1;  // Exit Status: List Empty
    }
}

int DeleteLastNode(Node *head, int *data){
    if(!isEmpty(head)){
        Node *del_node, *handle;
        handle = head;
        while(handle->next->next){
            handle = handle->next;
        }
        del_node = handle->next;
        handle->next = handle->next->next;
        *data = del_node->data;
        free(del_node);
        return 0;  // Exit Status: Successful
    }
    else{
        data = NULL;
        return 1;  // Exit Status: List Empty
    }
}

int DeleteNodeFromPosn(int posn, Node *head, int *data){
    if(!isEmpty(head)){
        Node *del_node, *previous;
        int exit_status;
        previous = FindPreviousNode(posn, head, &exit_status);
        if(exit_status){
            return exit_status;  // Exit Status: Position out of bound - Lower or Upper
        }
        else{
            del_node = previous->next;
            previous->next = previous->next->next;
            *data = del_node->data;
            free(del_node);
            return 0;  // Exit Status: Successful
        }
    }
    else{
        data = NULL;
        return 1;  // Exit Status: List Empty
    }
}

Node* SearchByData(int value, Node *head){
    Node *handle = head;
    Node *posns = CreateHeadNode();
    int posn = 0;
    while(handle->next){
        handle = handle->next;
        posn++;
        if(handle->data==value){
            InsertNodeLast(CreateNewNode(posn), posns);
        }
    }
    return posns;
}

void DisplayList(Node *head){
    Node *handle = head;
    if(isEmpty(head)){
        printf("\nEmpty List\n");
    }
    else{
        printf("\nHEAD");
        while(handle->next){
            handle = handle->next;
            printf(" -> ");
            printf("%d", handle->data);
        }
        printf(" -> END\n");
    }
}

void main(){

    Node *main_head = CreateHeadNode();
    char choice_1, choice_2;
    int data, posn, response;

    do{
        printf("\nMAIN MENU\n1-Insert Element\n2-Delete Element\n3-Search By Element\n4-Display\n5-Exit\nEnter Choice: ");
        scanf(" %c", &choice_1);
        switch(choice_1){

            case '1':
                do{
                    printf("\nCurrent List Status");
                    DisplayList(main_head);
                    printf("\nINSERTION\n1-At Beginning\n2-At End\n3-Specify Position\n4-Go Back\nEnter Choice: ");
                    scanf(" %c", &choice_2);
                    switch(choice_2){
                        case '1':
                            printf("\nEnter Data: ");
                            scanf(" %d", &data);
                            InsertNodeFirst(CreateNewNode(data), main_head);
                            printf("\nElement inserted at beginning\n");
                            break;
                        case '2':
                            printf("\nEnter Data: ");
                            scanf(" %d", &data);
                            InsertNodeLast(CreateNewNode(data), main_head);
                            printf("\nElement inserted at end\n");
                            break;
                        case '3':
                            printf("\nEnter Data: ");
                            scanf(" %d", &data);
                            printf("Enter Position: ");
                            scanf(" %d", &posn);
                            response = InsertNodeAtPosn(posn, CreateNewNode(data), main_head);
                            if(response==-2){
                                printf("\nCould not add element. Position below lower bound\n");
                            }
                            else if(response==-1){
                                printf("\nPosition higher than upper bound. Element added to END\n");
                            }
                            else{
                                printf("\nElement inserted at position %d\n", posn);
                            }
                            break;
                        case '4':
                            break;
                        default:
                            printf("\nInvalid Option\n");
                            break;
                    }
                }while(choice_2!='4');
                break;

            case '2':
                do{
                    printf("\nCurrent List Status");
                    DisplayList(main_head);
                    printf("\nDELETION\n1-First Element\n2-Last Element\n3-Specify Position\n4-Go Back\nEnter Choice: ");
                    scanf(" %c", &choice_2);
                    switch(choice_2){
                        case '1':
                            response = DeleteFirstNode(main_head, &data);
                            if(response==1){
                                printf("\nCannot Delete. Empty List\n");
                            }
                            else{
                                printf("\nFirst Element Deleted. Value was %d\n", data);
                            }
                            break;
                        case '2':
                            response = DeleteLastNode(main_head, &data);
                            if(response==1){
                                printf("\nCannot Delete. Empty List\n");
                            }
                            else{
                                printf("\nLast Element Deleted. Value was %d\n", data);
                            }
                            break;
                        case '3':
                            printf("\nEnter Position: ");
                            scanf(" %d", &posn);
                            response = DeleteNodeFromPosn(posn, main_head, &data);
                            if(response<0){
                                printf("\nCould not delete element. Position out of bounds\n");
                            }
                            else if(response==1){
                                printf("\nCannot Delete. Empty List\n");
                            }
                            else{
                                printf("\nElement deleted from position %d. Value was %d\n", posn, data);
                            }
                            break;
                        case '4':
                            break;
                        default:
                            printf("\nInvalid Option\n");
                            break;
                    }
                }while(choice_2!='4');
                break;

            case '3':
                printf("\nEnter Element to Search: ");
                scanf(" %d",&data);
                Node *posns = SearchByData(data, main_head);
                if(isEmpty(posns)){
                    printf("\nNo matching nodes found!");
                }
                else{
                    printf("\nMatching nodes were found at following positions:");
                    DisplayList(posns);
                }
                break;

            case '4':
                printf("\nCurrent List Status");
                DisplayList(main_head);
                break;

            case '5':
                break;

            default:
                printf("\nInvalid Option\n");
                break;
        }
    }while(choice_1!='5');
}
