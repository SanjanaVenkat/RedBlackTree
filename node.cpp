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

TreeNode* TreeNode::getParent(TreeNode* root, int current, int willoutput) {
  if (root == NULL) {
     parent = NULL;
    return parent;
  }
  else {
    while (root->getNumber() != current) {
      //cout << "Test" << endl;
      if (root->getLeft() != NULL) {
      if (root->getLeft()->getNumber() == current) {
        //cout << "Case1" << endl;
        parent = root;
        if (willoutput == 4) {
          cout << "I am the left child of ";
        }
        return parent;
      }
      }
      if (root->getRight() != NULL) {
     if (root->getRight()->getNumber() == current) {
       //cout << "Case2" << endl;
      parent = root;
      if (willoutput == 4) {
        cout << "I am the right child of ";
      }
        return parent;
    }
      }

     if (root->getLeft() != NULL && root->getNumber() > current) {
       // cout << "Case3" << endl;
      root = root->getLeft();
      }
    else if (root->getRight() != NULL && root->getNumber() < current) {
      // cout << "Case4" << endl;
      root = root->getRight();
    }

    else {
      return NULL;
    }
    }
  }
}
