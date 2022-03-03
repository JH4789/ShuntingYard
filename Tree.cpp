#include "Tree.h"
//Functions that aren't used a ton, constructor is the most important one
Tree::Tree() {
  left = NULL;
  right = NULL;
}
void Tree::setLeft(Tree* newleft) {
  left = newleft;
}
void Tree::setRight(Tree* newright) {
  right = newright;
}
Tree* Tree::getLeft() {
  return left;
}
Tree* Tree::getRight() {
  return right;
}
char Tree::returnToken() {
  return token;
}

