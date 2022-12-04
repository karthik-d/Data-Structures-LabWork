struct employee{
    char name[25];
    int id;
    int salary;
};
typedef struct employee Employee;

struct priority_q{
    Employee *employees;
    int capacity;
    int size;
};
typedef struct priority_q PriorityQ;

Employee makeEmployee(int, char*, int);
PriorityQ* createEmptyQueue(int);
short isFull(PriorityQ*);
short isEmpty(PriorityQ*);
void expandQueue(PriorityQ*);
int enqueue(PriorityQ *, Employee);
Employee dequeue(PriorityQ*, int*);
void displayEmployee(Employee);
void display(PriorityQ*);
