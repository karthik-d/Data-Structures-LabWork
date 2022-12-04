#define STARTER_SIZE 10

struct list{
    int *data;
    int length;
    int capacity;
    short isSorted;
};
typedef struct list List;

List* initializeList();
short isFull(List *list);
short isEmpty(List *list);
void expandList(List *list);
void append(int value, List *list);
int swap(int ind1, int ind2, List *list);
int get(int index, List *list, int *value);
void display(List *list);
int linearSearch(int value, List *list);
int binarySearchRecurser(int value, List *list, int start, int end);
int binarySearch(int value, List *list);
void selectionSort(List *list);
void shellSort(List *list);
