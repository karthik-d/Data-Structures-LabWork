#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// UTILITY FUNCTIONS //

short classifyCharacter(char ch){
    if(ch>='A'&&ch<='Z' || ch>='a'&&ch<='z'){
        return 1;     // For Alphabets
    }
    else if(ch>='0'&&ch<='9'){
        return 2;     // For Numbers
    }
    else if(ch==' '){
        return 3;     // For WhiteSpace
    }
    else if(ch>=0&&ch<=9){
        return 4;     // Actual integers between 0 and 9
    }
    else{
        return 0;     // Others
    }
}

int deducePrecedence(int index){
    if(index<0){
        return index;  // Relay the same error code
    }
    else if(index<=1){
        return 1;    // lowest precedence
    }
    else if(index<=3){
        return 2;     // next precedence
    }
    else{
        return -1;
    }
}

int getOperatorIndex(char ch){
    for(short i=0;i<OPERATORS_COUNT;i++){
        if(ch==PRECEDENCE[i]){
            return i;
        }
    }
    return -1;       // Not an operator
}

// STACK ADT FUNCTIONS //

short isEmpty(Stack *top){
    return (top->next==NULL);
}

Stack* createSentinelStackNode(){
    Stack *handle = (Stack*)malloc(sizeof(Stack));
    handle->next = NULL;
    return handle;
}

Stack* createNewStackNode(Tree *value){
    Stack *handle = (Stack*)malloc(sizeof(Stack));
    handle->data = value;
    handle->next = NULL;
    return handle;
}

void push(Stack *top, Stack *node){
    node->next = top->next;
    top->next = node;
}

Tree* pop(Stack *top, int *exit_status){
    Tree *temp = NULL;
    if(!isEmpty(top)){
        Stack *del_node = top->next;
        temp = del_node->data;
        top->next = top->next->next;
        free(del_node);
        *exit_status = 0;   // Exit Status: Successful
        return temp;
    }
    else{
        *exit_status = -1;   // Exit Status: List Empty
        return temp;
    }
}

Tree* peek(Stack *top, int *exit_status){
    Tree *temp = NULL;
    if(!isEmpty(top)){
        temp = top->next->data;
        *exit_status = 0;   // Exit Status: Successful
        return temp;
    }
    else{
        *exit_status = -1;   // Exit Status: List Empty
        return temp;
    }
}

void displayStack(Stack *top, short asInt){
    Stack *handle = top;
    printf("\nSTACK\n");
    if(isEmpty(top)){
        printf("\nEmpty Stack\n");
    }
    else{
        printf("\nTOP");
        while(handle->next){
            handle = handle->next;
            printf("\n-> ");
            if(asInt){
                printf("%d", handle->data->data);
            }
            else{
                printf("%c", handle->data->data);
            }
        }
        printf("\nEND\n");
    }
}

// TREE ADT FUNCTIONS //

Tree* createNewTreeNode(int value){
    Tree *handle = (Tree*)malloc(sizeof(Tree));
    handle->data = value;
    handle->left = NULL;
    handle->right = NULL;
    return handle;
}

Tree* makeExpressionTree(char *postfix, int *exit_status){
    Tree *node, *node1, *node2;
    Stack *top = createSentinelStackNode();
    char *variables = (char*)malloc(sizeof(char)*strlen(postfix));
    char ch;
    int i=0, result, status, response, class;
    while(*(postfix+i)!='\0'){
        ch = *(postfix+i);
        response = deducePrecedence(getOperatorIndex(ch));
        class = classifyCharacter(ch);
        if(class==1){                   // Alphabet
            node = createNewTreeNode(ch);
            push(top, createNewStackNode(node));     // Store the ASCII of the variable
        }
        else if(class==2){              // Number
            node = createNewTreeNode((int)(ch-48));
            push(top, createNewStackNode(node));
        }
        else if(response!=-1){        // Is an operator
            node1 = pop(top, &status);
            if(status==-1){
                *exit_status = -3;     // Invalid expression
                return NULL;
            }
            node2 = pop(top, &status);
            if(status==-1){
                *exit_status = -3;     // Invalid expression
                return NULL;
            }
            node = createNewTreeNode(ch);
            node->left = node2;
            node->right = node1;
            push(top, createNewStackNode(node));
        }
        else{                          // Non-Fatal Error
            *exit_status = 1;          // Unknown character / Space(s) encountered and ignored
        }
        i++;
    }
    node = pop(top, &status);
    pop(top, &status);                 // Make sure the last element was popped
    if(status!=-1){
        *exit_status = -4;             // Insufficient Operators
    }
    return node;
}

void displayTreeInOrder(Tree *root){
    if(root!=NULL){
        int class = classifyCharacter(root->data);
        int response = deducePrecedence(getOperatorIndex(root->data));
        if(class==0&&response!=-1){
            printf("(", root->data);
        }

        displayTreeInOrder(root->left);
        if(class==1||class==2){
            printf("%c", root->data);
        }
        else if(class==4){
            printf("%d", root->data);
        }
        else if(response!=-1){
            printf("%c", root->data);
        }
        displayTreeInOrder(root->right);

        if(class==0&&response!=-1){
            printf(")", root->data);
        }
    }
    else{
        ;
    }
}

void displayTreePostOrder(Tree *root){
    if(root!=NULL){
        //char *exp = (char*)malloc(sizeof(char)*strlen())
        displayTreePostOrder(root->left);
        displayTreePostOrder(root->right);
        int class = classifyCharacter(root->data);
        int response = deducePrecedence(getOperatorIndex(root->data));
        if(class==1||class==2){
            printf("%c", root->data);
        }
        else if(class==4){
            printf("%d", root->data);
        }
        else if(response!=-1){
            printf("%c", root->data);
        }
    }
    else{
        ;
    }
}

void displayTreePreOrder(Tree *root){
    if(root!=NULL){
        int class = classifyCharacter(root->data);
        int response = deducePrecedence(getOperatorIndex(root->data));
        if(class==1||class==2){
            printf("%c", root->data);
        }
        else if(class==4){
            printf("%d", root->data);
        }
        else if(response!=-1){
            printf("%c", root->data);
        }
        displayTreePreOrder(root->left);
        displayTreePreOrder(root->right);
    }
    else{
        ;
    }
}
