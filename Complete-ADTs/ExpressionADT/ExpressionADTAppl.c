#include "ExpressionADT.h"
#include "ExpressionADTImpl.h"

void main(){
    int response, choice;
    char *postfix;
    char ch1='y', ch2;
    Tree *expression = NULL;
    while(ch1!='n'){
        printf("\nEnter Postfix Expression: ");
        scanf(" %s", postfix);
        expression = makeExpressionTree(postfix, &response);
        if(response==-4){
            printf("\nInsufficient Operators\n");
            continue;
        }
        else if(response==-3){
            printf("\nInvalid Postfix Form\n");
            continue;
        }
        ch2 = 'y';
        while(ch2!='n'){
            printf("\n1-Display Infix Form\n2-Display Prefix Form\n3-Display Postfix Form\nEnter Choice: ");
            scanf("%d", &choice);
            if(choice==1){
                printf("\nINFIX FORM\n");
                displayTreeInOrder(expression);
            }
            else if(choice==2){
                printf("\nPREFIX FORM\n");
                displayTreePreOrder(expression);
            }
            else if(choice==3){
                printf("\nPOSTFIX FORM\n");
                displayTreePostOrder(expression);
            }
            else{
                printf("\nInvalid Choice\n");
                continue;
            }
            printf("\n\nMore Operations? (y/n): ");
            scanf(" %c", &ch2);
        }
        printf("\nMore Expressions? (y/n): ");
        scanf(" %c", &ch1);
    }
}
