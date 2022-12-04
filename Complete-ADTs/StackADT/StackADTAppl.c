#include "StackADT.h"
#include "StackADTImpl.h"

void main(){
    int choice, response, result;
    char ch='y';
    char *infix, *postfix;

    while(ch!='n'){
        printf("\nNOTE: Enter either\n      SINGLE DIGIT INTEGERS (OR) SINGLE LETTER VARIABLES\n      which can be substitued for any integer values\n");
        printf("\n1-Convert Infix to Postfix Expression\n2-Evaluate Postfix Expression\n3-Evaluate Infix Expression\nEnter Choice: ");
        scanf(" %d", &choice);

        switch(choice){

            case 1:
                printf("\nEnter Infix Expression: ");
                scanf(" %s", infix);
                postfix = convertToPostfix(infix, &response);
                if(response==-1){
                    printf("\nExcess Closing Parentheses\n");
                    continue;
                }
                else if(response==-2){
                    printf("\nExcess Opening Parentheses\n");
                    continue;
                }
                printf("\nEquivalent Postfix Form: ");
                displayExpression(postfix);
                if(response==1){
                    printf("\n(Some unidentified characters were encountered and ignored)");
                }
                break;

            case 2:
                printf("\nEnter Postfix Expression: ");
                scanf(" %s", postfix);
                result = evaluatePostfix(postfix, getUnknownValues(postfix), &response);
                if(response==-3){
                    printf("\nInvalid Expression\n");
                    continue;
                }
                else if(response==-4){
                    printf("\nInsufficient Operators in Expression\n");
                    continue;
                }
                printf("\nResult: %d", result);
                if(response==1){
                    printf("\n(Some unidentified characters were encountered and ignored)");
                }
                break;

            case 3:
                printf("\nEnter Infix Expression: ");
                scanf(" %s", infix);
                postfix = convertToPostfix(infix, &response);
                if(response==-1){
                    printf("\nExcess Closing Parentheses\n");
                    continue;
                }
                else if(response==-2){
                    printf("\nExcess Opening Parentheses\n");
                    continue;
                }
                printf("\nEquivalent Postfix Form: ");
                displayExpression(postfix);
                result = evaluatePostfix(postfix, getUnknownValues(postfix), &response);
                if(response==-3){
                    printf("\nInvalid Expression\n");
                    continue;
                }
                else if(response==-4){
                    printf("\nInsufficient Operators in Expression\n");
                    continue;
                }
                printf("\nResult: %d", result);
                if(response==1){
                    printf("\n(Some unidentified characters were encountered and ignored)");
                }
                break;

            default:
                printf("\nInvalid Choice!\n");
                break;
        }
        printf("\n\nMore Operations? (y/n): ");
        scanf(" %c", &ch);
    }
}
