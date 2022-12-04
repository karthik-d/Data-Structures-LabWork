#include<stdio.h>
#include<stdlib.h>

// HELPER FUNCTIONS //

Student makeStudentByInput(int *exit_status){
    Student stud;
    printf("\nEnter Register Number: ");
    scanf(" %d", &stud.reg_num);
    printf("Enter Student Name: ");
    scanf(" %s", &stud.name);
    printf("Choose Category");
    for(int i=0;i<5;i++){
        printf("\n%d - %s", (i+1), CATEGORIES[i]);
    }
    printf("\nEnter Choice: ");
    scanf(" %d", &stud.categ);
    if(stud.categ>=1 && stud.categ<=5){
        *exit_status = 0;
        stud.categ--;
        return stud;
    }
    else{
        *exit_status = -1;
        Student empty;
        return empty;    // Unsuccessful
    }
}

int toLowerCase(char c){
    int ascii = (int)c;
    if(ascii>=65&&ascii<=90){
        return ascii+32;
    }
    else{
        return ascii;  // Return lowercase and other characters as it is
    }
}

short caselessStringCompare(char* s1, char* s2){
    while(*s1!='\0' && *s2!='\0'){
        if(toLowerCase(*s1)==toLowerCase(*s2)){
            ;
        }
        else{
            return 0;    // Not Equal
        }
        s1++;
        s2++;
    }
    if(*s1==*s2){   // Both have terminated
        return 1;   // Equal
    }
    else{
        return 0;
    }
}

void insertInDynArray(Node **arr, int posn, Node *value){
    if(posn%STARTER_SIZE==0){
        arr = (Node**)realloc(arr, sizeof(Node*)*(posn+STARTER_SIZE));
    }
    *(arr+posn) = value;
}

int namePosnInArray(Node **arr, int N, char *name){
    for(int i=0;i<N;i++){
        if(caselessStringCompare((*(arr+i))->next->data.name, name)){
            return i;
        }
    }
    return -1;  // Not found
}

short isEmpty(Node *head){
    return (head->next==NULL);
}

Node* createSentinelNode(){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->next = NULL;
    return handle;
}

Node* createNewNode(Student stud){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->data = stud;
    handle->next = NULL;
    return handle;
}

Node* findPreviousNodeByRegNum(Node *head, int reg_num, int *exit_status){
    Node *handle = head;
    while(handle->next){
        if(handle->next->data.reg_num==reg_num){
            *exit_status = 0;  // Exit Status: Found
            return handle;
        }
        handle = handle->next;
    }
    *exit_status = -1;  // Exit Status: Not Found
    return NULL;
}

void insertFront(Node *head, Node *node){
    node->next = head->next;
    head->next = node;
}

int insertAfter(Node *head, Node *node, int reg_num){
    int exit_status;
    Node *previous = searchByRegNum(head, reg_num, &exit_status);
    if(exit_status){           // Node not found
        ;
    }
    else{
        node->next = previous->next;
        previous->next = node;
    }
    return exit_status;    // Relay the same exit status
}

Node* searchByRegNum(Node *head, int reg_num, int *exit_status){
    Node *handle = head;
    while(handle->next){
        handle = handle->next;
        if(handle->data.reg_num==reg_num){
            *exit_status = 0;  // Exit Status: Found
            return handle;
        }
    }
    *exit_status = -1;  // Exit Status: Not Found
    return NULL;
}

Student deleteByRegNum(Node *head, int reg_num, int *exit_status){
    Student data;
    if(!isEmpty(head)){
        Node *del_node, *previous;
        previous = findPreviousNodeByRegNum(head, reg_num, exit_status);
        if(*exit_status){   // Exit Status Not 0. Error Occurred
            return data;    // Dummy Data
        }
        else{
            del_node = previous->next;
            previous->next = previous->next->next;
            data = del_node->data;
            free(del_node);
            return data;   // Carries previous Exit Status
        }
    }
    else{
        *exit_status = 1;  // Exit Status: Empty List
        return data;       // Dummy Data
    }
}

Node* listByCategory(Node *head, Category categ){
    Node *handle = head;
    Node *results = createSentinelNode();
    while(handle->next){
        handle = handle->next;
        if(handle->data.categ == categ){
            insertFront(results, createNewNode(handle->data));
        }
    }
    return results;
}

Node** groupByNames(Node *head, int *result_size){
    Node *handle = head;
    Node *arr_head;
    Node **result = (Node**)malloc(sizeof(Node*)*STARTER_SIZE);
    int response;
    *result_size = 0;
    while(handle->next!=NULL){
        handle = handle->next;
        response = namePosnInArray(result, *result_size, handle->data.name);
        if(response==-1){
            arr_head = createSentinelNode();
            insertFront(arr_head, createNewNode(handle->data));    // Least expensive insertion
            insertInDynArray(result, *result_size, arr_head);
            (*result_size)++;   // Since a new array element was created
        }
        else{
            insertFront(*(result+response), createNewNode(handle->data));   // Least expensive insertion
        }
    }
    return result;
}

void display(Node *head){
    Node *handle = head;
    if(isEmpty(head)){
        printf("\nEmpty List\n");
    }
    else{
        int ctr = 0;
        while(handle->next){
            handle = handle->next;
            ctr++;
            printf("\nSTUDENT %d", ctr);
            printf("\n--------------------");
            displayStudent(handle->data);
            printf("\n--------------------\n");
        }
    }
}

void displayRegNumsOnly(Node *head){
    Node *handle = head;
    if(isEmpty(head)){
        printf("\nEmpty List\n");
    }
    else{
        printf("\nHEAD -> ");
        while(handle->next){
            handle = handle->next;
            printf(" %d ->", handle->data.reg_num);
        }
        printf(" END\n");
    }
}

void displayStudent(Student stud){
    printf(" \nRegister No.: %d", stud.reg_num);
    printf(" \nStudent Name: %s", stud.name);
    printf(" \nCategory: %s", CATEGORIES[stud.categ]);
}
