#ifndef GREEDY_CPP
#define GREEDY_CPP

#include <iostream>
#include <algorithm>
using namespace std;

int travelingSalesmanNaive(
  int** graph,
  unsigned int vertexCount,
  unsigned int source
) {
  int* vertices = new int[vertexCount];

  for(unsigned int i = 0; i < vertexCount; i++)
    vertices[i] = i;

  swap(vertices[0], vertices[source]);

  int minCount = INT_MAX;
  int currentCount = 0;

  do {
    currentCount = 0;

    for (unsigned int i = 0; i < vertexCount; i++) {
      // cout << vertices[i] << " ";
      
      if (i == vertexCount - 1)
        currentCount += graph[vertices[i]][vertices[0]];
      else
        currentCount += graph[vertices[i]][vertices[i+1]];
    }

    minCount = min(minCount, currentCount);
    // cout << endl;
  } while (next_permutation(vertices+1, vertices+vertexCount));

  return minCount;
}

unsigned int nextMinVertex(
  int** graph,
  unsigned int vertexCount,
  bool* visited,
  unsigned int actualVertex,
  unsigned int source
) {
  unsigned int vertex = source;
  int min = INT_MAX;

  for (unsigned int i = 0; i < vertexCount; i++) {
    if (visited[i]) continue;
    if (graph[actualVertex][i] < min) {
      min = graph[actualVertex][i];
      vertex = i;
    }
  }

  return vertex;
}

int travelingSalesmanGreedy(
  int** graph,
  unsigned int vertexCount,
  unsigned int source
) {
  bool* visited = new bool[vertexCount];
  for (unsigned int i = 0; i < vertexCount; i++)
    visited[i] = false;

  unsigned int actualVertex = source;
  unsigned int prevVertex = 0;

  int sum = 0;
  for (unsigned int i = 0; i < vertexCount; i++) {
    prevVertex = actualVertex;
    visited[prevVertex] = true;
    
    actualVertex = nextMinVertex(
      graph,
      vertexCount,
      visited,
      actualVertex,
      source
    );

    sum += graph[prevVertex][actualVertex];
  }

  return sum;
}

void notesThatAddToAmount(
  unsigned int* notes,
  unsigned int notesCount,
  unsigned int amount
) {
  unsigned int currentNote = 0;
  unsigned int currentNoteCount = 0;

  while (currentNote < notesCount) {
    if (amount >= notes[currentNote]) {
      currentNoteCount++;
      amount -= notes[currentNote];
    } else {
      if (currentNoteCount > 0)
        cout << notes[currentNote] << ": " << currentNoteCount << endl;

      currentNote++;
      currentNoteCount = 0;
    }
  }
}

void selectSort(int* vec, unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    unsigned int minPos = i;
    for (unsigned int j = i + 1; j < size; j++) {
      if (vec[j] < vec[minPos])
        minPos = j;
    }

    swap(vec[i], vec[minPos]);
  }
}

int assignMiceToHoles(int* mices, int* holes, unsigned int count) {
  selectSort(mices, count);
  selectSort(holes, count);

  int maxTime = INT_MIN;
  for (unsigned int i = 0; i < count; i++) {
    int diff = abs(mices[i] - holes[i]);
    maxTime = max(maxTime, diff);
  }

  return maxTime;
}

bool isBefore(string a, string b) {
  string aCopy = a;
  string bCopy = b;

  aCopy.replace(aCopy.find(":"), 1, "");
  bCopy.replace(bCopy.find(":"), 1, "");

  return atoi(aCopy.c_str()) <= atoi(bCopy.c_str());
}

unsigned int platformsNeeded(
  string* arrival,
  string* departures,
  unsigned int trains
) {
  unsigned int platforms = 0;
  unsigned int currentPlatforms = 0;

  unsigned int arrivalIndex = 0;
  unsigned int departureIndex = 0;

  while (arrivalIndex < trains && departureIndex < trains) {
    if (isBefore(departures[departureIndex], arrival[arrivalIndex])) {
      currentPlatforms--;
      departureIndex++;
    } else {
      currentPlatforms++;
      arrivalIndex++;
    }

    platforms = max(platforms, currentPlatforms);
  }

  return platforms;
}

void testGreedy() {  
  int g1[][4] = {{0, 1, 5, 2},
                 {1, 0, 4, 6},
                 {5, 4, 0, 3},
                 {2, 6, 3, 0}};

  int** graph1 = new int*[4];
  for (unsigned int i = 0; i < 4; i++) {
    graph1[i] = new int[4];
    for (unsigned int j = 0; j < 4; j++)
      graph1[i][j] = g1[i][j];
  }

  int result = travelingSalesmanNaive(graph1, 4, 0);
  cout << "RESULT: " << result << endl;
  int resultGreedy = travelingSalesmanGreedy(graph1, 4, 0);
  cout << "RESULT GREEDY: " << resultGreedy << endl;

  int g2[][6] = {{0, 3, 10, 11, 7, 25},
                 {3, 0, 6, 12, 8, 20},
                 {10, 6, 0, 9, 4, 20},
                 {11, 12, 9, 0, 5, 15},
                 {7, 8, 4, 5, 0, 18},
                 {25, 20, 20, 15, 18, 0}};

  int** graph2 = new int*[6];
  for (unsigned int i = 0; i < 6; i++) {
    graph2[i] = new int[6];
    for (unsigned int j = 0; j < 6; j++)
      graph2[i][j] = g2[i][j];
  }

  int result2 = travelingSalesmanNaive(graph2, 6, 0);
  cout << "RESULT: " << result2 << endl;
  int resultGreedy2 = travelingSalesmanGreedy(graph2, 6, 0);
  cout << "RESULT GREEDY: " << resultGreedy2 << endl;

  cout << endl;
  cout << "NOTE EXCHANGE" << endl;
  unsigned int notes1[] = {2000, 500, 200, 100, 50, 20, 10, 5, 1};
  notesThatAddToAmount(notes1, 9, 800);
  cout << endl;
  notesThatAddToAmount(notes1, 9, 2456);
  cout << endl;

  unsigned int notes2[] = {11, 5, 1};
  notesThatAddToAmount(notes2, 3, 15);
  
  cout << endl;
  cout << "MICES" << endl;
  
  int mices1[] = {4, -4, 2}; // -4, 2, 4
  int holes1[] = {4, 0, 5}; // 0, 4, 5

  cout << assignMiceToHoles(mices1, holes1, 3) << endl;

  cout << endl;
  cout << "PLATFORMS NEEDED" << endl;

  string arr[] = {"9:00", "9:40"};
  string dep[] = {"9:10", "12:00"};

  cout << platformsNeeded(arr, dep, 2) << endl; // 1

  string arr2[] = {"9:00", "9:40", "9:50", "11:00", "15:00", "18:00"};
  string dep2[] = {"9:10", "11:20", "11:30", "12:00", "19:00", "20:00"};

  cout << platformsNeeded(arr2, dep2, 6) << endl; // 3
}

#endif
