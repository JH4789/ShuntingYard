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
void popto(Node* & top, Node* & front, Node* &rear);
void pop(Node* & top);
char peek(Node* top);
int priority(char prio);
void treepush(Tree* & newtree, Tree* &top);
void treepop(Tree* &newtree, Tree* &top);
Tree* treepeek(Tree* top);
void postfixprint(Tree* current);
void prefixprint(Tree* current);
void infixprint(Tree* current);
void enqueue(Node* & front, Node* & rear, char newdata);
char dequeue(Node* &tempfront, Node* &rear);
void dequeuedel(Node* &tempfront, Node* &rear);
int main() {
  Node* stack = NULL;
  Node* queuefront = NULL;
  Node* queuerear = NULL;
  Tree* treestack = NULL;
  cout << "Welcome to the Shunting Yard. Please enter an equation in infix notation. Do not use spaces to separate tokens." << endl;
  char input[100];
  
  cin >> input;
  
  postfix(input, stack, queuefront, queuerear);
  
  while(queuerear != NULL && queuefront != NULL) {
    
    if(isdigit(dequeue(queuefront, queuerear))) {
       Tree* newbranch = new Tree();
       newbranch->token = dequeue(queuefront, queuerear);
       treepush(treestack, newbranch);
    }
    else {
      Tree* newbranch = new Tree();
      newbranch->token = dequeue(queuefront, queuerear);
      Tree* temp = NULL;
      treepop(treestack, temp);
      newbranch->setRight(temp);
      treepop(treestack, temp);
      newbranch->setLeft(temp);
      treepush(treestack, newbranch);
    }
    dequeuedel(queuefront, queuerear);
    
    
  }
  postfixprint(treestack);
  cout << endl;
  prefixprint(treestack);
  return 0;
}

void push(char newdata, Node* &top) {
  Node* tempnext = new Node();
  tempnext->data = newdata;
  tempnext->next = top;
  top = tempnext;
}
void postfixprint(Tree* current) {
  if(current == NULL) {
    return;
  }
  
    postfixprint(current->left);
  
  
    postfixprint(current->right);
  
    cout << current->token;
}
void prefixprint(Tree* current) {
  if(current == NULL) {
    return;
  }
    cout << current->token;
    prefixprint(current->left);
    prefixprint(current->right);
}
void infixprint(Tree* current) {

}
void treepush(Tree* & newtree, Tree* &top) {
  Tree* temp = top;
  temp->next = newtree;
  newtree= temp;
}
void treepop(Tree* & newtree, Tree* &top) {
  top = newtree;
  newtree = newtree->next;
}
Tree* treepeek(Tree* top) {
  if(top != NULL) {
    return top;
  }
  else {
    return NULL;
  }
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
void popto(Node* &top, Node* & front, Node* & rear) {
  if(top == NULL) {
    cout << "The stack is empty" << endl;
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
      while(peek(stack) != 'N' && priority(peek(stack)) != 5 && priority(peek(stack)) >= priority(input[i]) && priority(input[i]) != 3) {
        popto(stack, queuefront, queuerear);
      }
      push(input[i], stack);
      /*
      if(priority(peek(stack)) > priority(input[i]) && priority(peek(stack)) != 5) {
         
	popto(stack, queuefront, queuerear);
	push(input[i], stack);
      }
      else if(priority(peek(stack)) == priority(input[i]) && priority(peek(stack)) != 5 && priority(peek(stack)) != 3) {
        popto(stack, queuefront, queuerear);
	push(input[i] , stack);
      }
      else {
         push(input[i] , stack);
       }
      */
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
























































































































































































































































































































































































































































































































































































































































