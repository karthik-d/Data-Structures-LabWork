#include<stdio.h>
#include<stdlib.h>

struct bucket{
    int data;  // Stores the label for bucket and link to first value
    struct bucket *nextValue;   // For lateral access
};
typedef struct bucket Bucket;

struct hashtable{
    Bucket **buckets;   // Array of buckets
    int (*hashfunction)(int);
    int capacity;
};
typedef struct hashtable Hashtable;

// Indexing is used to access a specific bucket (vertcial)
// Linking is used to access values in a bucket (lateral)

int mod_10_hash(int value){
    return value%10;
}

Bucket* createElement(int data){
    // data can be label or value
    Bucket *handle = (Bucket*)malloc(sizeof(Bucket));
    handle->data = data;
    handle->nextValue = NULL;
    return handle;
}

Hashtable* createHashtable(int capacity, int (*hashfunction)(int)){
    Hashtable *handle = (Hashtable*)malloc(sizeof(Hashtable));
    handle->buckets = (Bucket**)malloc(sizeof(Bucket*)*capacity);
    for(int i=0;i<capacity;i++){
        *((handle->buckets)+i) = createElement(i);
    }
    handle->hashfunction = hashfunction;
    handle->capacity = capacity;
    return handle;
}

short isBucketEmpty(Bucket *bucket){
    return (bucket->nextValue==NULL);
}

Bucket* findBucket(Hashtable *table, int value){
    return *(table->buckets+(*table->hashfunction)(value));
}

int addElement(Hashtable *table, int value){
    Bucket *bucket = findBucket(table, value);
    Bucket *element = createElement(value);
    element->nextValue = bucket->nextValue;
    bucket->nextValue = element;
    return bucket->data;
}

int searchElement(Hashtable *table, int value, int *bucket_num){
    Bucket *bucket = findBucket(table, value);
    Bucket *handle = bucket;
    int ctr = -1;
    while(handle->nextValue!=NULL){
        handle = handle->nextValue;
        ctr++;
        if(handle->data==value){
            *bucket_num = bucket->data;   // Bucket Label
            return ctr;
        }
    }
    return ctr;
}

int deleteElement(Hashtable *table, int value){
    Bucket *bucket = findBucket(table, value);
    if(isBucketEmpty(bucket)){
        return -1;
    }
    Bucket *handle = bucket;
    while(handle->nextValue!=NULL){
        if(handle->nextValue->data==value){
            break;
        }
        handle = handle->nextValue;
    }
    if(handle->nextValue!=NULL){
        handle->nextValue = handle->nextValue->nextValue;
        return bucket->data;   // Label of bucket
    }
    else{
        return -1; // Not Found
    }
}

void display(Hashtable *table){
    Bucket *handle;
    printf("\nHASH TABLE STATUS\n");
    for(int i=0;i<table->capacity;i++){
        handle = *((table->buckets)+i);
        printf("BUCKET %d: ", handle->data);
        while(handle->nextValue!=NULL){
            handle = handle->nextValue;
            printf("%d -> ", handle->data);
        }
        printf("\n");
    }
}

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
