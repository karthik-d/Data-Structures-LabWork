#include "DictionaryADT.h"
#include "DictionaryADTImpl.h"

void main(){
    int oper;
    char ch;
    char word[16];
    char meaning[100];
    Dictionary *dictionary = NULL;
    WordMeaning *word_ins = NULL;
    ;

    do{
        printf("\n1-Insert Word\n2-Display Dictionary\n3-Search Word\nEnter Choice: ");
        scanf(" %d", &oper);
        if(oper==1){
            printf("\nEnter Word: ");
            scanf(" %s", word);
            printf("Enter Meaning: ");
            scanf(" %[^\n]s%*c", meaning);
            dictionary = insertWordNode(createWordNode(createWord(word, meaning)), dictionary);
        }
        else if(oper==2){
            dispHierarchical(dictionary);
        }
        else if(oper==3){
            printf("\nEnter Word: ");
            scanf(" %s", word);
            word_ins = search(word, dictionary);
            if(word_ins==NULL){
                printf("Word not found\n");
            }
            else{
                displayWord(word_ins);
            }
        }
        else{
            printf("\nInvalid Choice\n");
        }
        printf("\nMore Operations? (y/n): ");
        scanf(" %c", &ch);
    }while(ch!='n');
}
