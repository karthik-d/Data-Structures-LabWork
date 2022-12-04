#include<limits.h>

#define STARTER_SIZE 1
#define INFINITY INT_MAX

// WRAP ALL GRAPH CONTENTS ALONG WITH THE LATEST INDEX INTO A GRAPH STRUCTURE
// THEN USED STATIC INT to HANDLE INDICES

struct node{
    int v_index;
    int weight;
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

struct graph{
    Vertex *start;
    int num_vertices;
};
typedef struct graph Graph;

struct table{
    short known;
    int distance;
    int predecessor_index;    // -1 is unknown
};
typedef struct table Table;
