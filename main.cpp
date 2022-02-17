#include <iostream>
#include <cstring>
#include "Tree.h"
using namespace std;
struct Node {
  Node* next;
  char data;
};
void postfix(char input[], Node* stack, Node* queuefront, Node* queuerear);
void push(char newdata, Node* &top);
void print(Node* top);
void pop(Node* &top);
char peek(Node* top);
int priority(char prio);
void enqueue(Node* & front, Node* & rear, char newdata);
void dequeue(Node* &tempfront, Node* &rear);
int main() {
  Node* stack = NULL;
  Node* queuefront = NULL;
  Node* queuerear = NULL;
  
  cout << "Welcome to the Shunting Yard. Please enter an equation in infix notation. Do not use spaces to separate tokens." << endl;
  char input[100];
  cin >> input;
  postfix(input, stack, queuefront, queuerear);  
  return 0;
}

void push(char newdata, Node* &top) {
  Node* tempnext = new Node();
  tempnext->data = newdata;
  tempnext->next = top;
  top = tempnext;
}
int priority(char prio) {
  if(prio == '+') {
    return 1;
  }
  else if (prio == '-') {
    return 1;
  }
  else if (prio == '*') {
    return 2;
  }
  else if (prio == '/') {
    return 2;
  }
  else if (prio == '^') {
    return 3;
  }
  else {
    return 0;
  }
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
     cout << top->data << ' ';
     top = top->next;
     delete temp;
  }
}
char peek(Node* top) {
  if(top != NULL) {
    return top->data;
  }
  else {
    return 'N';
  }
}
void enqueue(Node* & front, Node* & rear, char newdata) {
  if(front == NULL && rear == NULL) {
    
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
    }
}
void dequeue(Node* &tempfront, Node* & rear) {
  if(rear == NULL) {
    cout << "The queue is empty!";
  }
  else if(tempfront == rear) {
     Node* temprear = rear;
     cout << temprear->data << ' ';
     delete temprear;
    tempfront = NULL;
    rear = NULL;
    
  }
  else if(tempfront->next == rear) {
    Node* temprear = rear;
    
    cout << rear->data << ' ';
    rear = tempfront;
    delete temprear;
    
  }
  else {
    dequeue(tempfront->next, rear);
   }
}

void postfix(char input[], Node* stack, Node* queuefront, Node* queuerear) {
  int i = 0;
  while(i <= strlen(input)) {
    if(isdigit(input[i])) {
      enqueue(queuefront, queuerear, input[i]);
    }
    else if(input[i] == '^' || input[i] == '*' || input[i] == '+' || input[i] == '-' || input[i] == '/') {
      if(priority(peek(stack)) > priority(input[i])) {
        while(queuerear != NULL) {
	  dequeue(queuefront, queuerear);
	}
	pop(stack);
	push(input[i], stack);
      }
      else {
         push(input[i] , stack);
      }
      
    }
    else {
      while(queuerear != NULL) {
	  dequeue(queuefront, queuerear);
      }
      while(stack != NULL) {
	pop(stack);
      }
    }
    i++;
  }
}
