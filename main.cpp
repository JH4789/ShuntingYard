#include <iostream>
#include <cstring>
#include "Tree.h"
using namespace std;
struct Node {
  Node* next;
  char data;
};
void postfix(char input[], Node* & stack, Node* & queuefront, Node* & queuerear);
void push(char newdata, Node* &top);
void print(Node* top);
void popto(Node* & top, Node* & front, Node* &rear);
void pop(Node* & top);
char peek(Node* top);
int priority(char prio);
void enqueue(Node* & front, Node* & rear, char newdata);
char dequeue(Node* &tempfront, Node* &rear);
void dequeuedel(Node* &tempfront, Node* &rear);
int main() {
  Node* stack = NULL;
  Node* queuefront = NULL;
  Node* queuerear = NULL;
  
  cout << "Welcome to the Shunting Yard. Please enter an equation in infix notation. Do not use spaces to separate tokens." << endl;
  char input[100];
  cin >> input;
  postfix(input, stack, queuefront, queuerear);
  Tree* last;
  Tree* secondlast;
  while(queuerear != NULL && queuefront != NULL) {
    Tree* newbranch = new Tree(dequeue(queuefront, queuerear));
    dequeuedel(queuefront, queuerear);
    cout << newbranch->returnToken();
    
  }
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
  else if (prio == '(') {
    return 5;
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
void popto(Node* &top, Node* & front, Node* & rear) {
  if(top == NULL) {
    cout << "The stack is empty" << endl;
  }
  else if(top->data == '(') {
     Node* temp = top;
     cout << "PopTheTop" << endl;
     top = top->next;
     delete temp;
     cout << "This is top data";
     cout << top->data << endl;
  }
  else {
     Node* temp = top;
     enqueue(front, rear, top->data);
     top = top->next;
     
     delete temp;
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
char dequeue(Node* & tempfront, Node* & rear) {
  if(rear == NULL) {
    cout << "The queue is empty!";
    return 'N';
  }
  else if(tempfront == rear) {
     Node* temprear = rear;
     return temprear->data;
     delete temprear;
    tempfront = NULL;
    rear = NULL; 
  }
  else if(tempfront->next == rear) {
    Node* temprear = rear;
    return temprear->data;
    rear = tempfront;
    delete temprear;
    
  }
  else {
    return dequeue(tempfront->next, rear);
  }
}
void dequeuedel(Node* & tempfront, Node* & rear) {
  if(rear == NULL) {
    cout << "The queue is empty!";
  }
  else if(tempfront == rear) {
     Node* temprear = rear;
     delete temprear;
    tempfront = NULL;
    rear = NULL; 
  }
  else if(tempfront->next == rear) {
    Node* temprear = rear;
    rear = tempfront;
    delete temprear;
    
  }
  else {
     dequeuedel(tempfront->next, rear);
  }
}

void postfix(char input[], Node* & stack, Node* & queuefront, Node* & queuerear) {
  int i = 0;
  while(i <= strlen(input)) {
    if(isdigit(input[i])) {
      enqueue(queuefront, queuerear, input[i]);
    }
    else if(input[i] == '^' || input[i] == '*' || input[i] == '+' || input[i] == '-' || input[i] == '/') {
      if(priority(peek(stack)) > priority(input[i]) && priority(peek(stack)) != 5) {
	popto(stack, queuefront, queuerear);
	push(input[i], stack);
      }
      else {
         push(input[i] , stack);
       }
    }
    else if (input[i] == '(') {
      
      push(input[i], stack);
    }
    else if(input[i] == ')') {
      bool running = true;
      while(running == true) {
	if(peek(stack) == '(') {
	  pop(stack);
	  running = false;
	}
	else {
	popto(stack, queuefront, queuerear);
       	}
      }
    }
    else {
      while(stack != NULL) {
	popto(stack, queuefront, queuerear);	
      }
      
    }
    i++;
  }
}
