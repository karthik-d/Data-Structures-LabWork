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
    else{
        return 0;     // Others
    }
}

void displayExpression(char *expression){
    int i=0;
    char *parser = expression;
    while(*(parser+i)!='\0'){
        printf("%c", *(parser+i));
        i++;
    }
}

int findCharInArray(char *array, char ch){
    int i=0;
    char *parser = array;
    while(*(parser+i)!='\0'){
        if(*(parser+i)==ch){
            return i;
        }
        i++;
    }
    return -1;      // Not Found
}

int* getUnknownValues(char *expression){
    int size = strlen(expression);
    int *values = (int*)malloc(sizeof(int)*size);
    char *variables = (char*)malloc(sizeof(char)*size);
    char *parser = expression;
    char ch;
    int i=0, j=0, num;
    printf("\n");
    while(*(parser+i)!='\0'){
        ch = *(parser+i);
        if(classifyCharacter(ch)==1 && findCharInArray(variables, ch)==-1){
            *(variables+j) = ch;
            printf("Enter Value for '%c': ", ch);
            scanf(" %d", &num);
            *(values+j) = num;
            j++;
        }
        i++;
    }
    return values;
}

// STACK ADT FUNCIONS //

short isEmpty(Stack *top){
    return (top==NULL);
}

Stack* createNewNode(int value){
    Stack *handle = (Stack*)malloc(sizeof(Stack));
    handle->data = value;
    handle->next = NULL;
    return handle;
}

void push(Stack **top, Stack *node){
    node->next = *top;
    *top = node;
}

int pop(Stack **top, int *exit_status){
    int temp;
    if(!isEmpty(*top)){
        Stack *del_node = *top;
        temp = del_node->data;
        *top = (*top)->next;
        free(del_node);
        *exit_status = 0;   // Exit Status: Successful
        return temp;
    }
    else{
        *exit_status = -1;   // Exit Status: List Empty
        return 0;
    }
}

int peek(Stack *top, int *exit_status){
    int temp = 0;
    if(!isEmpty(top)){
        temp = top->data;
        *exit_status = 0;   // Exit Status: Successful
        return temp;
    }
    else{
        *exit_status = -1;   // Exit Status: List Empty
        return temp;
    }
}

void display(Stack *top, short asInt){
    Stack *handle = top;
    printf("\nSTACK\n");
    if(isEmpty(top)){
        printf("\nEmpty Stack\n");
    }
    else{
        printf("\nTOP");
        while(handle){
            printf("\n-> ");
            if(asInt){
                printf("%d", handle->data);
            }
            else{
                printf("%c", handle->data);
            }
            handle = handle->next;
        }
        printf("\nEND\n");
    }
}

// APPLICATION FUNCTIONS //

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

short flushStack(Stack *top, char *expression, int posn){
    char ch;
    int status;
    ch = pop(&top, &status);
    while(status!=-1){
        if(ch=='('){
            return -2;    // Exit Status: Excess Opening Parentheses
        }
        *(expression+posn) = ch;
        posn++;
        ch = pop(&top, &status);
    }
    return 0;    // Exit Status: Successful
}

int operate(char operator, int op1, int op2){
    int index = getOperatorIndex(operator);
    switch(index){
        case 0:
            return op1-op2;
        case 1:
            return op1+op2;
        case 2:
            return op1*op2;
        case 3:
            return op1/op2;
    }
}

char* convertToPostfix(char *infix, int *exit_status){
    Stack *top = NULL;
    char *postfix = (char*)malloc(sizeof(char)*strlen(infix));
    char *parser = infix;
    int i = 0, j=0;
    int response, status, num, class;
    char ch, curr;
    while(*(parser+i)!='\0'){
        curr = *(parser+i);
        response = deducePrecedence(getOperatorIndex(curr));
        class = classifyCharacter(curr);
        if(response!=-1){
            ch = peek(top, &status);
            while(status==0 && deducePrecedence(getOperatorIndex(ch))>=response){
                *(postfix+j) = pop(&top, &status);
                j++;
                ch = peek(top, &status);
            }
            push(&top, createNewNode(curr));
        }
        else if(curr=='('){
            push(&top, createNewNode(curr));
        }
        else if(curr==')'){
            ch = pop(&top, &status);
            while(ch!='('){
                *(postfix+j) = ch;
                j++;
                ch = pop(&top, &status);
                if(status==-1){
                    *exit_status = -1;  // Exit Status: Excess Closing Parentheses
                    return postfix;
                }
            }
        }
        else if(class==1 || class==2){
            *(postfix+j) = curr;      // Must be operand
            j++;
        }
        else{
            *exit_status = 1;          // Unknown character / Space(s) encountered and ignored
        }
        //display(top);
        i++;
    }
    *exit_status = flushStack(top, postfix, j);
    return postfix;
}

int evaluatePostfix(char *postfix, int *unknowns, int *exit_status){
    Stack *top = NULL;
    char *variables = (char*)malloc(sizeof(char)*strlen(postfix));
    int i=0, j=0, class, result, status, response, val1, val2;
    char ch;
    while(*(postfix+i)!='\0'){
        ch = *(postfix+i);
        response = deducePrecedence(getOperatorIndex(ch));
        class = classifyCharacter(ch);
        if(class==1){
            result = findCharInArray(variables, ch);
            if(result==-1){
                *(variables+j) = ch;
                push(&top, createNewNode(unknowns[j]));
                j++;
            }
            else{
                push(&top, createNewNode(unknowns[result]));
            }
        }
        else if(class==2){
            push(&top, createNewNode((int)(ch-48)));
        }
        else if(response!=-1){
            val1 = pop(&top, &status);
            if(status==-1){
                *exit_status = -3;     // Invalid expression
                return 0;
            }
            val2 = pop(&top, &status);
            if(status==-1){
                *exit_status = -3;     // Invalid expression
                return 0;
            }
            result = operate(ch, val2, val1);
            push(&top, createNewNode(result));
        }
        else{
            *exit_status = 1;          // Unknown character / Space(s) encountered and ignored
        }
        i++;
    }
    result = pop(&top, &status);
    if(!isEmpty(top)){
        *exit_status = -4;             // Insufficient Operators
    }
    return result;
}
