struct node{
    int v_index;
    struct node *next;
};
typedef struct node Node;

struct vertex{
    int index;
    int label;
    Node *edges;
    struct vertex *next;
};
typedef struct vertex Vertex;

struct stack_node{
    Vertex *data;
    struct stack_node *next;
};
typedef struct stack_node StackNode;

struct queue_node{
    Vertex *data;
    struct queue_node *next;
};
typedef struct queue_node QueueNode;
