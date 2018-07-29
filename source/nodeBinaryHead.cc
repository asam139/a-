//
// Created by Saul Moreno Abril on 29/07/2018.
//

#include "nodeBinaryHead.h"


// A utility function to swap two elements
void swap(Node *x, Node *y)
{
    Node temp = *x;
    *x = *y;
    *y = temp;
}

// Constructor: Builds a heap from a given array a[] of given size
NodeBinaryHead::NodeBinaryHead(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new Node[cap];
}

// Inserts a new key 'k'
void NodeBinaryHead::insertKey(Node k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)].F > harr[i].F)
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void NodeBinaryHead::decreaseKey(int i, int new_val)
{
    harr[i].F = new_val;
    while (i != 0 && harr[parent(i)].F > harr[i].F)
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Method to remove minimum element (or root) from min heap
Node* NodeBinaryHead::extractMin()
{
    if (heap_size <= 0)
        return nullptr;
    if (heap_size == 1)
    {
        heap_size--;
        return &harr[0];
    }

    // Store the minimum value, and remove it from heap
    Node* root = &harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
}


// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void NodeBinaryHead::deleteKey(int i)
{
    decreaseKey(i, UINT_MAX);
    extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void NodeBinaryHead::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l].F < harr[i].F)
        smallest = l;
    if (r < heap_size && harr[r].F < harr[smallest].F)
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

void NodeBinaryHead::clear() {
    heap_size = 0;
}