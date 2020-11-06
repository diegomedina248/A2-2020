#include <iostream>
using namespace std;

int binarySearch(int* arr, unsigned int low, unsigned int high, int element) {
  if (high < low) return -1;

  unsigned int middle = (low + high) / 2;

  if (arr[middle] == element) return middle;
  else if (arr[middle] > element)
    return binarySearch(arr, low, middle - 1, element);
  else
    return binarySearch(arr, middle + 1, high, element);
}

int power(int x, unsigned int pow) {
  if (pow == 0) return 1;
  if (pow % 2 == 0)
    return power(x, pow / 2) * power(x, pow / 2);
  else
    return x * power(x, pow / 2) * power(x, pow / 2);
}

void merge(int* arr, unsigned int low, unsigned int middle, unsigned int high) {
  unsigned int lowCount = middle - low + 1;
  unsigned int highCount = high - middle;

  int* lowVec = new int[lowCount];
  int* highVec = new int[highCount];

  for (unsigned int i = 0; i < lowCount; i++)
    lowVec[i] = arr[low + i];
  for (unsigned int i = 0; i < highCount; i++)
    highVec[i] = arr[middle + 1 + i];

  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int k = low;

  while (i < lowCount && j < highCount) {
    if (lowVec[i] <= highVec[j]) {
      arr[k] = lowVec[i];
      i++;
    } else {
      arr[k] = highVec[j];
      j++;
    }

    k++;
  }

  while (i < lowCount) {
    arr[k] = lowVec[i];
    i++;
    k++;
  }

  while (j < highCount) {
    arr[k] = highVec[j];
    j++;
    k++;
  }
}

void mergeSort(int* arr, unsigned int low, unsigned int high) {
  if (low >= high) return;

  unsigned int middle = (low + high) / 2;
  mergeSort(arr, low, middle);
  mergeSort(arr, middle + 1, high);

  merge(arr, low, middle, high);
}

unsigned int partition(int* arr, unsigned int low, unsigned int high) {
  int pivot = arr[high];
  unsigned int pivotFinalPosition = low;

  for (unsigned int i = low; i < high; i++) {
    if (arr[i] < pivot) {
      swap(arr[i], arr[pivotFinalPosition]);
      pivotFinalPosition++;
    }
  }

  swap(arr[pivotFinalPosition], arr[high]);
  return pivotFinalPosition;
}

void quickSort(int* arr, unsigned int low, unsigned int high) {
  if (low < high) {
    unsigned int pivot = partition(arr, low, high);

    quickSort(arr, low, pivot - 1);
    quickSort(arr, pivot + 1, high);
  }
}

unsigned int smallestMissingAux(
  unsigned int* arr,
  unsigned int low,
  unsigned int high
) {
  if (low > high) return low;

  unsigned int middle = (low + high) / 2;
  if (arr[middle] == middle)
    return smallestMissingAux(arr, middle + 1, high);
  else
    return smallestMissingAux(arr, low, middle - 1);
}

// vector que contiene solo naturales (no negativos)
// vector ordenado
// vector sin elementos repetidos
// Devolver el numero mas chico que no este presente en el vector
unsigned int smallestMissing(unsigned int* arr, unsigned int size) {
  return smallestMissingAux(arr, 0, size - 1);
}

string matchPrefix(string first, string second) {
  string result = "";

  unsigned int minLegth = min(first.length(), second.length());
  for (unsigned int i = 0; i < minLegth; i++) {
    if (first[i] == second[i])
      result += first[i];
    else break;
  }

  return result;
}

string commonPrefix(string* arr, unsigned int low, unsigned int high) {
  if (high > low) {
    unsigned int middle = (low + high) / 2;
    string left = commonPrefix(arr, low, middle);
    string right = commonPrefix(arr, middle + 1, high);

    return matchPrefix(left, right);
  }

  return arr[low];
}

int maxCrossingIncludingMid(
  int* arr,
  unsigned int low,
  unsigned int middle,
  unsigned int high
) {
  int sum = 0;
  int rightSum = INT_MIN;
  for (unsigned int i = middle + 1; i <= high; i++) {
    sum += arr[i];
    if (sum > rightSum)
      rightSum = sum;
  }

  sum = 0;
  int leftSum = INT_MIN;
  for (int i = middle; i >= (int)low; i--) {
    sum += arr[i];
    if (sum > leftSum)
      leftSum = sum;
  }

  return max(leftSum, max(rightSum, rightSum + leftSum));
}

int maxSumInSubArray(int* arr, unsigned int low, unsigned int high) {
  if (high > low) {
    unsigned int middle = (low + high) / 2;

    int maxLeft = maxSumInSubArray(arr, low, middle);
    int maxRight = maxSumInSubArray(arr, middle + 1, high);
    int maxCrossing = maxCrossingIncludingMid(arr, low, middle, high);

    return max(maxLeft, max(maxRight, maxCrossing));
  }

  return arr[low];
}

int main() {
  cout << "Hello world!" << endl << endl;
  
  cout << "SMALLEST MISSING" << endl;
  unsigned int vec[] = { 0, 1, 2, 3, 4, 5, 6 };
  cout << smallestMissing(vec, 7) << endl; // Resultado: 7

  unsigned int vec2[] = {0, 1, 2, 4, 5, 6, 7};
  cout << smallestMissing(vec2, 7) << endl; // Resultado: 3

  unsigned int vec3[] = {0, 2, 3, 4, 6, 7};
  cout << smallestMissing(vec3, 6) << endl; // Resultado: 1

  cout << endl << "COMMON PREFIX" << endl;
  string strVec[] = { "aaba", "aabfew", "aabfe", "aabfqe" };
  cout << commonPrefix(strVec, 0, 3) << endl; // Resultado: aab

  string strVec2[] = { "Qaaba", "aabfew", "aabfe", "aabfqe" };
  cout << commonPrefix(strVec2, 0, 3) << endl; // Resultado: (string vacio)

  string strVec3[] = { "mqqrt", "mqqrt", "mqqrsdq", "mqqrsdq", "mqqrs" };
  cout << commonPrefix(strVec3, 0, 4) << endl; // Resultado: mqqr

  cout << endl << "MAX SUM IN SUB ARRAY" << endl;
  int sumVec[] = { 1, 2, 3, 4 };
  cout << maxSumInSubArray(sumVec, 0, 3) << endl; // Resultado: 10

  int sumVec2[] = { -2, -5, 6, -2, -3, 1, 5, -6 };
  cout << maxSumInSubArray(sumVec2, 0, 7) << endl; // Resultado: 7

  return 0;
}
