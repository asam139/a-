//
// Created by Saul Moreno Abril on 29/07/2018.
//

#ifndef A_NODEBINARYHEAD_H
#define A_NODEBINARYHEAD_H

// A C++ program to demonstrate common Binary Heap Operation
#include<iostream>
#include<climits>
#include <defines.h>
using namespace std;

// Prototype of a utility function to swap two integers
void swap(Node *x, Node *y);

// A class for Min Heap
class NodeBinaryHead
{
    Node **harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    // Constructor
    NodeBinaryHead(int capacity);
    ~NodeBinaryHead();

    // to heapify a subtree with the root at given index
    void MinHeapify(int );

    int parent(int i) { return (i-1)/2; }

    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // to extract the root which is the minimum element
    Node* extractMin();

    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val);

    // Returns the minimum key (key at root) from min heap
    Node* getMin() { return harr[0]; }

    // Deletes a key stored at index i
    void deleteKey(int i);

    // Inserts a new key 'k'
    void insertKey(Node* k);

    // clear
    void clear();
};



#endif //A_NODEBINARYHEAD_H
