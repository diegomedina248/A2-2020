#ifndef AVL_H
#define AVL_H

#include <iostream>
using namespace std;

class AVL {
  public:
    AVL() {
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
      int height;
      Node* left;
      Node* right;
    };
    Node* root;

    void insert(Node* &node, int data) {
      if (!node) {
        node = new Node;
        node->data = data;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
      } else if (data < node->data) {
        insert(node->left, data);
      } else if (data > node->data) {
        insert(node->right, data);
      }

      balance(node);
    }

    void balance(Node* &node) {
      if (!node) return;

      if (height(node->left) - height(node->right) > 1) {
        // rotar derecha
        rightRotation(node);
      } else if (height(node->right) - height(node->left) > 1) {
        // rotar izq
      }

      updateHeight(node);
    }

    void rightRotation(Node* &node) {
      Node* aux = node->left;
      node->left = aux->right;
      aux->right = node;

      updateHeight(node);
      updateHeight(aux);

      node = aux;
    }

    void updateHeight(Node* &node) {
      if (!node) return;
      node->height = max(height(node->left), height(node->right)) + 1;
    }

    int height(Node* node) {
      return node ? node->height : 0;
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
