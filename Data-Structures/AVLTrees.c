// DO NOT USE SENTINEL NODE HERE //

#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    int height;
    struct node *left;
    struct node *right;
};
typedef struct node Node;

short isEmpty(Node* root){
    return root==NULL;
}

Node* createNewNode(int value){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->data = value;
    handle->height = 0;
    handle->left = NULL;
    handle->right = NULL;
    return handle;
}

int getNodeHeight(Node *node){
    if(node==NULL){
        return -1;     // This has to be -1
    }
    else{
        return node->height;
    }
}

int getTreeHeight(Node* root){
    int left_height = getNodeHeight(root->left);
    int right_height = getNodeHeight(root->right);
    if(left_height>=right_height){        // Deduce new height of root
        return left_height+1;             // If a new node is inseted, its height becomes -1+1 = 0 //
    }
    else{
        return right_height+1;
    }
}

Node* singleRotateWithLeft(Node* n2){
    Node *n1 = n2->left;
    n2->left = n1->right;
    n1->right = n2;
    n2->height = getTreeHeight(n2);   // MUST HAPPEN FIRST SINCE THIS IS A SUBTREE OF n1
    n1->height = getTreeHeight(n1);
    return n1;
}

Node* singleRotateWithRight(Node *n2){
    Node *n1 = n2->right;
    n2->right = n1->left;
    n1->left = n2;
    n2->height = getTreeHeight(n2);    // MUST HAPPEN FIRST SINCE THIS IS A SUBTREE OF n1
    n1->height = getTreeHeight(n1);
    return n1;
}

Node* doubleRotateWithLeft(Node* n3){
    n3->left = singleRotateWithRight(n3->left);   // First rotate n2 and store it in the right of n3
    n3 = singleRotateWithLeft(n3);
    return n3;
}

Node* doubleRotateWithRight(Node *n3){
    n3->right = singleRotateWithLeft(n3->right);
    n3 = singleRotateWithRight(n3);
    return n3;
}

Node* insertNode(Node *node, Node *root){
    if(root==NULL){
        root = node;   // Placing the new node //
    }
    else if(node->data<root->data){
        root->left = insertNode(node, root->left);
        if(getNodeHeight(root->left)-getNodeHeight(root->right)==2){  // If height has increased
            if(root->left->data > node->data){
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
        root->right = insertNode(node, root->right);
        if(getNodeHeight(root->left)-getNodeHeight(root->right)==-2){  // If height has increased
            if(root->right->data < node->data){
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

void preOrder(Node *root){
    if(root==NULL){
        ;
    }
    else{
        printf(" %d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void main(){
    Node *AVL = createNewNode(15);
    AVL = insertNode(createNewNode(20), AVL);
    AVL = insertNode(createNewNode(24), AVL);
    AVL = insertNode(createNewNode(10), AVL);
    AVL = insertNode(createNewNode(13), AVL);
    AVL = insertNode(createNewNode(7), AVL);
    AVL = insertNode(createNewNode(30), AVL);
    AVL = insertNode(createNewNode(36), AVL);
    AVL = insertNode(createNewNode(25), AVL);
    preOrder(AVL);
    printf("\n");
}
