#ifndef TREEHEADER
#define TREEHEADER
#include <iostream>
class Tree{
 public:
  Tree(char newtoken);
  Tree* getLeft();
  Tree* getRight();
  char returnToken();
 private:

  char token;
  Tree* left;
  Tree* right;
};













#endif
