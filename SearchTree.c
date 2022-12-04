#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
};
typedef struct node Node;

Node* createNewNode(int value){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->data = value;
    handle->left = NULL;
    handle->right = NULL;
    return handle;
}

Node* insertNode(Node *node, Node* root){
    if(root==NULL){
        root = node;
    }
    else{
        if(node->data < root->data){
            root->left = insertNode(node, root->left);
        }
        else{
            root->right = insertNode(node, root->right);
        }
    }
    return root;
}

Node* findNode(int value, Node *root){
    if(root==NULL){
        return NULL;
    }
    else{
        if(value == root->data){
            return root;
        }
        else if(value < root->data){
            return findNode(value, root->left);
        }
        else{
            return findNode(value, root->right);
        }
    }
}

Node* findMinNode(Node *root){
    if(root==NULL){
        return NULL;
    }
    else{
        if(root->left==NULL){
            return root;
        }
        else{
            return findMinNode(root->left);
        }
    }
}

Node* findMaxNode(Node *root){
    if(root==NULL){
        return NULL;
    }
    else{
        if(root->right==NULL){
            return root;
        }
        else{
            return findMinNode(root->right);
        }
    }
}

Node* deleteNode(int value, Node *root){
    if(root==NULL){
        return NULL;
    }
    else{
        Node *duplicate = NULL;
        if(value < root->data){
            root->left = deleteNode(value, root->left);
        }
        else if(value > root->data){
            root->right = deleteNode(value, root->right);
        }
        else{
            // Node found
            if(root->left!=NULL && root->right!=NULL){
                duplicate = findMinNode(root->right);
                root->data = duplicate->data;    // DON'T REPLACE THE ENTIRE NODE ITSELF, ONLY THE VALUE //
                root->right = deleteNode(duplicate->data, root->right);
            }
            else{
                duplicate = root;
                if(root->left!=NULL){
                    root = root->left;
                }
                else if(root->right!=NULL){
                    root = root->right;
                }
                else{
                    root = NULL;
                }
                free(duplicate);
            }
        }
        return root;
    }
}

Node* findSibling(int value, Node *root){
    if(root==NULL || (root->left==NULL && root->right==NULL)){
        return NULL;
    }
    else if(root->left && root->left->data==value){
        return root->right;
    }
    else if(root->right && root->right->data==value){
        return root->left;
    }
    else{
        if(value < root->data){
            return findSibling(value, root->left);
        }
        else if(value > root->data){
            return findSibling(value, root->right);
        }
    }
}

int findTreeHeight(Node *root){
    if(root==NULL){
        return -1;
    }
    else{
        int left_height = findTreeHeight(root->left);
        int right_height = findTreeHeight(root->right);
        if(left_height>=right_height){
            return left_height+1;
        }
        else{
            return right_height+1;
        }
    }
}

void preOrder(Node *root){
    if(root==NULL){
        return;
    }
    else{
        printf(" %d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void main(){
    Node *BST = NULL;
    BST = insertNode(createNewNode(1), BST);
    BST = insertNode(createNewNode(10), BST);
    BST = insertNode(createNewNode(8), BST);
    BST = insertNode(createNewNode(4), BST);
    BST = insertNode(createNewNode(6), BST);
    BST = insertNode(createNewNode(3), BST);
    BST = insertNode(createNewNode(2), BST);
    BST = insertNode(createNewNode(5), BST);
    //BST = deleteNode(2, BST);
    //BST = deleteNode(8, BST);
    //BST = deleteNode(4, BST);
    preOrder(BST);
    printf("\n");
    printf("\nTREE HEIGHT: %d", findTreeHeight(BST));
    printf("\nSIBLING: %d", findSibling(4, BST)->data);

}
