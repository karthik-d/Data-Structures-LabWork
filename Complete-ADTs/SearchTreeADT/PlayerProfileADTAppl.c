#include "PlayerProfileADT.h"
#include "PlayerProfileADTImpl.h"

void main(){
    Node *players = NULL, *result;
    char ch = 'y';
    int oper, response;
    char name[30];
    do{
        printf("\n1-Add Player\n2-Search Player\n3-Delete player\n4-Display Hierarchically\n5-PreOrder Display\n6-InOrder Display\n7-PostOrder Display\nEnter Choice: ");
        scanf(" %d", &oper);
        if(oper==1){
            players = insert(createNewNode(makePlayer()), players);
        }
        else if(oper==2){
            printf("\nEnter Name: ");
            scanf(" %s", name);
            result = search(name, players);
            if(result==NULL){
                printf("\nPlayer Not Found\n");
            }
            else{
                displayPlayer(result->player);
            }
        }
        else if(oper==3){
            printf("\nEnter Name: ");
            scanf(" %s", name);
            players = delete(name, players);
            if(result==NULL){
                printf("\nPlayer Not Found\n");
            }
            else{
                printf("\nPlayer Deleted\n");
            }
        }
        else if(oper==4){
            printf("\nHIERARCHICAL\n");
            display(players, 0);
        }
        else if(oper==5){
            printf("\nPRE-ORDER\n");
            preOrder(players);
        }
        else if(oper==6){
            printf("\nIN-ORDER\n");
            inOrder(players);
        }
        else if(oper==7){
            printf("\nPOST-ORDER\n");
            postOrder(players);
        }
        else{
            printf("\nInvalid Choice\n");
        }
        printf("\nMore Operations? (y/n): ");
        scanf(" %c", &ch);
    }while(ch!='n');
}
