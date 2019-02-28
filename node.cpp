#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

TreeNode::TreeNode(int n, char* rb) {
  left = NULL;
  right = NULL;
  number = n;
  strcpy(redblack, rb);
}

TreeNode::~TreeNode() {
  left = NULL;
  right = NULL;
}

void TreeNode::setLeft(TreeNode* newleft) {
  left = newleft;
}

void TreeNode::setRight(TreeNode* newright) {
  right = newright;
}

TreeNode* TreeNode::getLeft() {
  return left;
}

TreeNode* TreeNode::getRight() {
  return right;
}

int TreeNode::getNumber() {
  return number;
}

char* TreeNode::getRedBlack() {
  return redblack;
}

void TreeNode::setRedBlack(char* rb) {
  strcpy(redblack,rb);
}
