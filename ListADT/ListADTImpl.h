#include<stdio.h>
#include<stdlib.h>

List* initializeList(){
    List *handle = (List*)malloc(sizeof(List));
    handle->data = (int*)malloc(sizeof(int)*STARTER_SIZE);
    handle->length = 0;
    handle->capacity = STARTER_SIZE;
    handle->isSorted = 1;   // An empty list is considered sorted
    return handle;
}

short isFull(List *list){
    return (list->capacity==list->length);
}

short isEmpty(List *list){
    return(list->length==0);
}

void expandList(List *list){
    list->capacity *= 2;
    list->data = realloc(list->data, sizeof(int)*list->capacity);
}

void append(int value, List *list){
    if(isFull(list)){
        expandList(list);
    }
    *(list->data+list->length) = value;
    // If the new element is smaller than previous, sort order is destroyed
    if(list->length>0 && *(list->data+list->length-1)>value){
        list->isSorted = 0;
    }
    list->length++;
}

int swap(int ind1, int ind2, List *list){
    if(ind1>=list->length){
        return 0;   // Error occurred
    }
    if(ind2>=list->length){
        return 0;   // Error occurred
    }
    int temp = *(list->data+ind1);
    *(list->data+ind1) = *(list->data+ind2);
    *(list->data+ind2) = temp;

    list->isSorted = 0;   // Uncertain if it is sorted
    return 1;   // Successful
}

int get(int index, List *list, int *value){
    if(index>=list->length){
        return 0;   // Error occurred
    }
    else{
        *value = *(list->data+index);
        return 1;   // Successful
    }
}

void display(List *list){
    if(isEmpty(list)){
        printf("\nEmpty List\n");
        return;
    }
    printf("\nLIST CONTENTS\n");
    for(int i=0;i<list->length;i++){
        printf("%d, ", *(list->data+i));
    }
    printf("\n");
}

int linearSearch(int value, List *list){
    int elem;
    int i = 0;
    while(get(i, list, &elem)){
        if(elem == value){
            return i;
        }
        i++;
    }
    return -1;  // Not Found
}

int binarySearchRecurser(int value, List *list, int start, int end){
    if(start>end){
        return -1;  // Not Found
    }

    int mid = (start+end)/2;
    if(*(list->data+mid) == value){
        return mid;
    }
    else if(*(list->data+mid) > value){
        return binarySearchRecurser(value, list, start, mid-1);
    }
    else{
        return binarySearchRecurser(value, list, mid+1, end);
    }
}

int binarySearch(int value, List *list){
    if(!list->isSorted){
        return -2;   // Not Sorted
    }
    return binarySearchRecurser(value, list, 0, list->length);
}

void selectionSort(List *list){
    if(list->isSorted){
        return;
    }

    int min, elem, posn;
    for(int i=0;i<list->length-1;i++){
        get(i, list, &min);
        posn = i;
        for(int j=i+1;j<list->length;j++){
            get(j, list, &elem);
            if(elem<min){
                min = elem;
                posn = j;
            }
        }
        if(posn!=i){
            swap(i, posn, list);
        }
    }
    list->isSorted = 1;
}

/* Uses Bubble Sort //
void shellSort(List *list){
    if(list->isSorted){
        return;
    }
    int settled, elem1, elem2;
    for(int gap=list->length/2;gap>=1;gap/=2){
        for(int i=0;i<(list->length-1)/gap;i++){
            settled = (i+1)*gap;
            for(int j=0;j<list->length-settled;j++){
                get(j, list, &elem1);
                get(j+gap, list, &elem2);
                if(elem1>elem2){
                    swap(j, j+gap, list);
                }
            }
        }
    }
    list->isSorted = 1;
}
*/

void shellSort(List *list){
    if(list->isSorted){
        return;
    }
    int elem1, elem2, j;
    for(int gap=list->length/2;gap>=1;gap/=2){
        for(int i=gap;i<list->length;i++){
            j = i-gap;
            get(j, list, &elem1);
            get(j+gap, list, &elem2);
            while(j>=0 && elem1>elem2){
                swap(j, j+gap, list);
                j -= gap;
                get(j, list, &elem1);
                get(j+gap, list, &elem2);
            }
        }
    }
    list->isSorted = 1;
}
