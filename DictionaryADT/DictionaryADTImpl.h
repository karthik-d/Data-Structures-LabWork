#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// UTILITY FUNCTIONS //
int power(int base, int exp){
    int result = 1;
    for(int i=0;i<exp;i++){
        result *= base;
    }
    return result;
}

// MUST BE A POINTER SINCE THE SIZE OF STRUCTURE WILL BE UNKNOWN FOR ITS WRAPPER
WordMeaning* createWord(char *word, char *meaning){
    WordMeaning *word_ins = (WordMeaning*)malloc(sizeof(WordMeaning));
    strcpy(word_ins->word, word);
    strcpy(word_ins->meaning, meaning);
    return word_ins;
}

short isEmpty(Dictionary* root){
    return root==NULL;
}

// CREATE AVL TREE NODE
Dictionary* createWordNode(WordMeaning *word){
    Dictionary *handle = (Dictionary*)malloc(sizeof(Dictionary));
    handle->word = word;
    handle->height = 0;
    handle->left = NULL;
    handle->right = NULL;
    return handle;
}

// SIMPLE GETTER FUNCTION
int getDictionaryHeight(Dictionary *dictionary){
    if(isEmpty(dictionary)){
        return -1;     // This has to be -1 (reason in below function)
    }
    else{
        return dictionary->height;
    }
}

// RECURSIVE HEIGHT CALCULATION
int getTreeHeight(Dictionary* root){
    int left_height = getDictionaryHeight(root->left);
    int right_height = getDictionaryHeight(root->right);
    if(left_height>=right_height){        // Deduce new height of root
        return left_height+1;             // If a new Dictionary is inseted, its height becomes -1+1 = 0 //
    }
    else{
        return right_height+1;
    }
}

Dictionary* singleRotateWithLeft(Dictionary* n2){
    Dictionary *n1 = n2->left;
    n2->left = n1->right;             // MUST HAPPEN FIRST
    n1->right = n2;
    n2->height = getTreeHeight(n2);   // MUST HAPPEN FIRST SINCE THIS IS A SUBTREE OF n1
    n1->height = getTreeHeight(n1);
    return n1;
}

Dictionary* singleRotateWithRight(Dictionary *n2){
    Dictionary *n1 = n2->right;
    n2->right = n1->left;
    n1->left = n2;
    n2->height = getTreeHeight(n2);    // MUST HAPPEN FIRST SINCE THIS IS A SUBTREE OF n1
    n1->height = getTreeHeight(n1);
    return n1;                         // Because n1 is now the new root of this subtree
}

Dictionary* doubleRotateWithLeft(Dictionary* n3){
    n3->left = singleRotateWithRight(n3->left);   // First rotate n2 and store it in the right of n3
    n3 = singleRotateWithLeft(n3);
    return n3;
}

Dictionary* doubleRotateWithRight(Dictionary *n3){
    n3->right = singleRotateWithLeft(n3->right);
    n3 = singleRotateWithRight(n3);
    return n3;
}

Dictionary* insertWordNode(Dictionary *word_node, Dictionary *root){
    if(isEmpty(root)){
        root = word_node;   // Placing the new Node //
    }
    else if(strcmp(word_node->word->word, root->word->word)<0){  // New word is smaller
        root->left = insertWordNode(word_node, root->left);
        if(getDictionaryHeight(root->left)-getDictionaryHeight(root->right)==2){  // Checking unbalanced condition
            if(strcmp(word_node->word->word, root->left->word->word)<0){   // New word is smaller
                // Insertion occurred at LEFT of LEFT
                root = singleRotateWithLeft(root);
            }
            else{
                // Insertion occurred at RIGHT of LEFT
                root = doubleRotateWithLeft(root);
            }
        }
    }
    else{
        // New word is larger than root
        root->right = insertWordNode(word_node, root->right);
        if(getDictionaryHeight(root->left)-getDictionaryHeight(root->right)==-2){  // If height has increased
            if(strcmp(word_node->word->word, root->right->word->word)>0){   // New word is greater
                // Insertion occurred at RIGHT of RIGHT
                root = singleRotateWithRight(root);
            }
            else{
                // Insertion occurred at LEFT of RIGHT
                root = doubleRotateWithRight(root);
            }
        }
    }
    root->height = getTreeHeight(root);       // Deduce new height of root
    return root;
}

WordMeaning* search(char *word, Dictionary *root){
    if(isEmpty(root)){
        return NULL;  // Not Found
    }
    int comparison = strcmp(word, root->word->word);
    if(comparison==0){
        return root->word;
    }
    else if(comparison<0){
        return search(word, root->left);
    }
    else{
        return search(word, root->right);
    }
}

void displayWord(WordMeaning *word){
    printf("\n%s\n%s\n", word->word, word->meaning);
}

void dispEntireLevel(Dictionary *root, int level){
    if(isEmpty(root)){
        return;
    }
    static int level_const = 0;
    static int disp_ctr = 0;
    // Keeps moving to the child nodes unitl level becomes 0
    // When level is 0, the node with intended height has been reached
    if(level==0){
        disp_ctr++;
        if(disp_ctr%(power(2, level_const))==0){
            if(level_const!=0){
                printf("\n------------------\n");
            }
            printf("\n---- LEVEL %d ----\n", level_const);
            level_const++;
        }
        displayWord(root->word);
    }
    else{
        dispEntireLevel(root->left, level-1);
        dispEntireLevel(root->right, level-1);
    }
}

void dispHierarchical(Dictionary *root){
    int height = getDictionaryHeight(root);
    // Will give each height from 0 to h. Hence, parses all depths
    for(int i=0;i<=height;i++){
        dispEntireLevel(root, i);
    }
    printf("\n------------------\n");
}
