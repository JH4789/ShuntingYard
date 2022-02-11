#include "Tree.h"

Tree::Tree(char newtoken) {
  token = newtoken;
  left = NULL;
  right = NULL;
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

