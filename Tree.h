#ifndef TREEHEADER
#define TREEHEADER
#include <iostream>
class Tree{
 public:
  Tree();
  Tree* getLeft();
  Tree* getRight();
  
  void setLeft(Tree* newleft);
  void setRight(Tree* newright);
  char returnToken();
  Tree* next;
  char token;
  Tree* left;
  Tree* right;
};













#endif
