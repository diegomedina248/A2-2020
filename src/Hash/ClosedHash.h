#ifndef CLOSED_HASH_H
#define CLOSED_HASH_H

#include <iostream>
using namespace std;

class ClosedHash {
  public:
    ClosedHash(unsigned int expectedItems) {
      tableSize = expectedItems;
      items = 0;

      buckets = new Cell[tableSize];
      for (unsigned int i = 0; i < tableSize; i++)
        buckets[i].state = EMPTY;
    }

    // PRE: data not in hash
    void insert(int data) {
      if (shouldExpand()) {
        // expandir tabla
      }

      unsigned int position = hashFunction(data, tableSize);

      // Cambiar esta condicion si se quiere considerar que
      // data exista en el hash
      // data puede estar ACTIVE o DELETED.
      // Hay que recorrer hasta encotrar data o una celda EMPTY
      while (buckets[position].state == ACTIVE) {
        position = (position + 1) % tableSize;
      }

      buckets[position].data = data;
      buckets[position].state = ACTIVE;
    }
  private:
    enum CellType { ACTIVE, EMPTY, DELETED };
    struct Cell {
      int data;
      CellType state;
    };

    unsigned int tableSize;
    unsigned int items;
    Cell* buckets;

    unsigned int hashFunction(int data, unsigned int size) {
      return abs(data) % size;
    }

    // implementar
    bool shouldExpand() {
      return false;
    }
};

#endif
