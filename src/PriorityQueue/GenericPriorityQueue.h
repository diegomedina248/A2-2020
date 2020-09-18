#ifndef GENERIC_PRIORITY_QUEUE_H
#define GENERIC_PRIORITY_QUEUE_H

#include <iostream>
using namespace std;

#include "../Heap/GenericHeap.h"

template <class U>
class GenericPriorityQueue {
  public:
    GenericPriorityQueue() {
      heap = new GenericHeap<Item>;
      count = 0;
    }
  
    void insert(U data) {
      count++;
      
      Item item = Item();
      item.data = data;
      item.insertedAt = count;

      heap->insert(item);
    }

    // PRE: priority queue is not empty
    U min() {
      return heap->min().data;
    }

    // PRE: priority queue is not empty
    void deleteMin() {
      heap->deleteMin();
    }
  private:
    struct Item {
      U data;
      long insertedAt;

      bool operator<(Item& item) {
        return data < item.data
          || (data == item.data && insertedAt < item.insertedAt);
      }
    };

    GenericHeap<Item>* heap;
    long count;
};

#endif
