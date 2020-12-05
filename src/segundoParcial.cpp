#include <iostream>
using namespace std;

/*
Parcial 2, fecha: 5-12-19 matutino
https://drive.google.com/file/d/18asg2iUWkaFzSLW7G8ed_xafAbSz5OK5/view?usp=sharing
*/
struct MazeNode {
  int health;
  int steps;
  char** maze;
  MazeNode* next;
};

int xMazePos2[4] = { -1, 1, 0, 0 };
int yMazePos2[4] = { 0, 0, -1, 1 };

bool isStepValid(
  char** maze,
  int rows,
  int cols,
  int x,
  int y
) {
  return x >= 0 &&
    y >= 0 &&
    x < rows &&
    y < cols &&
    (maze[x][y] == 'S' || maze[x][y] == 'R');
}

bool isMazeToEscapeSolution(
  int x,
  int y,
  int endX,
  int endY
) {
  return x == endX && y == endY;
}

void mazeToEscape(
  char** maze,
  int rows,
  int cols,
  int endX,
  int endY,
  int x,
  int y,
  int health,
  int currentSteps,
  MazeNode* &solution
) {
  if (!isStepValid(maze, rows, cols, x, y)) return;
  int newHealth = maze[x][y] == 'R' ? (health - 5) : health;
  if (newHealth <= 0) return;

  if (maze[x][y] == 'S')
    maze[x][y] = 'M';
  else
    maze[x][y] = 'Q';

  if (isMazeToEscapeSolution(x, y, endX, endY)) {
    MazeNode* node = new MazeNode;
    node->health = newHealth;
    node->steps = currentSteps;

    node->maze = new char*[rows];
    for (unsigned int i = 0; i < rows; i++) {
      node->maze[i] = new char[cols];
      for (unsigned int j = 0; j < cols; j++)
        node->maze[i][j] = maze[i][j];
    }

    if (
      solution != NULL &&
      solution->steps == currentSteps &&
      solution->health == newHealth
    ) {
      node->next = solution;
      solution = node;
    } else if (
      solution == NULL ||
      currentSteps < solution->steps ||
      (currentSteps == solution->steps && newHealth > solution->health)
    ) {
      solution = node;
    }
  } else {
    for (int i = 0; i < 4; i++) {
      mazeToEscape(
        maze,
        rows,
        cols,
        endX,
        endY,
        x + xMazePos2[i],
        y + yMazePos2[i],
        newHealth,
        currentSteps + 1,
        solution
      );
    }
  }

  if (maze[x][y] == 'M')
    maze[x][y] = 'S';
  else
    maze[x][y] = 'R';
}

int f(int n) {
  if (n < 4) {
    return n;
  } else if (n % 2 == 0) {
    return f(n - 1) + f(n - 2) + f(n - 3) - f(n - 4);
  } else {
    return f(n - 2) + f(n - 3) - f(n - 4);
  }
}

int fMemo(int n, int* mem) {
  if (n < 4) {
    return n;
  }

  if (mem[n] != INT_MAX) {
    return mem[n];
  }

  int result = 0;
  if (n % 2 == 0) {
    result = fMemo(n - 1, mem) + fMemo(n - 2, mem) + fMemo(n - 3, mem) - fMemo(n - 4, mem);
  } else {
    result = fMemo(n - 2, mem) + fMemo(n - 3, mem) - fMemo(n - 4, mem);
  }

  mem[n] = result;
  return result;
}

int fDynamic(int n) {
  int* memo = new int[n + 1];

  for (unsigned int i = 0; i < 4; i++)
    memo[i] = i;

  for (unsigned int i = 4; i <= n; i++) {
    if (i % 2 == 0) {
      memo[i] = memo[i - 1] + memo[i - 2] + memo[i - 3] - memo[i - 4];
    } else {
      memo[i] = memo[i - 2] + memo[i - 3] - memo[i - 4];
    }
  }

  return memo[n];
}

/*
Parcial 2, fecha: 5-12-19 nocturno
https://drive.google.com/file/d/1IjyFtsAa5bVBP59CMuqALRh6myX2R8_T/view?usp=sharing

Los ejemplos del ejercicio 2 en el parcial son en su mayoria incorrectos.
Ignorar.
*/
int sumaMultiplos(int* v, int desde, int hasta, int k) {
  if (desde > hasta) return 0;
  if (desde == hasta) {
    if (v[desde] % k == 0)
      return v[desde];
    return 0;
  }

  int medio = (desde + hasta) / 2;
  int left = sumaMultiplos(v, desde, medio, k);
  int right = sumaMultiplos(v, medio + 1, hasta, k);

  return left + right;
}

void testSegundoParcial() {
  int* memo = new int[9];
  for (unsigned int i = 0; i < 9; i++)
    memo[i] = INT_MAX;

  // Con memorizacion, creamos la memoria antes de llamar a la funcion.
  // La funcion es recursiva, la memoria que usa para guardar los calculos
  // ya hechos no la puede crear en cada paso recursivo.
  cout << "F MEMO: " << fMemo(8, memo) << endl;
}
