#include <iostream>
using namespace std;

#include "Heap/Heap.h"
#include "Heap/GenericHeap.h"
#include "PriorityQueue/GenericPriorityQueue.h"
#include "Graph/Graph.h"

int main() {
  cout << "Hello world!" << endl;

  Graph<int, int>* graph = new Graph<int, int>;
  graph->addVertex(1);
  graph->addVertex(2);
  graph->addEdge(1, 2, 100);

  return 0;
}
