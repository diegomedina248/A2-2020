#ifndef BACKTRACKING_CPP
#define BACKTRACKING_CPP

#include <iostream>
using namespace std;

void printMatrix(int** matrix, unsigned int rows, unsigned int cols) {
  for (unsigned int i = 0; i < rows; i++) {
    for (unsigned int j = 0; j < cols; j++)
      cout << matrix[i][j] << " ";
    cout << endl;
  }
}

bool isNQueensSolution(unsigned int n, int col) {
  return col >= n;
}

bool isQueenSafe(
  int** board,
  unsigned int n,
  int row,
  int col
) {
  // misma fila
  for (unsigned int i = 0; i < col; i++) {
    if (board[row][i] == 1)
      return false;
  }

  // diagonal superior
  for (unsigned int d = 1; d < n; d++) {
    int newRow = row - d;
    int newCol = col - d;
    if (newRow >= 0 && newCol >= 0 && board[newRow][newCol] == 1)
      return false;
  }

  // diagonal inferior
  for (unsigned int d = 1; d < n; d++) {
    int newRow = row + d;
    int newCol = col - d;
    if (newRow < n && newCol >= 0 && board[newRow][newCol] == 1)
      return false;
  }

  return true;
}

bool nQueens(
  int** board,
  unsigned int n,
  int row,
  int col
) {
  if (isNQueensSolution(n, col))
    return true;

  board[row][col] = 1;
  if (isQueenSafe(board, n, row, col)) {
    if (nQueens(board, n, 0, col + 1))
      return true;
  }

  board[row][col] = 0; // back
  if (row < n - 1)
    return nQueens(board, n, row + 1, col);
  return false;
}

int** buildMatrix(unsigned int rows, unsigned int cols) {
  int** matrix = new int*[rows];

  for (unsigned int i = 0; i < rows; i++) {
    matrix[i] = new int[cols];
    for (unsigned int j = 0; j < cols; j++)
      matrix[i][j] = 0;
  }

  return matrix;
}

#define boardSize 8
int xKnightPos[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int yKnightPos[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

bool isKnightSolution(int step) {
  return step == boardSize * boardSize;
}

bool isKnightPosValid(int** board, int x, int y) {
  return x >= 0 
    && y >= 0
    && x < boardSize
    && y < boardSize
    && board[x][y] == 0;
}

bool knight(
  int** board,
  int x,
  int y,
  int step
) {
  board[x][y] = step;
  if (isKnightSolution(step))
    return true;

  for (unsigned int i = 0; i < 8; i++) {
    int nextX = x + xKnightPos[i];
    int nextY = y + yKnightPos[i];

    if (isKnightPosValid(board, nextX, nextY)) {
      if (knight(board, nextX, nextY, step + 1))
        return true;
    }
  }

  board[x][y] = 0; // back
  return false;
}

int xMazePos[4] = { -1, 1, 0, 0 };
int yMazePos[4] = { 0, 0, -1, 1 };

bool isMazeSolution(int x, int y, int endX, int endY) {
  return x == endX && y == endY;
}

bool isMazeStepValid(int** maze, int rows, int cols, int x, int y) {
  return x >= 0 && y >= 0 && x < rows && y < cols && maze[x][y] == 0;
}

void minStepsToEscape(
  int** maze,
  int rows,
  int cols,
  int endX,
  int endY,
  int x,
  int y,
  int currentSteps,
  int &bestSteps,
  int** &bestPath
) {
  if (
    !isMazeStepValid(maze, rows, cols, x, y)
    || (bestSteps > 0 && currentSteps >= bestSteps)
  ) return;

  maze[x][y] = 2;
  if (isMazeSolution(x, y, endX, endY)) {
    if (bestSteps == 0 || currentSteps < bestSteps) {
      bestSteps = currentSteps;

      for (unsigned int i = 0; i < rows; i++)
        for (unsigned int j = 0; j < cols; j++)
          bestPath[i][j] = maze[i][j];
    }

    maze[x][y] = 0;
    return;
  }

  for (unsigned int i = 0; i < 4; i++) {
    minStepsToEscape(
      maze,
      rows,
      cols,
      endX,
      endY,
      x + xMazePos[i],
      y + yMazePos[i],
      currentSteps + 1,
      bestSteps,
      bestPath
    );
  }

  maze[x][y] = 0;
}

struct MinStepsBestValue {
  int bestSteps;
  int** bestPath;
};

void minStepsToEscape2(
  int** maze,
  int rows,
  int cols,
  int endX,
  int endY,
  int x,
  int y,
  int currentSteps,
  MinStepsBestValue* solution
) {
  if (
    !isMazeStepValid(maze, rows, cols, x, y)
    || (solution->bestSteps > 0 && currentSteps >= solution->bestSteps)
  ) return;

  maze[x][y] = 2;
  if (isMazeSolution(x, y, endX, endY)) {
    if (solution->bestSteps == 0 || currentSteps < solution->bestSteps) {
      solution->bestSteps = currentSteps;

      for (unsigned int i = 0; i < rows; i++)
        for (unsigned int j = 0; j < cols; j++)
          solution->bestPath[i][j] = maze[i][j];
    }

    maze[x][y] = 0;
    return;
  }

  for (unsigned int i = 0; i < 4; i++) {
    minStepsToEscape2(
      maze,
      rows,
      cols,
      endX,
      endY,
      x + xMazePos[i],
      y + yMazePos[i],
      currentSteps + 1,
      solution
    );
  }

  maze[x][y] = 0;
}

struct ListNode {
  int* array;
  unsigned int size;
  ListNode* next;
};

void allPermutations(
  int* array,
  unsigned int size,
  unsigned int currentPermutationSize,
  ListNode* &permutations
) {
  if (size == currentPermutationSize) {
    ListNode* node = new ListNode();
    node->array = new int[size];
    node->size = size;

    for (unsigned int i = 0; i < size; i++)
      node->array[i] = array[i];

    node->next = permutations;
    permutations = node;
  } else {
    for (unsigned int i = currentPermutationSize; i < size; i++) {
      swap(array[currentPermutationSize], array[i]);
      allPermutations(array, size, currentPermutationSize + 1, permutations);
      swap(array[currentPermutationSize], array[i]);
    }
  }
}

void testBacktracking() {
  cout << "N QUEENS" << endl;
  int** queens4 = buildMatrix(4, 4);
  printMatrix(queens4, 4, 4);
  cout << endl;
  nQueens(queens4, 4, 0, 0);
  printMatrix(queens4, 4, 4);

  cout << endl << "KNIGHTS" << endl;
  int** knightBoard = buildMatrix(boardSize, boardSize);
  knight(knightBoard, 0, 0, 1);
  printMatrix(knightBoard, boardSize, boardSize);

  cout << endl;
  knightBoard = buildMatrix(boardSize, boardSize);
  knight(knightBoard, 4, 5, 1);
  printMatrix(knightBoard, boardSize, boardSize);

  cout << endl << "MAZE" << endl;

  int** maze = buildMatrix(6, 6);
  for (int i = 0; i < 6; i++) {
    if (i != 1 && i != 4) {
      maze[i][1] = 1;
      maze[i][4] = 1;
    }
  }

  cout << "PATH: " << endl;
  printMatrix(maze, 6, 6);
  cout << endl;

  int solution = 0;
  int** bestPath = buildMatrix(6, 6);
  minStepsToEscape(maze, 6, 6, 5, 5, 5, 0, 0, solution, bestPath);
  printMatrix(bestPath, 6, 6);
  cout << "SOLUTION: " << solution << endl << endl;

  MinStepsBestValue* solution2 = new MinStepsBestValue();
  solution2->bestSteps = 0;
  solution2->bestPath = buildMatrix(6, 6);
  minStepsToEscape2(maze, 6, 6, 5, 5, 5, 0, 0, solution2);
  printMatrix(solution2->bestPath, 6, 6);
  cout << "SOLUTION: " << solution2->bestSteps << endl << endl;

  cout << "PERMUTATIONS" << endl;
  int perm1[] = {2, 1, 3};
  ListNode* permutations = NULL;
  allPermutations(perm1, 3, 0, permutations);
  while (permutations) {
    for (unsigned int i = 0; i < permutations->size; i++)
      cout << permutations->array[i] << " ";
    cout << endl;
    permutations = permutations->next;
  }

  int perm2[] = {2, 1, 3, 6, 8};
  permutations = NULL;
  allPermutations(perm2, 5, 0, permutations);
  while (permutations) {
    for (unsigned int i = 0; i < permutations->size; i++)
      cout << permutations->array[i] << " ";
    cout << endl;
    permutations = permutations->next;
  }
}

#endif
