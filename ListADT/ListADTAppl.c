#include "ListADT.h"
#include "ListADTImpl.h"

void main(){
    List *list = initializeList();

    char ch = 'y';
    int value, oper, index;
    do{
        printf("Enter Element %d: ", list->length+1);
        scanf(" %d", &value);
        append(value, list);
        printf("More Elements? (y/n): ");
        scanf(" %c", &ch);
    }while(ch!='n');

    do{
        printf("\nOPERATIONS\n1-Linear Search\n2-Binary Search\n3-Selection Sort\n4-Shell Sort\n5-Exit\nEnter Choice: ");
        scanf(" %d", &oper);

        if(oper==1){
            printf("\nEnter Value to Search: ");
            scanf(" %d", &value);
            index = linearSearch(value, list);
            if(index==-1){
                printf("Element not found\n");
            }
            else{
                printf("%d found at index %d\n", value, index);
            }
        }

        else if(oper==2){
            printf("\nEnter Value to Search: ");
            scanf(" %d", &value);
            index = binarySearch(value, list);
            if(index==-1){
                printf("Element not found\n");
            }
            else if(index==-2){
                printf("List not sorted\n");
            }
            else{
                printf("%d found at index %d\n", value, index);
            }
        }

        else if(oper==3){
            selectionSort(list);
            display(list);
        }

        else if(oper==4){
            shellSort(list);
            display(list);
        }

        else if(oper!=5){
            printf("\nInvalid Choice\n");
            continue;
        }

    }while(oper!=5);
}
