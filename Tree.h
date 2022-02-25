#ifndef TREEHEADER
#define TREEHEADER
#include <iostream>
class Tree{
 public:
  Tree(char newtoken);
  Tree* getLeft();
  Tree* getRight();
  
  void setLeft(Tree* newleft);
  void setRight(Tree* newright);
  char returnToken();
 private:

  char token;
  Tree* left;
  Tree* right;
};













#endif
