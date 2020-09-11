#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
using namespace std;

#include "../Heap/Heap.h"

class PriorityQueue {
  public:
    PriorityQueue() {
      heap = new Heap;
    }
  
    void insert(int data) {
      heap->insert(data);
    }

    // PRE: priority queue is not empty
    int min() {
      return heap->min();
    }

    // PRE: priority queue is not empty
    void deleteMin() {
      heap->deleteMin();
    }
  private:
    Heap* heap;
};

#endif
