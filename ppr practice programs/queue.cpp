#include <iostream>
using namespace std;

struct Queue
{
  int data;
  struct Queue* nextnode;
};
struct Queue* topofqueue = nullptr;

void push(int num1) {
  struct Queue* temp = new Queue();
  temp->data = num1;
  temp->nextnode = nullptr;

  if (topofqueue == nullptr) {
    topofqueue = temp;
  } else {
    struct Queue* current = topofqueue;
    while (current->nextnode != nullptr) {
      current = current->nextnode;
    }
    current->nextnode = temp;
  }
}

void pop() {
  if (topofqueue != nullptr) {
    cout << topofqueue->data << endl;
    struct Queue* next = topofqueue->nextnode;
    delete topofqueue;
    topofqueue = next;
  } else {
    cout << "Queue is empty." << endl;
  }
}

int main() {
  int choice;

  while (true) {
    cout << "Press 1 to push 2 to pop ";
    cin >> choice;

    switch (choice) {
      case 1:
        int num;
        cout << "Enter the number to insert: ";
        cin >> num;
        push(num);
        break;
      case 2:
        pop();
        break;
    }
  }

  return 0;
}