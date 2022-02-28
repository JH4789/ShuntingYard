#include "Tree.h"

Tree::Tree() {
  left = NULL;
  next = NULL;
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

