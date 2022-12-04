#define STARTER_SIZE 100

const char CATEGORIES[5][15] = {
    "StateBoard",
    "CBSE",
    "LateralEntry",
    "Rural",
    "NRI"
};
enum category{StateBoard, CBSE, LateralEntry, Rural, NRI};
typedef enum category Category;

struct student{
    int reg_num;
    char name[30];
    Category categ;
};
typedef struct student Student;

struct node{
    Student data;
    struct node *next;
};
typedef struct node Node;

// LINKED_LISYT HANDLING FUNCTIONS
short isEmpty(Node *head);
Node* createSentinelNode();
Node* createNewNode(Student stud);
Node* findPreviousNodeByRegNum(Node *head, int reg_num, int *exit_status);
void insertFront(Node *head, Node *node);
int insertAfter(Node *head, Node *node, int reg_num);
Node* searchByRegNum(Node *head, int reg_num, int *exit_status);
Student deleteByRegNum(Node *head, int reg_num, int *exit_status);
Node* listByCategory(Node *head, Category categ);
Node** groupByNames(Node *head, int *result_size);
void display(Node *head);
void displayRegNumsOnly(Node *head);
void displayStudent(Student stud);

// UTILITY FUNCTIONS
Student makeStudentByInput(int *exit_status);
int toLowerCase(char c);
short caselessStringCompare(char* s1, char* s2);
void insertInDynArray(Node **arr, int posn, Node *value);
int namePosnInArray(Node **arr, int N, char *name);
