struct node{
    char *job_num;
    int burst_time;
    struct node *next;
};
typedef struct node Node;

struct queue{
    // int *arr;
    Node *front;
    Node *rear;
};
typedef struct queue Queue;

short isEmpty(Queue*);
Queue* initializeQueue();
void enqueue(Queue*, Node*);
char* dequeue(Queue*, int*);
void display(Queue*);

Node* createSentinelNode();
Node* createDataNode(char*, int);

// Application Functions
int getWaitingTime(Queue *Q);
Queue* getFasterQueue(Queue* Q1, Queue* Q2, int *diff);
