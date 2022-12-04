#include<string.h>
#include<stdio.h>
#include<stdlib.h>

// UTILITY FUNCTIONS //

Player makePlayer(){
    Player player;
    int choice=0;
    printf("\nEnter Name: ");
    scanf(" %s", player.name);
    printf("Choose Role: ");
    for(int i=0;i<2;i++){
        printf("\n%d - %s", (i+1), ROLES[i]);
    }
    printf("\nChoose Role: ");
    scanf(" %d", &player.role);
    player.role--;  // Storing Index in ROLES
    printf("Enter Run Rate: ");
    scanf(" %f", &player.run_rate);
    return player;
}

void displayPlayer(Player player){
    printf("\nNAME: %s", player.name);
    printf("\nROLE: %s", ROLES[player.role]);
    printf("\nRUN RATE: %f", player.run_rate);
}

// SEARCH TREE FUNCTIONS //

Node* createNewNode(Player value){
    Node *handle = (Node*)malloc(sizeof(Node));
    handle->player = value;
    handle->left = NULL;
    handle->right = NULL;
    return handle;
}

Node* insert(Node *node, Node *root){
    if(root==NULL){
        root = node;
    }
    else{
        if(strcmp(node->player.name, root->player.name)==-1){
            root->left = insert(node, root->left);
        }
        else{
            root->right = insert(node, root->right);
        }
    }
    return root;
}

Node* search(char *name, Node *root){
    if(root==NULL){
        return NULL;
    }
    else{
        if(strcmp(name, root->player.name)==0){
            return root;
        }
        else if(strcmp(name, root->player.name)==-1){
            return search(name, root->left);
        }
        else{
            return search(name, root->right);
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

Node* delete(char *name, Node *root){
    if(root==NULL){
        return NULL;
    }
    else{
        Node *duplicate = NULL;
        int compare = strcmp(name, root->player.name);
        if(compare==-1){
            root->left = delete(name, root->left);
        }
        else if(compare==1){
            root->right = delete(name, root->right);
        }
        else{
            // Node found
            if(root->left!=NULL && root->right!=NULL){
                duplicate = findMinNode(root->right);
                root->player = duplicate->player;    // DON'T REPLACE THE ENTIRE NODE ITSELF, ONLY THE VALUE //
                root->right = delete(duplicate->player.name, root->right);
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

void display(Node *root, int level){ // Initially, level is 0
    if(root==NULL){
        return;
    }
    printf("\n\nLEVEL %d", level);
    displayPlayer(root->player);
    display(root->left, level+1);
    display(root->right, level+1);
}

void preOrder(Node *root){
    if(root==NULL){
        return;
    }
    else{
        printf(", %s ", root->player.name);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root){
    if(root==NULL){
        return;
    }
    else{
        inOrder(root->left);
        printf(", %s ", root->player.name);
        inOrder(root->right);
    }
}

void postOrder(Node *root){
    if(root==NULL){
        return;
    }
    else{
        postOrder(root->left);
        postOrder(root->right);
        printf(", %s ", root->player.name);
    }
}
