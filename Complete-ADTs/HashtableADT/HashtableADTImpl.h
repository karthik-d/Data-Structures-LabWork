#include<stdio.h>
#include<stdlib.h>

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
    // "capacity" is the number of buckets in the hashtable
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
