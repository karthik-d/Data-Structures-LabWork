#include<string.h>
#include "StudentADT.h"
#include "StudentADTImpl.h"

void main(){

    char choice_1, choice_2;
    int response, rnum, categ, size, ctr;
    Student stud_inst;
    Node *student_list = createSentinelNode();
    Node *handle;
    Node **names;
    do{
        printf("\nCurrent Student List");
        displayRegNumsOnly(student_list);
        printf("\nMAIN MENU\n1-Insert Student\n2-Delete By Register Number\n3-Search By Register Number\n4-Display All Students\n5-List Student By Category\n6-List Students With Repeated Names\n7-Exit\nEnter Choice: ");
        scanf(" %c", &choice_1);
        switch(choice_1){

            case '1':
                do{
                    printf("\nCurrent Student List");
                    displayRegNumsOnly(student_list);
                    printf("\nINSERTION\n1-At Beginning\n2-After a Register Number End\n3-Go Back\nEnter Choice: ");
                    scanf(" %c", &choice_2);
                    switch(choice_2){
                        case '1':
                            stud_inst = makeStudentByInput(&response);
                            if(response==-1){
                                printf("\nInvalid Input\n");
                                continue;
                            }
                            insertFront(student_list, createNewNode(stud_inst));
                            printf("\nStudent Record inserted at beginning\n");
                            break;
                        case '2':
                            stud_inst = makeStudentByInput(&response);
                            if(response==-1){
                                printf("\nInvalid Input");
                                continue;
                            }
                            printf("\nEnter Preceding Register Number: ");
                            scanf(" %d", &rnum);
                            response = insertAfter(student_list, createNewNode(stud_inst), rnum);
                            if(response==-1){
                                printf("\nPreceding Register No. Not Found...Aborted\n");
                                continue;
                            }
                            printf("\nStudent Record inserted after Register Number %d\n", rnum);
                            break;
                        case '3':
                            break;
                        default:
                            printf("\nInvalid Option\n");
                            break;
                    }
                }while(choice_2!='3');
                break;

            case '2':
                printf("\nEnter Register Number: ");
                scanf(" %d", &rnum);
                stud_inst = deleteByRegNum(student_list, rnum, &response);
                if(response==-1){
                    printf("\nStudent Not Found\n");
                }
                else if(response==1){
                    printf("\nCannot Delete Student. Empty List\n");
                }
                else{
                    printf("\nFollowing Student Record was Deleted\n");
                    displayStudent(stud_inst);
                }
                printf("\n");
                break;

            case '3':
                printf("\nEnter Register Number: ");
                scanf(" %d", &rnum);
                handle = searchByRegNum(student_list, rnum, &response);
                if(response==-1){
                    printf("\nStudent Not Found\n");
                }
                else{
                    displayStudent(handle->data);
                }
                printf("\n");
                break;

            case '4':
                printf("\nCURRENT STUDENT LIST\n");
                display(student_list);
                break;

            case '5':
                printf("Choose Category");
                for(int i=0;i<5;i++){
                    printf("\n%d - %s", (i+1), CATEGORIES[i]);
                }
                printf("\nEnter Choice: ");
                scanf(" %d", &categ);
                if(categ<1||categ>5){
                    printf("\nInvalid Category Selected\n");
                    break;
                }
                printf("\nStudents in %s Category\n", CATEGORIES[categ-1]);
                display(listByCategory(student_list, categ-1));
                break;

            case '6':
                names = groupByNames(student_list, &size);
                for(int i=0;i<size;i++){
                    handle = names[i];
                    if(handle->next->next==NULL){
                        continue;   // Name is not repeated
                    }
                    printf("\nSTUDENTS WITH NAME '%s'\n", handle->next->data.name);
                    ctr = 0;
                    while(handle->next!=NULL){
                        handle = handle->next;
                        ctr++;
                        printf("\nSTUDENT %d", ctr);
                        printf("\n--------------------");
                        displayStudent(handle->data);
                        printf("\n--------------------\n");
                    }
                    printf("\n");
                }
                printf("\n");
                break;
            case '7':
                break;
            default:
                printf("\nInvalid Option\n");
                break;
        }
    }while(choice_1!='7');

}
