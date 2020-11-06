#include <iostream>
#include <stack>
using namespace std;

#include "Heap/Heap.h"
#include "Heap/GenericHeap.h"
#include "PriorityQueue/GenericPriorityQueue.h"
#include "Graph/Graph.h"

struct TopologicalSortVertex {
  int value;
  int indegree;

  bool operator==(TopologicalSortVertex v) {
    return value == v.value;
  }
};

void topologicalSort(Graph<TopologicalSortVertex, bool>* graph) {
  unsigned int count = graph->getVerticesCount();
  TopologicalSortVertex* vertices = graph->getVertices();

  for (unsigned int i = 0; i < count; i++) {
    vertices[i].indegree = 0;

    for (unsigned int k = 0; k < count; k++) {
      if (graph->getEdge(vertices[k], vertices[i]))
        vertices[i].indegree++;
    }
  }

  for (unsigned int i = 0; i < count; i++) {
    int position = -1;
    for (unsigned int i = 0; i < count; i++) {
      if (vertices[i].indegree == 0) {
        position = i;
        break;
      }
    }

    // Process the current vertex
    cout << vertices[position].value << endl;
    vertices[position].indegree = -1;

    for (unsigned int i = 0; i < count; i++) {
      if (graph->getEdge(vertices[position], vertices[i])) {
        vertices[i].indegree--;
      }
    }
  }
};

struct Vertex {
  int value;
  int distance;
  bool visited;
  int path;

  Vertex() {}
  Vertex(int v): value(v) {}

  bool operator==(Vertex v) {
    return value == v.value;
  }
};

void dijkstra(Graph<Vertex, int>* graph, Vertex v) {
  unsigned int count = graph->getVerticesCount();
  Vertex* vertices = graph->getVertices();

  for (unsigned int i = 0; i < count; i++) {
    vertices[i].visited = false;
    vertices[i].distance = INT_MAX;

    if (vertices[i] == v) {
      vertices[i].distance = 0;
    }
  }

  for (unsigned int i = 0; i < count; i++) {
    int position = -1;
    for (unsigned int k = 0; k < count; k++) {
      if (!vertices[k].visited && 
        (position == -1 || vertices[k].distance < vertices[position].distance)) {
        position = k;
      }
    }

    vertices[position].visited = true;
    for (unsigned int k = 0; k < count; k++) {
      if (!graph->hasEdge(vertices[position], vertices[k])) continue;
      if (vertices[k].visited) continue;

      int weight = graph->getEdge(vertices[position], vertices[k]);
      int newDistance = vertices[position].distance + weight;
      if (newDistance < vertices[k].distance) {
        vertices[k].distance = newDistance;
        vertices[k].path = vertices[position].value;
      }
    }
  }

  for (unsigned int i = 0; i < count; i++) {
    cout << "v" << vertices[i].value << " " << vertices[i].distance;
    cout << " " << vertices[i].path << endl;
  }
}

#define INF 9999

void floydWarshall(Graph<Vertex, int>* graph) {
  unsigned int count = graph->getVerticesCount();
  Vertex* vertices = graph->getVertices();

  int** dist = new int*[count];
  int** path = new int*[count];

  for (unsigned int i = 0; i < count; i++) {
    dist[i] = new int[count];
    path[i] = new int[count];

    for (unsigned int k = 0; k < count; k++) {
      if (graph->hasEdge(vertices[i], vertices[k])) {
        dist[i][k] = graph->getEdge(vertices[i], vertices[k]);
        path[i][k] = i;
      } else {
        dist[i][k] = INF;
        path[i][k] = -1;
      }
    }
  }

  for (unsigned int k = 0; k < count; k++) {
    for (unsigned int i = 0; i < count; i++) {
      for (unsigned int j = 0; j < count; j++) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          path[i][j] = k;
        }
      }
    }
  }
}

void prim(Graph<Vertex, int>* graph, Vertex v) {
  unsigned int count = graph->getVerticesCount();
  Vertex* vertices = graph->getVertices();

  for (unsigned int i = 0; i < count; i++) {
    vertices[i].visited = false;
    vertices[i].distance = INT_MAX;

    if (vertices[i] == v) {
      vertices[i].distance = 0;
    }
  }

  for (unsigned int i = 0 ; i < count; i++) {
    int position = -1;
    for (unsigned int k = 0; k < count; k++) {
      if (!vertices[k].visited && 
        (position == -1 || vertices[k].distance < vertices[position].distance)) {
        position = k;
      }
    }

    vertices[position].visited = true;
    for (unsigned int k = 0; k < count; k++) {
      if (graph->hasEdge(vertices[position], vertices[k]) && !vertices[k].visited) {
        int weight = graph->getEdge(vertices[position], vertices[k]);
        if (weight < vertices[k].distance) {
          vertices[k].distance = weight;
          vertices[k].path = position;
        }
      }
    }
  }
}

class Edge {
  public:
    int from;
    int to;
    int weight;

    Edge() {}
    Edge(int f, int t, int w): from(f), to(t), weight(w) {}

    bool operator==(Edge &e) {
      return e.weight == weight;
    }

    bool operator<(Edge &e) {
      return weight < e.weight;
    }
};

bool hasCycle(Graph<Vertex, int>* graph) {
  unsigned int count = graph->getVerticesCount();
  Vertex* vertices = graph->getVertices();

  bool* visited = new bool[count];
  int* parent = new int[count];

  for (unsigned int i = 0; i < count; i++) {
    visited[i] = false;
    parent[i] = -1;
  }

  stack<int> s;
  s.push(vertices[0].value);

  while (!s.empty()) {
    int current = s.top();
    s.pop();
    visited[current] = true;

    for (unsigned int i = 0; i < count; i++) {
      if (graph->hasEdge(vertices[current], vertices[i])) {
        if (!visited[i]) {
          parent[i] = current;
          s.push(i);
        } else if (parent[current] != -1 && parent[current] != i) {
          return true;
        }
      }
    }
  }

  return false;
}

void kruskal(Graph<Vertex, int>* graph) {
  unsigned int count = graph->getVerticesCount();
  Vertex* vertices = graph->getVertices();

  GenericHeap<Edge> *heap = new GenericHeap<Edge>();
  Graph<Vertex, int>* result = new Graph<Vertex, int>();

  for (unsigned int i = 0; i < count; i++) {
    result->addVertex(vertices[i]);

    for (unsigned int k = i + 1; k < count; k++) {
      if (graph->hasEdge(vertices[i], vertices[k])) {
        heap->insert(Edge(i, k, graph->getEdge(vertices[i], vertices[k])));
      }
    }
  }

  unsigned int edgesAccepted = 0;
  while (edgesAccepted <= count - 1 && !heap->isEmpty()) {
    Edge e = heap->min();
    heap->deleteMin();

    result->addEdge(vertices[e.from], vertices[e.to], e.weight);
    result->addEdge(vertices[e.to], vertices[e.from], e.weight);
    if (hasCycle(result)) {
      result->removeEdge(vertices[e.from], vertices[e.to]);
      result->removeEdge(vertices[e.to], vertices[e.from]);
    } else {
      edgesAccepted++;
      cout << "E: " << e.from << " -> " << e.to << " (" << e.weight << ")";
      cout << endl;
    }
  }
}

void test() {
  cout << "Hello world!" << endl << endl;

  Graph<Vertex, int>* graph = new Graph<Vertex, int>;

  Vertex v1(1);
  Vertex v2(2);
  Vertex v3(3);
  Vertex v4(4);
  Vertex v5(5);
  Vertex v6(6);
  Vertex v7(7);

  graph->addVertex(v1);
  graph->addVertex(v2);
  graph->addVertex(v3);
  graph->addVertex(v4);
  graph->addVertex(v5);
  graph->addVertex(v6);
  graph->addVertex(v7);

  graph->addEdge(v1, v2, 2);
  graph->addEdge(v1, v4, 1);
  graph->addEdge(v2, v5, 10);
  graph->addEdge(v2, v4, 3);
  graph->addEdge(v3, v1, 4);
  graph->addEdge(v3, v6, 5);
  graph->addEdge(v4, v3, 2);
  graph->addEdge(v4, v6, 8);
  graph->addEdge(v4, v5, 2);
  graph->addEdge(v4, v7, 4);
  graph->addEdge(v5, v7, 6);
  graph->addEdge(v7, v6, 1);

  dijkstra(graph, v1);
}
