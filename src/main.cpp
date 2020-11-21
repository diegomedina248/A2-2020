#include <iostream>
using namespace std;

#include "divideAndConquer.cpp"
#include "greedy.cpp"
#include "dynamicProgramming.cpp"

int main() {
  cout << "========================" << endl << "START D&C" << endl << "========================" << endl << endl;
  testDivideAndConquer();
  cout << endl << "========================" << endl << "END D&C" << endl << "========================" << endl << endl;

  cout << "========================" << endl << "START GREEDY" << endl << "========================" << endl << endl;
  testGreedy();
  cout << endl << "========================" << endl << "END GREEDY" << endl << "========================" << endl << endl;

  cout << "========================" << endl << "START DYNAMIC PROGRAMMING" << endl << "========================" << endl << endl;
  testDynamicProgramming();
  cout << endl << "========================" << endl << "END DYNAMIC PROGRAMMING" << endl << "========================" << endl << endl;

  return 0;
}
