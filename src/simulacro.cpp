#include <iostream>
using namespace std;

// Ejercicio 2
struct User {
  string username;
  string password;
};

struct AVLNode {
  int height;
  User* user;
  AVLNode* left;
  AVLNode* right;
};

struct HashNode {
  User* user;
  HashNode* next;
};

struct TeCocinORT {
  AVLNode* users;
  unsigned int priorityUserCount;
  unsigned int hashTableSize;
  HashNode** hashTable;

  unsigned int hashFunction(string username) {
    unsigned int charCount = 0;
    for (unsigned int i = 0; i < username.length(); i++)
      charCount += username[i];

    return charCount % hashTableSize;
  }

  HashNode* getNode(HashNode* node, string username) {
    if (node == NULL) return NULL;
    else if (node->user->username == username) return node;
    else return getNode(node->next, username);
  }

  bool soyRePro(string username, string password) {
    unsigned int position = hashFunction(username);
    HashNode* node = getNode(hashTable[position], username);
    return node != NULL && node->user->password == password;
  }
};

struct QueueNode {
  int value;
  QueueNode* next;
};

struct Queue {
  QueueNode* first;
  QueueNode* last;

  bool isEmpty() {
    return first == NULL;
  }

  void enqueue(int value) {
    QueueNode* node = new QueueNode;
    node->value = value;
    node->next = NULL;
  
    if (first == NULL) {
      first = node;
    } else {
      last->next = node;
    }

    last = node;
  }

  int front() {
    return first->value;
  }

  void dequeue() {
    QueueNode* node = first;
    first = first->next;
    delete node;
  }
};

struct Graph {
  bool** mat;
  unsigned int vertices;

  void dondeEstasMoquita(int origen) {
    bool* visited = new bool[vertices + 1];

    for (unsigned int i = 1; i <= vertices; i++)
      visited[i] = false;

    Queue* queue = new Queue;
    queue->enqueue(origen);

    while (!queue->isEmpty()) {
      int current = queue->front();
      queue->dequeue();

      if (visited[current]) continue;
      visited[current] = true;

      for (unsigned int i = 1; i <= vertices; i++) {
        if (mat[current][i] && !visited[i]) {
          cout << current << " - " << i << endl;
          queue->enqueue(i);
        }
      }
    }
  }
};
