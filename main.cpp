/*
Name: Jayden Huang
Date: 3/2/2022
Description: Shunting Yard and Binary Tree Implementation
 */
//Includes
#include <iostream>
#include <cstring>
#include "Tree.h"
using namespace std;
struct Node {
  Node* next;
  char data;
};
//Prototyping
void enqueue(Node* & front, Node* & rear, char newdata);
char dequeue(Node* &tempfront, Node* &rear);
void dequeuedel(Node* &tempfront, Node* &rear);
void postfix(char input[], Node* & stack, Node* & queuefront, Node* & queuerear);
void push(char newdata, Node* &top);
//Popto and pop kept separate because one adds it to a queue and the other only deletes it
void popto(Node* & top, Node* & front, Node* &rear);
void pop(Node* & top);
char peek(Node* top);
int priority(char prio);
//Binary Tree Functions
void treepush(Tree* & newtree, Tree* &top);
void treepop(Tree* &newtree, Tree* &top);
Tree* treepeek(Tree* top);
void postfixprint(Tree* current);
void prefixprint(Tree* current);
void infixprint(Tree* current);
int main() {
  //Two stacks and a queue
  Node* stack = NULL;
  Node* queuefront = NULL;
  Node* queuerear = NULL;
  Tree* treestack = NULL;
  cout << "Welcome to the Shunting Yard. Please enter an equation in infix notation. Do not use spaces to separate tokens." << endl;
  char input[100];
  cin >> input;
  //Initial conversion
  postfix(input, stack, queuefront, queuerear);
  //Tree construction
  while(queuerear != NULL && queuefront != NULL) {  
    //Inputs get added to the stack immediately if they are a number, otherwise the top two values on the stack become the left and right of the new input.
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
  //Outputs
  cout << "Postfix output: ";
  postfixprint(treestack);
  cout << endl;
  cout << "Prefix output: ";
  prefixprint(treestack);
  cout << endl;
  cout << "Infix output: ";
  infixprint(treestack);
  return 0;
}
void push(char newdata, Node* &top) {
  Node* tempnext = new Node();
  tempnext->data = newdata;
  tempnext->next = top;
  top = tempnext;
}
//Three different types of print
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
  if(current != NULL) {
    if(isdigit(treepeek(current)->token) == false) {
      cout << "(";
    }
    infixprint(current->left);
    cout << current->token;
    infixprint(current->right);
    if(isdigit(treepeek(current)->token) == false) {
      cout << ")";
    }
  }
}
//Tree related functions, only applicable to the stack for binary tree construction
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
//Generates priority between operators
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
//Moves top of stack to the queue
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
//Deletes the top of the stack
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
//Returns the top of the stack
char peek(Node* top) {
  if(top != NULL) {
    return top->data;
  }
  else {
    return 'N';
  }
}
//Adds an element to the queue
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
//Returns the front of the queue
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
//Deletes the front of the queue don't ask why this couldn't be done in one function
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
//Big function to convert infix to postfix
void postfix(char input[], Node* & stack, Node* & queuefront, Node* & queuerear) {
  int i = 0;
  //If digit immediately go to queue
  while(i <= strlen(input)) {
    if(isdigit(input[i])) {
      enqueue(queuefront, queuerear, input[i]);
    }
    //If operator that isn't parenthese pop stack to queue until empty or until a token with different priority is read
    else if(input[i] == '^' || input[i] == '*' || input[i] == '+' || input[i] == '-' || input[i] == '/') {
      while(peek(stack) != 'N' && priority(peek(stack)) != 5 && priority(peek(stack)) >= priority(input[i]) && priority(input[i]) != 3) {
        popto(stack, queuefront, queuerear);
      }
      push(input[i], stack);
    }
    //Parenthese get pushed to stack
    else if (input[i] == '(') {
      push(input[i], stack);
    }
    /*Close parenthese runs through stack until open parenthese is found
      Pops everything that is found, excluding open parenthese
    */
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
    //Once there is nothing to read pop the entire stack
    else {
      while(stack != NULL) {
	popto(stack, queuefront, queuerear);	
      }
    }
    i++;
  }
}
