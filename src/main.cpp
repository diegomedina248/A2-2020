#include <iostream>
using namespace std;

#include "ABB/ABB.h"

int main() {
  cout << "Hello world!" << endl;

  ABB* obj = new ABB;
  obj->insert(5);
  obj->insert(4);
  obj->insert(6);
  obj->remove(5);

  return 0;
}
