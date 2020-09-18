#include <iostream>
using namespace std;

#include "Heap/Heap.h"
#include "Heap/GenericHeap.h"
#include "PriorityQueue/GenericPriorityQueue.h"

template <class T>
void intercambiar(T &a, T &b) {
  T aux = a;
  a = b;
  b = aux;
};

template <class T>
struct ListNode {
  T data;
  ListNode<T>* next;
};

template <class T>
void addEnd(ListNode<T>* &node, T data) {
  if (!node) {
    node = new ListNode<T>;
    node->data = data;
    node->next = NULL;
  } else addEnd(node->next, data);
}

class Employee {
  public:
    Employee() { }

    Employee(int id, string name, unsigned int salary) {
      this->id = id;
      this->name = name;
      this->salary = salary;
    }

    int getId() {
      return id;
    }

    string getName() {
      return name;
    }

    bool operator<(Employee& employee) {
      return salary < employee.salary;
    }

    bool operator==(Employee& employee) {
      return salary == employee.salary;
    }

    void operator-=(int delta) {
      salary -= delta;
    }
  private:
    int id;
    string name;
    unsigned int salary;
};

class EmployeeById {
  public:
    EmployeeById(Employee& employee) {
      this->employee = employee;
    }

    bool operator<(EmployeeById& employeeById) {
      return employee.getId() < employeeById.employee.getId();
    }
  private:
    Employee employee;
};

int main() {
  cout << "Hello world!" << endl;

  Employee e1 = Employee(4, "Diego", 100);
  Employee e2 = Employee(5, "Pedro", 200);

  GenericPriorityQueue<Employee>* pq = new GenericPriorityQueue<Employee>;
  pq->insert(e2);
  pq->insert(e1);

  cout << pq->min().getName() << endl;

  return 0;
}
