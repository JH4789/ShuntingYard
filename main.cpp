#include <iostream>

using namespace std;
struct Node {
  Node* next;
  int data;
};

void push(int newdata, Node* &top);
void print(Node* top);
void pop(Node* &top);
void peek(Node* top);
int main() {
  Node* top = NULL;
  pop(top);
  push(20, top);
  push(11, top);
  peek(top);
  print(top);
  pop(top);
  print(top);
  return 0;
}

void push(int newdata, Node* &top) {
  Node* tempnext = new Node();
  tempnext->data = newdata;
  tempnext->next = top;
  top = tempnext;
}
void print(Node* top) {
  Node* current = top;
  while(current != NULL) {
    cout << current->data << endl;
    current = current->next;
  }
}
void pop(Node* &top) {
  if(top == NULL) {
    cout << "The stack is empty" << endl;
  }
  else {
     Node* temp = top;
     top = top->next;
     delete temp;
  }
}
void peek(Node* top) {
  if(top != NULL) {
    cout << top->data;
  }
  else {
    cout << "The stack is empty";
  }
}

