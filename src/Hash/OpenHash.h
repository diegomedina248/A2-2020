#ifndef OPEN_HASH_H
#define OPEN_HASH_H

#include <iostream>
using namespace std;

class OpenHash {
  public:
    OpenHash(unsigned int expectedItems) {
      tableSize = expectedItems;
      table = new Node*[tableSize];
      for (unsigned int i = 0; i < tableSize; i++)
        table[i] = NULL;
    }

    void insert(int data) {
      unsigned int key = hashFunction(data, tableSize);
      insert(table[key], data);
    }

  private:
    struct Node {
      int data;
      Node* next;
    };

    Node** table;
    unsigned int tableSize;

    unsigned int hashFunction(int data, unsigned int size) {
      return abs(data) % size;
    }

    void insert(Node* &node, int data) {
      if (!node) {
        node = new Node;
        node->data = data;
        node->next = NULL;
      } else if (node->data == data) {
        node->data = data;
      } else {
        insert(node->next, data);
      }
    }
};

#endif
