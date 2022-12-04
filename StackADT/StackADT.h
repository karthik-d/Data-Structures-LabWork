#define OPERATORS_COUNT 4

const char PRECEDENCE[] = {'-', '+', '*', '/'};

struct stack{
    int data;
    struct stack *next;
};
typedef struct stack Stack;

// STACK ADT APPLICATIONS //
//the address of the top pointer is passed
//whenever the top of the stack is being modified
short isEmpty(Stack*);
Stack* createNewNode(int);
void push(Stack**, Stack*);
int pop(Stack**, int*);
int peek(Stack*, int*);
void display(Stack*, short);
short flushStack(Stack*, char*, int);

// APPLICATION FUNCTIONS //
int deducePrecedence(int);
int getOperatorIndex(char);
int operate(char, int, int);
char* convertToPostfix(char*, int*);
int evaluatePostfix(char*, int*, int*);

// UTILITY FUNCTIONS //
short classifyCharacter(char);
void displayExpression(char*);
int findCharInArray(char*, char);
int* getUnknownValues(char*);
