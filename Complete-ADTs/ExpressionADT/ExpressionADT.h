#define OPERATORS_COUNT 4

const char PRECEDENCE[] = {'-', '+', '*', '/'};

struct tree{
    int data;
    struct tree *left;
    struct tree *right;
};
typedef struct tree Tree;

struct stack{
    Tree *data;
    struct stack *next;
};
typedef struct stack Stack;

// STACK ADT FUNCTIONS //
short isEmpty(Stack*);
Stack* createSetninelStackNode();
Stack* createNewStackNode(Tree*);
void push(Stack*, Stack*);
Tree* pop(Stack*, int*);
Tree* peek(Stack*, int*);
void displayStack(Stack*, short);
short flushStack(Stack*, char*, int);

// TREE ADT FUNCTIONS //
Tree* createNewTreeNode(int);
Tree* makeExpressionTree(char*, int*);
void displayTreeInOrder(Tree*);
void displayTreePostOrder(Tree*);
void displayTreePreOrder(Tree*);

// UTILITY FUNCTION //
short classifyCharacter(char);
int deducePrecedence(int);
int getOperatorIndex(char);
