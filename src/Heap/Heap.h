#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

#define INITIAL_SIZE 10

class Heap {
  public:
    Heap() {
      size = INITIAL_SIZE;
      array = new int[size];
      items = 0;
    }

    void insert(int data) {
      items++;
      unsigned int hole = items;
      array[hole] = data;

      percolateUp(hole);
    }

    // PRE: heap is not empty
    void deleteMin() {
      unsigned int hole = 1;
      array[hole] = array[items];
      items--;

      percolateDown(hole);
    }

    // PRE: heap is not empty
    int min() {
      return array[1];
    }

    void decreasePriority(unsigned int position, unsigned int delta) {
      array[position] -= delta;
      percolateUp(position);
    }

    void increasePriority(unsigned int position, unsigned int delta) {
      array[position] += delta;
      percolateDown(position);
    }
  private:
    int* array;
    unsigned int size;
    unsigned int items;

    // filtrado hacia arriba
    void percolateUp(unsigned int hole) {
      while (hole > 1 && array[hole] < array[hole / 2]) {
        swap(array[hole], array[hole / 2]);
        hole /= 2;
      }
    }

    // filtrado hacia abajo
    void percolateDown(unsigned int hole) {
      while (hole * 2 <= items) {
        unsigned int child = hole * 2;
        if (child + 1 <= items && array[child + 1] < array[child])
          child++;

        if (array[child] < array[hole]) {
          swap(array[child], array[hole]);
          hole = child;
        } else break;
      }
    }
};

#endif
