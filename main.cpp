#include <iostream>
#include "Tree.h"
using namespace std;
struct Node {
  Node* next;
  int data;
};

void push(int newdata, Node* &top);
void print(Node* top);
void pop(Node* &top);
void peek(Node* top);
void enqueue(Node* & front, Node* & rear, int newdata);
void dequeue(Node* &tempfront, Node* &rear);
int main() {
  cout << "Welcome to the Shunting Yard. Please enter an equation in infix notation." << endl;
  char input[100];
  cin >> input;
  for(int i = 0; i < strlen(input)/2; i++) {
      
  }
  Node* stack = NULL;
  Node* queuefront = NULL;
  Node* queuerear = NULL;
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
    cout << top->data << endl;
  }
  else {
    cout << "The stack is empty";
  }
}
void enqueue(Node* & front, Node* & rear, int newdata) {
  if(front == NULL && rear == NULL) {
    cout << "test";
    
    Node* temp = new Node();
    temp->next = NULL;
    
    temp->data = newdata;

    front = temp;
    rear = temp;
    temp->next = NULL;
    }
  else {
    Node* temp = new Node();
    temp->data = newdata;
    temp->next = front;
    front = temp;
    cout << "The front is" << front->data << endl;
    cout << "The rear is" << rear->data << endl;
  }
}
void dequeue(Node* &tempfront, Node* & rear) {
  if(rear == NULL) {
    cout << "The queue is empty!";
  }
  else if(tempfront == rear) {
    cout << "One left" <<endl;
     Node* temprear = rear;
    delete temprear;
    tempfront = NULL;
    rear = NULL;
    
  }
  else if(tempfront->next == rear) {
    Node* temprear = rear;
    
    cout << "The rear has been delete" << rear->data << endl;
    rear = tempfront;
    delete temprear;
  }
  else {
    dequeue(tempfront->next, rear);
  }
}

