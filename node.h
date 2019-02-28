#include <iostream>
#include <cstring>

using namespace std;


class TreeNode {
 public:
  TreeNode(int n);
  ~TreeNode();
  TreeNode* getLeft();
  void setLeft(TreeNode* newleft);
  TreeNode* getRight();
  void setRight(TreeNode* newright);
  int getNumber();
 private:
  TreeNode* left;
  TreeNode* right;
  int number;
};
