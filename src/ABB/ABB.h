#ifndef ABB_H
#define ABB_H

#include <iostream>
using namespace std;

class ABB {
  public:
    ABB() {
      root = NULL;
    }

    void insert(int data) {
      insert(root, data);
    }

    void remove(int data) {
      remove(root, data);
    }
  
  private:
    struct Node {
      int data;
      Node* left;
      Node* right;
    };
    Node* root;

    void insert(Node* &node, int data) {
      if (!node) {
        node = new Node;
        node->data = data;
        node->left = NULL;
        node->right = NULL;
      } else if (data < node->data) {
        insert(node->left, data);
      } else if (data > node->data) {
        insert(node->right, data);
      }
    }

    void remove(Node* &node, int data) {
      if (!node) return;

      if (data < node->data) {
        remove(node->left, data);
      } else if (data > node->data) {
        remove(node->right, data);
      } else if (node->left && node->right) {
        node->data = findMin(node->right)->data;
        remove(node->right, node->data);
      } else {
        Node* toRemove = node;
        node = node->left ? node->left : node->right;
        delete toRemove;
      }
    };

    Node* findMin(Node* &node) {
      if (!node) return NULL;
      return node->left ? findMin(node->left) : node;
    }
};

#endif
