struct word_meaning{
    char word[16];
    char meaning[100];
};
typedef struct word_meaning WordMeaning;

struct dictionary{
    WordMeaning *word;
    int height;
    struct dictionary *left;
    struct dictionary *right;
};
typedef struct dictionary Dictionary;

// AVL Tree Handling Functions //
WordMeaning* createWord(char*, char*);
short isEmpty(Dictionary*);
Dictionary* createWordNode(WordMeaning*);
int getDictionaryHeight(Dictionary*);
int getTreeHeight(Dictionary*);
Dictionary* singleRotateWithLeft(Dictionary*);
Dictionary* singleRotateWithRight(Dictionary*);
Dictionary* doubleRotateWithLeft(Dictionary*);
Dictionary* doubleRotateWithRight(Dictionary*);
Dictionary* insertWordNode(Dictionary*, Dictionary*);
WordMeaning* search(char*, Dictionary*);
void dispEntireLevel(Dictionary*, int);
void dispHierarchical(Dictionary*);

// UTILITY FUNCTIONS //
void displayWord(WordMeaning*);
int power(int, int);
