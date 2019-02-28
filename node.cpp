#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

TreeNode::TreeNode(int n) {
  left = NULL;
  right = NULL;
  number = n;
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
