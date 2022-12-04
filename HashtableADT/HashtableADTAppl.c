#include "HashtableADT.h"
#include "HashtableADTImpl.h"

void main(){
    Hashtable *table = createHashtable(10, mod_10_hash);
    int nums[] = {35, 26, 12, 24, 43, 38, 37, 41, 22, 11, 15};
    int response, value, b_num;
    for(int i=0;i<11;i++){
        response = addElement(table, nums[i]);
        printf("%d added to Bucket %d\n", nums[i], response);
    }
    display(table);

    printf("\nEnter Element to Search: ");
    scanf(" %d", &value);
    response = searchElement(table, value, &b_num);
    if(response==-1){
        printf("\nElement not found\n");
    }
    else{
        printf("\nElement found in Bucket %d at index %d\n", b_num, response);
    }
    display(table);

    response = deleteElement(table, 35);
    if(response==-1){
        printf("\n35 not found in table\n");
    }
    else{
        printf("\n35 deleted from Bucket %d\n", response);
    }
    display(table);
}
