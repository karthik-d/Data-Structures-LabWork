struct bucket{
    int data;  // Stores the label for bucket and link to first value
    struct bucket *nextValue;   // For lateral access
};
typedef struct bucket Bucket;

struct hashtable{
    Bucket **buckets;   // Array of bucket pointers
    int (*hashfunction)(int);
    int capacity;       // Number of buckets in the table
};
typedef struct hashtable Hashtable;

// Indexing is used to access a specific bucket (vertcial)
// Linking is used to access values in a bucket (lateral)
