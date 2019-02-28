#include <iostream>
#include <cstring>

using namespace std;


class TreeNode {
 public:
  TreeNode(int n, char* rb);
  ~TreeNode();
  TreeNode* getLeft();
  void setLeft(TreeNode* newleft);
  TreeNode* getRight();
  void setRight(TreeNode* newright);
  int getNumber();
  char* getRedBlack();
  void setRedBlack(char* rb);
 private:
  TreeNode* left;
  TreeNode* right;
  int number;
  char redblack[1];
};
