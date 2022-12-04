struct vertex;
struct neighbor;

struct vertex{
  int index;
  int label;
  struct neighbor *neighbors;
  struct vertex *next;
};
typedef struct vertex Vertex;

struct neighbor{
  Vertex *vertex;
  struct neighbor *next;
};
typedef struct neighbor Neighbor;

struct graph{
  Vertex *vertex;   // NOT SENTINEL
  int num_vertices;
};
typedef struct graph Graph;

struct stack_node{
  Vertex *node;
  struct stack_node *next;
};
typedef struct stack_node StackNode;

struct stack{
  StackNode *top;
  int size;
};
typedef struct stack Stack;

struct queue_node{
  Vertex *node;
  struct queue_node *next;
};
typedef struct queue_node QueueNode;

struct queue{
  QueueNode *front;
  QueueNode *rear;
  int size;
};
typedef struct queue Queue;
