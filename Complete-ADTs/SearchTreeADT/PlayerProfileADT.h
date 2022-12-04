char ROLES[][10] = {"Batsman", "Bowler"};

struct playerInfo{
    char name[30];
    int role;
    float run_rate;
};
typedef struct playerInfo Player;

struct playerProfile{
    Player player;
    struct playerProfile *left;
    struct playerProfile *right;
};
typedef struct playerProfile Node;

// UTILITY FUNCTIONS //
Player makePlayer();
void displayPlayer(Player);

//SEARCH TREE FUNCTIONS //
Node* createNewNode(Player);
Node* insert(Node*, Node*);
Node* search(char*, Node*);
Node* findMinNode(Node*);
Node* delete(char*, Node*);
void display(Node*, int);
void preOrder(Node*);
void inOrder(Node*);
void postOrder(Node*);
