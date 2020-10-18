#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

#define INITIAL_VERTICES 5

template <class V, class W>
class Graph {
  public:
    Graph() {
      listSize = INITIAL_VERTICES;
      vertices = 0;
      adjacencyList = new Node*[listSize];

      for (unsigned int i = 0; i < listSize; i++)
        adjacencyList[i] = NULL;
    }

    // PRE: vertex does not belong to graph
    void addVertex(V vertex) {
      expandAdjacencyListIfNeeded();

      Node* node = new Node;
      node->vertex = vertex;
      node->list = NULL;

      adjacencyList[vertices] = node;
      vertices++;
    }

    // PRE: edge between from and to does not exist in the graph
    //      from, to vertices belong to the graph
    void addEdge(V from, V to, W weight) {
      Node* node = getVertexNode(from);

      EdgeListNode* edgeNode = new EdgeListNode;
      edgeNode->toVertex = to;
      edgeNode->weight = weight;
      edgeNode->nextEdge = node->list;

      node->list = edgeNode;
    }

    unsigned int getVerticesCount() {
      return vertices;
    }

    V* getVertices() {
      V* verticesVec = new V[vertices];
      for (unsigned int i = 0; i < vertices; i++)
        verticesVec[i] = adjacencyList[i]->vertex;
      
      return verticesVec;
    }

    bool hasEdge(V from, V to) {
      Node* node = getVertexNode(from);
      EdgeListNode *edgeNode = node->list;

      while (edgeNode != NULL) {
        if (edgeNode->toVertex == to)
          return true;
        edgeNode = edgeNode->nextEdge;
      }

      return false;
    }

    // PRE: edge between from and to exists in graph
    W getEdge(V from, V to) {
      Node* node = getVertexNode(from);
      EdgeListNode *edgeNode = node->list;

      while (edgeNode != NULL) {
        if (edgeNode->toVertex == to)
          return edgeNode->weight;
        edgeNode = edgeNode->nextEdge;
      }

      return 0;
    }

    void removeEdge(V from, V to) {
      // TODO: implement
    }
  private:
    struct EdgeListNode {
      V toVertex;
      W weight;
      EdgeListNode* nextEdge;
    };
  
    struct Node {
      V vertex;
      EdgeListNode* list;
    };
  
    Node** adjacencyList;
    unsigned int listSize;
    unsigned int vertices;

    // PRE: vertex belong to the graph
    Node* getVertexNode(V vertex) {
      for (unsigned int i = 0; i < vertices; i++) {
        if (adjacencyList[i]->vertex == vertex)
          return adjacencyList[i];
      }

      return NULL;
    }

    void expandAdjacencyListIfNeeded() {
      if (vertices < listSize) return;

      unsigned int newSize = listSize * 1.5;
      Node** newList = new Node*[newSize];

      for (unsigned int i = 0; i < newSize; i++) {
        newList[i] = i < vertices ? adjacencyList[i] : NULL;
      }

      delete[] adjacencyList;
      adjacencyList = newList;
      listSize = newSize;
    }
};

#endif
