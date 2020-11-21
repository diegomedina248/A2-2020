#ifndef DYNAMIC_PROGRAMMING_CPP
#define DYNAMIC_PROGRAMMING_CPP

#include <iostream>
using namespace std;

long fibRecursive(long n) {
  if (n <= 1) return 1;
  else return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// Orden tiempo de ejecucion: O(n)
// Orden espacial: O(n)
long fibTable(long n) {
  long* table = new long[n + 1];

  table[0] = 1;
  table[1] = 1;
  for (unsigned int i = 2; i <= n; i++)
    table[i] = table[i - 1] + table[i - 2];

  return table[n];
}

// Orden tiempo de ejecucion: O(n)
// Orden espacial: O(1)
long fibSum(long n) {
  if (n <= 1) return 1;

  long x = 1;
  long y = 1;

  for (unsigned int i = 2; i <= n; i++) {
    long value = x + y;
    x = y;
    y = value;
  }

  return y;
}

// Orden tiempo de ejecucion: O(n*k)
// Orden espacial: O(n*k)
int binomialCoefficient(int n, int k) {
  int** matrix = new int*[n + 1];
  for (unsigned int i = 0; i <= n; i++) {
    matrix[i] = new int[k + 1];
    for (unsigned int j = 0; j <= k; j++)
      matrix[i][j] = 0;
  }

  for (unsigned int i = 0; i <= n; i++)
    matrix[i][0] = 1;

  for (unsigned int i = 0; i <= k; i++)
    matrix[i][i] = 1;

  for (unsigned int i = 2; i<= n; i++) {
    for (unsigned int j = 1; j <= k; j++) {
      matrix[i][j] = matrix[i - 1][j - 1] + matrix[i - 1][j];
    }
  }

  return matrix[n][k];
}

int notesThatAddToAmountDP(
  unsigned int* notes,
  unsigned int notesCount,
  unsigned int amount
) {
  int** matrix = new int*[notesCount];
  for (unsigned int i = 0; i < notesCount; i++) {
    matrix[i] = new int[amount + 1];
    for (unsigned int j = 0; j <= amount; j++)
      matrix[i][j] = INT_MAX;
  }

  for (unsigned int i = 0; i < notesCount; i++)
    matrix[i][0] = 0;

  for (unsigned int i = 0; i < notesCount; i++) {
    for (unsigned int j = 1; j <= amount; j++) {
      if (i == 0) {
        if (j < notes[0]) {
          matrix[i][j] = INT_MAX;
        } else {
          int notesForRemainingAmount = matrix[i][j - notes[0]];
          matrix[i][j] = notesForRemainingAmount == INT_MAX
            ? INT_MAX
            : (1 + notesForRemainingAmount);
        }
      } else {
        if (j < notes[i]) {
          matrix[i][j] = matrix[i - 1][j];
        } else {
          int notesForRemainingAmount = matrix[i][j - notes[i]];
          int minAmountConsideringAllNotes = notesForRemainingAmount == INT_MAX
            ? INT_MAX
            : (notesForRemainingAmount + 1);
          int minAmountIgnoringLastNote = matrix[i - 1][j];

          matrix[i][j] = min(
            minAmountConsideringAllNotes,
            minAmountIgnoringLastNote
          );
        }
      }
    }
  }

  return matrix[notesCount - 1][amount];
}

// Dada una cantidad de items, donde cada uno tiene un valor y un peso determinado,
// se quiere colocar elementos en una mochila de capacidad weight cuyo valor sea el
// maximo posible.
// itemValues e itemWeights son dos vectores que, para la misma posicion, representan el
// valor y peso de un item, respectivamente.
// Los items no se pueden partir, o se colocan o se descartan.
int knapsackDP(
  unsigned int weight,
  int* itemValues,
  int* itemWeight,
  unsigned int items
) {
  int** K = new int*[items + 1];
  for (unsigned int i = 0; i <= items; i++) {
    K[i] = new int[weight + 1];
    for (unsigned int j = 0; j <= weight; j++)
      K[i][j] = -1;
  }

  for (unsigned int i = 0; i <= items; i++) {
    for (unsigned int j = 0; j <= weight; j++) {
      if (i == 0 || j == 0) {
        K[i][j] = 0;
      } else if (itemWeight[i - 1] > j) {
        K[i][j] = K[i - 1][j];
      } else {
        int valueIncludingLastItem = itemValues[i - 1] + K[i - 1][j - itemWeight[i - 1]];
        int valueIgnoringLastItem = K[i - 1][j];

        K[i][j] = max(valueIncludingLastItem, valueIgnoringLastItem);
      }
    }
  }

  return K[items][weight];
}

int knapsackRec(
  unsigned int weight,
  int* itemValues,
  int* itemWeight,
  unsigned int items
) {
  if (weight == 0 || items == 0) return 0;

  if (itemWeight[items - 1] > weight)
    return knapsackRec(weight, itemValues, itemWeight, items - 1);

  return max(
    itemValues[items - 1] + knapsackRec(
      weight - itemWeight[items - 1],
      itemValues,
      itemWeight,
      items - 1
    ),
    knapsackRec(weight, itemValues, itemWeight, items - 1)
  );
}

int knapsackMemRec(
  unsigned int weight,
  int* itemValues,
  int* itemWeight,
  int items,
  int** matrix
) {
  if (items < 0 || weight <= 0) return 0;
  if (matrix[items][weight] != -1) return matrix[items][weight];

  if (itemWeight[items] > weight) {
    matrix[items][weight] = knapsackMemRec(
      weight,
      itemValues,
      itemWeight,
      items - 1,
      matrix
    );
  } else {
    matrix[items][weight] = max(
      knapsackMemRec(weight, itemValues, itemWeight, items - 1, matrix),
      itemValues[items] + knapsackMemRec(
        weight - itemWeight[items],
        itemValues,
        itemWeight,
        items - 1,
        matrix
      )
    );
  }

  return matrix[items][weight];
}

int knapsackMem(
  unsigned int weight,
  int* itemValues,
  int* itemWeight,
  unsigned int items
) {
  int** matrix = new int*[items];
  for (unsigned int i = 0; i < items; i++) {
    matrix[i] = new int[weight + 1];
    for (unsigned int j = 0; j <= weight; j++)
      matrix[i][j] = -1;
  }

  return knapsackMemRec(weight, itemValues, itemWeight, items - 1, matrix);
}

void testDynamicProgramming() {
  cout << "FIBONACCI REC" << endl;
  cout << fibRecursive(10) << endl;
  cout << fibRecursive(20) << endl;
  // cout << fibRecursive(100) << endl;

  cout << endl << "FIBONACCI TABLE" << endl;
  cout << fibTable(10) << endl;
  cout << fibTable(20) << endl;
  cout << fibTable(100) << endl;

  cout << endl << "NOTES EXCHANGE" << endl;
  unsigned int notes[] = {11, 5, 1};
  cout << notesThatAddToAmountDP(notes, 3, 15) << endl; // 3
  unsigned int notes2[] = {5, 4, 1};
  cout << notesThatAddToAmountDP(notes2, 3, 8) << endl; // 2
  unsigned int notes3[] = {2000, 500, 200, 100, 50, 20, 10, 5, 1};
  cout << notesThatAddToAmountDP(notes3, 9, 2456) << endl; // 6

  cout << endl << "KNAPSACK DP" << endl;
  int val[] = { 60, 100, 120 };
  int weights[] = { 10, 20, 30 };
  cout << knapsackDP(50, val, weights, 3) << endl; // 220
  int val2[] = { 20, 5, 10, 40, 15, 25 };
  int weights2[] = { 1, 2, 3, 8, 7, 4 };
  cout << knapsackDP(10, val2, weights2, 6) << endl; // 60

  cout << endl << "KNAPSACK DP MEMOIZATION" << endl;
  cout << knapsackMem(50, val, weights, 3) << endl; // 220
  cout << knapsackMem(10, val2, weights2, 6) << endl; // 60
}

#endif
