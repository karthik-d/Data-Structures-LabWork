#include<stdio.h>

void display(int arr[], int N){
    printf("\n");
    for(int i=0;i<N;i++){
        printf("%d, ", arr[i]);
    }
}

void shellSort(int arr[], int N){
    int temp, j;
    for(int gap=N/2;gap>=1;gap/=2){
        printf("\n\nGAP: %d", gap);
        for(int i=gap;i<N;i++){
            j = i-gap;
            while(j>=0 && arr[j]>arr[j+gap]){
                temp = arr[j];
                arr[j] = arr[j+gap];
                arr[j+gap] = temp;
                j -= gap;
                display(arr, N);
                printf(" SWAPPED %d - %d ", j+gap, j+gap+gap);
            }
            display(arr, N);
            printf(" BROKE %d - %d", j, j+gap);
        }
    }
}

void selectionSort(int arr[], int N){
    int min, posn;
    for(int i=0;i<N-1;i++){
        min = arr[i];
        posn = i;
        for(int j=i+1;j<N;j++){
            if(arr[j]<min){
                min = arr[j];
                posn = j;
            }
        }
        display(arr, N);
        printf(" FOUND MIN %d - %d", i, posn);
        if(posn!=i){
            arr[posn] = arr[i];
            arr[i] = min;
        }
    }
}

int binarySearch(int value, int arr[], int start, int end){
    if(start>end){
        return -1;  // Not Found
    }

    int mid = (start+end)/2;
    if(arr[mid] == value){
        return mid;
    }
    else if(arr[mid] > value){
        return binarySearch(value, arr, start, mid-1);
    }
    else{
        return binarySearch(value, arr, mid+1, end);
    }
}

void main(){
    int size = 9;
    int arr[] = {17, 26, 20, 44, 55, 31, 54, 77, 93};
    int arr2[] = {18, 32, 12, 5, 38, 33, 16, 2};
    shellSort(arr, size);
    printf("\n\n\n");
    selectionSort(arr2, size-1);
    display(arr, size);
    printf("\n%d\n", binarySearch(77, arr, 0, size));
    //selectionSort(arr, size);
}
