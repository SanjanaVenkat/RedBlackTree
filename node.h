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
  TreeNode* getParent(TreeNode* root, int current, int out);
private:
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;
  int number;
};
