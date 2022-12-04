#include<stdio.h>
#include<stdlib.h>

#define MIN_STACK_SIZE 5
#define EMPTY_STACK -1

typedef stack_dtype int;

struct StackRecord{
    int capacity;
    int top_of_stack;
    stack_dtype *contents;
}
typedef Stack struct StackRecord;

Stack* createStack(int size, int *exit_status){
    Stack *stack;
    if(size<MIN_STACK_SIZE){
        *exit_status = -1;   // Size too less
        return NULL;
    }
    else{
        stack = (Stack*)malloc(sizeof(Stack));
        stack->contents = (stack_dtype*)malloc(sizeof(stack_dtype)*size);
        stack->capacity = size;
        *exit_status = 0;    // Successful
        return stack;
    }
}
