#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define OPERATORS_COUNT 4

const char PRECEDENCE[] = {'-', '+', '*', '/'};

struct stack{
    int data;
    struct stack *next;
};
typedef struct stack Stack;

// HELPER FUNCTIONS //

void displayExpression(char *expression){
    int i=0;
    char *parser = expression;
    while(*(parser+i)!='\0'){
        printf("%c", *(parser+i));
        i++;
    }
}

short isEmpty(Stack *top){
    return (top->next==NULL);
}

Stack* createSentinelNode(){
    Stack *handle = (Stack*)malloc(sizeof(Stack));
    handle->data = 0;
    handle->next = NULL;
    return handle;
}

Stack* createNewNode(int value){
    Stack *handle = (Stack*)malloc(sizeof(Stack));
    handle->data = value;
    handle->next = NULL;
    return handle;
}

void push(Stack *top, Stack *node){
    node->next = top->next;
    top->next = node;
}

int pop(Stack *top){
    if(isEmpty(top)){
        return -1;  //Empty
    }
    Stack *del = top->next;
    int data = del->data;
    top->next = top->next->next;
    free(del);
    return data;
}

int peek(Stack *top){
    if(isEmpty(top)){
        return -1;  //Empty
    }
    return top->next->data;
}

void display(Stack *top){
    if(isEmpty(top)){
        printf("\nEmpty Stack\n");
        return;
    }
    printf("\nCURRENT STACK\n");
    Stack *handle = top;
    while(handle->next!=NULL){
        handle = handle->next;
        printf("\n->%d", handle->data);
    }
}

short checkBrackets(char* expression){
    Stack *stack = createSentinelNode();
    char *parser = expression;
    int i = 0;
    while(*(parser+i)!='\0'){
        switch(*(parser+i)){
            case ')':
                if(pop(stack)!='('){
                    return 0;
                }
                break;
            case ']':
                if(pop(stack)!='['){
                    return 0;
                }
                break;
            case '}':
                if(pop(stack)!='{'){
                    return 0;
                }
                break;
            case '(':
                push(stack, createNewNode('('));
                break;
            case '[':
                push(stack, createNewNode('['));
                break;
            case '{':
                push(stack, createNewNode('{'));
                break;
        }
        i++;
    }
    return 1;
}

int findCharInArray(const char *array, char ch){
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

short classifyCharacter(char ch){
    if(ch>='0' && ch<='9'){
        return 4;   // Digit between 0 and 9
    }
    else if(ch=='('){
        return 5;   //Opening
    }
    else if(ch==')'){
        return 6;   //Closing
    }
    if(ch>='A'&&ch<='Z' || ch>='a'&&ch<='z'){
        return 7;  //Alphabet
    }
    else{
        return findCharInArray(PRECEDENCE, ch);   // Index of Operator
    }
}

char* getPostfix(char* expression){
    Stack *stack = createSentinelNode();
    char *parser = expression;
    char* output = (char*)malloc(sizeof(char)*sizeof(expression));
    int i = 0, response, result, j=0;
    while(*(parser+i)!='\0'){
        response = classifyCharacter(*(parser+i));
        if (response==-1){
            ; //INVALID CHARACTER
        }
        else if(response<4){
            // Operator
            result = findCharInArray(PRECEDENCE, peek(stack));
            while(result>=response){  // If it is not an operator, -1 is returned, which is lesser than 0 response and loop exits anyway
                *(output+j) = pop(stack);
                j++;
                result = findCharInArray(PRECEDENCE, peek(stack));
            }
            //Current Operator
            push(stack, createNewNode(PRECEDENCE[response]));
        }
        else if(response==4 ||  response==7){
            // Number or Operand
            *(output+j) = *(parser+i);
            j++;
        }
        else if(response==5){
            // Opening
            push(stack, createNewNode(*(parser+i)));
        }
        else if(response==6){
            // Closing
            result = pop(stack);
            while(result!='('){
                *(output+j) = result;
                j++;
                result = pop(stack);
            }
        }
        i++;
    }
    // FLUSH REMAINING OPERATORS
    result = pop(stack);
    while(!isEmpty(stack)){
        *(output+j) = (char)result;
        j++;
        result = pop(stack);
    }
    if(result!=-1){
        *(output+j) = (char)result;
    }
    return output;
}

int performOperation(int op1, int op2, int operator){
    switch(operator){
        case 0:
            return op1-op2;
        case 1:
            return op1+op2;
        case 2:
            return op1*op2;
        case 3:
            return op1/op2;
        default:
            return -1;
    }
}

int evaluatePostfix(char *postfix){
    Stack *stack = createSentinelNode();
    char *parser = postfix;
    int op1, op2, num;
    int i = 0, response;
    while(*(parser+i)!='\0'){
        response = classifyCharacter(*(parser+i));
        if (response==-1){
            ; //INVALID CHARACTER
        }
        else if(response<4){
            // Operator
            op2 = pop(stack);
            op1 = pop(stack);
            push(stack, createNewNode(performOperation(op1, op2, response)));
        }
        else if(response==4){
            // Number
            num = (*(parser+i)) - 48;
            push(stack, createNewNode(num));
        }
        i++;
    }
    return pop(stack);
}

/*int deducePrecedence(int index){
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
    pop(&top, &status);                 // Make sure the last element was popped
    if(status!=-1){
        *exit_status = -4;             // Insufficient Operators
    }
    return result;
}*/

void main(){
    printf("\n%d\n", checkBrackets("([13{([asa])33}]34)"));
    printf("\n%d\n", checkBrackets("([13{([asa])33]]34)"));
    printf("\n%d\n", checkBrackets("([]13{([asa])33}]34)"));
    printf("\n%s\n", getPostfix("(1+2)*(3*4-5)*6/7"));
    printf("\n%d\n", evaluatePostfix("234+*6-"));
}
