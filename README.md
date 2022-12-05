# UCS1312-Data-Structures-LabWork
Programs and complete ADTs for common data structures implemented in C for the coursework on UCS1312: Data Structures course 

## [Complete Abstract Data Types](./Complete-ADTs)

A structured ADT implementations for the following data structures are included.
An ADT implementation involves three components:
1. The data structure (defined in `.h` files)
2. An interfacing implementation with functions to store & retreive data (defined as `..Impl.c` files)
3. The abstract application level, that use the interfacing implementation (defined as `..Appl.c` files)

- **Array-based List**
  - *Application*: [Numeric list with search and sort techniques applied: Linear & Binary Search, Shell & Selection Sort](./Complete-ADTs/ListADT)
- **Singly Linked List**
  - *Application*: [Simple student database without sorting](./Complete-ADTs/StudentData-ADT)
- **Linked List -based Stacks**
  - *Application*: [Interconversion between Infix and Postfix Expressions](./Complete-ADTs/StackADT) 
- **Doubly Linked List -based Circular Queue**
  - *Application*: [CPU Scheduling Queue](./Complete-ADTs/CircularQueueADT)
- **Binary Trees**
  - *Application*: [Interconversion between Infix and Postfix Expressions](./Complete-ADTs/DictionaryADT) 
  - *Application*: [Players database with in-order, post-order and pre-order traversal](./Complete-ADTs/SearchTreeADT)
- **AVL Trees**
  - *Application*: [Dictionary of words with sorted insertion and search](./Complete-ADTs/DictionaryADT)
- **Graph using Adjacency Lists**
  - *Algorithm Application*: [Dijkstra's Shortest Path](./Complete-ADTs/GraphADT)
  - *Algorithm Application*: [Depth-first Search](./Complete-ADTs/GraphADT) 
- **Hash Table binned with Linked Lists**
  - *Application*: [Simple integer search](./Complete-ADTs/HashtableADT)
- **Priority Queue**
  - *Application*: [Employee database index by employee ID](./Complete-ADTs/PriorityQueueADT)
