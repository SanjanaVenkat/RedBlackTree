//Sanjana Venkat
//2.27.19
//Binary search tree, can add, print, and remove
#include <iostream>
#include <cstring>
#include "node.h"
#include <fstream>

using namespace std;  
//functions
void print(TreeNode* root, int level);
TreeNode* remove(TreeNode* realroot, TreeNode* root, TreeNode* parent, int num, int lr);
bool printlevel(TreeNode* root, int level, int startlevel);
void redblackupdate(TreeNode* root, TreeNode* parent);
TreeNode* rotate_right(TreeNode* root, TreeNode* current);
TreeNode* rotate_left(TreeNode* root, TreeNode* current);
void insertrecursive(TreeNode* root, TreeNode* n);
TreeNode* insertrepairtree(TreeNode* root, TreeNode* current);
TreeNode* case1(TreeNode* current, TreeNode* root);
TreeNode* case2(TreeNode* current, TreeNode* root);
void case3(TreeNode* current, TreeNode* uncle, TreeNode* root);
TreeNode* case4(TreeNode* current, TreeNode* root);
TreeNode* insert(TreeNode* root, int current);
TreeNode* case4_2(TreeNode* current, TreeNode* root);

//add to tree

TreeNode* insert(TreeNode* root, int current) {
  TreeNode* realroot = root;
  char black[2] = "B";
  TreeNode* n = new TreeNode(current, black);
  insertrecursive(root, n);

  //  cout << "Test1" << endl;
  // print(root, 0);
  root = insertrepairtree(root, n);
  // cout << root->getNumber() << endl;
  //print(root, 0);
  cout << root->getNumber() << endl;
  print(root, 0);
  //cout << "Root" << endl;
  /*if (root != NULL) {
    while (root->getParent(root, root->getNumber(), 0) != NULL) {
    
    root = root->getParent(root, root->getNumber(), 0);
     
    
    return root;
    }
    }
  */
    return root;
  

  }


TreeNode* insertrepairtree(TreeNode* root, TreeNode* current) {

   TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* grandparent = NULL;
   if (parent != NULL) {
    grandparent = parent->getParent(root, parent->getNumber(), 0);
   }
  TreeNode* uncle = NULL;
  if (parent != NULL) {
  if (grandparent != NULL) {
    if (grandparent->getLeft() == current->getParent(root, current->getNumber(), 0)) {
	if (grandparent->getRight() != NULL) {

	  uncle = grandparent->getRight();
	}
	else {
	  uncle = NULL;
	}
      }
    else if (grandparent->getRight() == current->getParent(root, current->getNumber(), 0)) {
	if (grandparent->getLeft() != NULL) {
	  uncle = grandparent->getLeft();
	}
	else {
	  uncle = NULL;
	}
	  }
	 }
  }
  //  cout << "STATS" << endl;
  //if (uncle != NULL) {
  //cout << "Uncle " << uncle->getNumber() << endl;
  //}
  
  if (current->getParent(root, current->getNumber(), 0) == NULL) {
    //cout << "Test4" << endl;
    //cout << "Case 1" << endl;
    root = case1(current, root);
    return root;
    //    cout << "Test8" << endl;
  }
  //cout << "Test9" << endl;
  else if (strcmp(current->getParent(root, current->getNumber(), 0)->getRedBlack(), "B") == 0) {
    //cout << "Case 2" << endl;
    case2(current, root);
  }
  
    else if (uncle != NULL && strcmp(uncle->getRedBlack(), "R") == 0) {
      //cout << "Case 3" << endl;
      case3(current, uncle, root);
    }
  
    else {
      //  cout << "Case 4" << endl;
      root = case4(current, root);
      return root;
    }
   
  }

TreeNode* case4(TreeNode* current, TreeNode* root) {
  cout << "Case 4" << endl;
  TreeNode* p = current->getParent(root, current->getNumber(), 0);
  TreeNode* g = NULL;
  if (p != NULL) {
    g = p->getParent(root, p->getNumber(), 0);
  }
  if (current == p->getRight() && p == g->getLeft()) {
    rotate_left(root, p);
    //    cout << "Rotated left" << endl;
    current = current->getLeft();
  }
  else if (current == p->getLeft() && p == g->getRight()) {
    rotate_right(root, p);
    //cout << "Rotated right" << endl;
    current = current->getRight();
  }
TreeNode* hold = case4_2(current, root);
 cout << hold->getNumber() << endl;
 return hold;
}

TreeNode*  case4_2(TreeNode* current, TreeNode* root) {
  cout << "Case 4 part 2" << endl;
  char black[2] = "B";
  char red[2] = "R";
  TreeNode* p;
  if (current != NULL) {
  p = current->getParent(root, current->getNumber(), 0);
  }
  TreeNode* g;
  if (p != NULL) {
    g = p->getParent(root, p->getNumber(), 0);
  }
  //cout << "Test" << endl;
  if (current == p->getLeft()) {
    //cout << "RR" << endl;
   rotate_right(root, g);
   //  cout << "Rotated right" << endl;
  }
  else {
    //cout << "RL" << endl;
    rotate_left(root, g);
    //cout << "Rotated Left" << endl;
  }
  p->setRedBlack(black);
  g->setRedBlack(red);
  return p;
}


TreeNode* case1(TreeNode* current, TreeNode* root) {
  cout << "Case 1" << endl;
  if(current->getParent(root, current->getNumber(), 0) == NULL) {
    //cout << "Test5" << endl;
    char black[2] = "B";
    current->setRedBlack(black);
    //cout << "Test6" << endl;
    return current;
    }
  }


TreeNode* case2(TreeNode* current, TreeNode* root) {
  cout << "Case 2" << endl;
  TreeNode* p;
  if (current != NULL) {
   p = current->getParent(root, current->getNumber(), 0);
  }
  char red[2] = "R";
  if (strcmp(p->getRedBlack(), "B") == 0) {
    if (p->getNumber() > current->getNumber()) {
      p->setLeft(current);
      current->setRedBlack(red);
    }
    else if (p->getNumber() < current->getNumber()) {
      p->setRight(current);
      current->setRedBlack(red);
    }
  }
  return root;
}

void case3(TreeNode* current, TreeNode* uncle, TreeNode* root) {
  cout << "Case 3" << endl;
  char black[2] = "B";
  char red[2] = "R";
  current->getParent(root, current->getNumber(), 0)->setRedBlack(black);
  uncle->setRedBlack(black);
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* grandparent = current->getParent(root, parent->getNumber(), 0);
  grandparent->setRedBlack(red);
  insertrepairtree(root, grandparent);
}

  
void insertrecursive(TreeNode* root, TreeNode* n) {

  char black[2] = "B";
  char red[2] = "R";
  TreeNode* newnode = n;
  if (root != NULL && newnode->getNumber() < root->getNumber()) {

    if (root->getLeft() != NULL) {
      TreeNode* left = root->getLeft();
      if (left->getLeft() == NULL || left->getRight() == NULL) {
  
      insertrecursive(left, newnode);
      //    cout << "Going left" << endl;
    }
    }
  else {

    root->setLeft(newnode);
    //cout << "Left" << endl;
    //return;
  }
    
    //cout << "D" << endl;
  }
  else if (root != NULL && newnode->getNumber() > root->getNumber()) {
    //cout << "Test" << endl;
      if (root->getRight() != NULL) {
	TreeNode* right = root->getRight();
	if (right->getRight() == NULL || right->getLeft() == NULL) {
       
	insertrecursive(right, newnode);
	//	cout << "Going right" << endl;
	}
      }
      else {
	root->setRight(newnode);
	//	cout << "Test2" << endl;
	//cout << "Right" << endl;
	//	return;
      }
      
  }
  TreeNode* p = newnode->getParent(root, newnode->getNumber(), 0);
  if (p != NULL) {
    p = root;
  }
  /*
  if (newnode != NULL && newnode != root) {
    cout << "Test" << endl;
    TreeNode* newnodep = newnode->getParent(root, newnode->getNumber(), 0);
  newnodep = root;
  TreeNode* nll = newnode->getLeft()->getLeft();
  nll= NULL;
  TreeNode* nlr = newnode->getLeft()->getRight();
  nlr = NULL;
  TreeNode* nrl = newnode->getRight()->getLeft();
  nrl = NULL;
  TreeNode* nrr = newnode->getRight()->getRight();
  nrr = NULL;
  */
newnode->setRedBlack(red);
   
  
}

//print levels
void print (TreeNode* root, int level) {
  int setlevel = 0;
  bool done = true;
  while (done == true) {
    done = printlevel(root, setlevel, 0);
    cout << endl;
    setlevel = setlevel + 1;
  }
}


//prints numbers in each level, recursive
bool printlevel(TreeNode* root, int level, int startlevel) {
  bool check = false;
  if (root != NULL) {
  if (startlevel == level) {
    cout << root->getNumber() << root->getRedBlack() << " ";
    check = true;
  }
  else {
    if (root->getLeft() != NULL) {
      check = printlevel(root->getLeft(), level, startlevel+1);
      //    cout << " ";
    }
    
    if (root->getRight() != NULL) {
      //cout << " ";
      check = printlevel(root->getRight(), level, startlevel+1);
    }

  }
  return check;
  }

}

//remove
TreeNode* remove (TreeNode* realroot, TreeNode* root, TreeNode* parent, int num, int lr) {
  
}




TreeNode* rotate_right(TreeNode* root, TreeNode* current)  {
  cout << "Rotate right" << endl;
  //  cout << "Current " << current->getNumber() << endl;
  TreeNode* newcurrent = current->getLeft();
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* gp = root;
  if (parent != NULL && parent != root) {
    gp = parent->getParent(root, parent->getNumber(), 0);
  }
  //  cout << "Test" << endl;
  // cout << "Newcurrent " << newcurrent->getNumber() << endl;
  //if (parent != NULL) {
  //cout << "Parent " << parent->getNumber() << endl;
  // }
  //cout << parent->getNumber() << endl;
  
  current->setLeft(newcurrent->getRight());
  newcurrent->setLeft(newcurrent->getLeft());
  newcurrent->setRight(current);
  if (parent == NULL) {
    newcurrent->getLeft()->setLeft(NULL);
    newcurrent->getLeft()->setRight(NULL);
    newcurrent->getRight()->setLeft(NULL);
    newcurrent->getRight()->setRight(NULL);
    return newcurrent;
  }
  //  current->setRight(current->getLeft());
  //  cout << "Test2" << endl;
  //newcurrent->setLeft(newcurrent->getLeft());
  /*
  if (parent != NULL) {

    if (newcurrent->getLeft() != NULL &&newcurrent ->getLeft()->getNumber() == parent->getNumber()) {
      cout << "Test" << endl;
    parent->setLeft(NULL);
  }
    else if (newcurrent->getRight() != NULL && newcurrent->getRight()->getNumber() == parent->getNumber()) {
      cout << "TEst" << endl;
    parent->setRight(NULL);
  }
  }
  */
  //  newcurrent->setLeft(
  //  print(root, 0);
  //newcurrent->setLeft();
  cout << "STATS: " << endl;
  cout << "Current: " << current->getNumber() << endl;
  cout << "NewCurrent: " << newcurrent->getNumber() << endl;
  if (parent != NULL) {
  cout << "Parent: " << parent->getNumber() << endl;
  }
  if (gp != NULL) {
    cout << "GP: " << gp->getNumber() << endl;
  }

  //newcurrent->getParent(root, newcurrent->getNumber(), 0) = parent;
  /*
  if (newcurrent->getLeft() != NULL) {
    //cout << "Test" << endl;
    TreeNode* holdparent = current->getLeft()->getParent(root, current->getLeft()->getNumber(), 0);
    holdparent = current;
    }
  //cout << "Test" << endl;
   if (parent != NULL)  {

    if (current == parent->getLeft()) {
            parent->setLeft(newcurrent);
    }
    else if (current == parent->getRight()) {
      //cout << "Test" << endl;
      parent->setRight(newcurrent);
    }
  */
   
    if (parent != NULL && gp != NULL) {
      //cout << gp->getNumber() << endl;
      if (gp->getNumber() >newcurrent->getNumber()) {
	gp->setLeft(newcurrent);
      }
      else if (gp->getNumber() < newcurrent->getNumber()) {
	gp->setRight(newcurrent);
      }
    }
    return root;
      // }
     
    //    cout << "Done" << endl;
 
    //return parent;
}



TreeNode* rotate_left(TreeNode* root, TreeNode* current) {
  TreeNode* realroot = root;
  cout << "Rotate left" << endl;
  TreeNode* newcurrent = current->getRight();
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* gp = root;
  cout << "STATS: " << endl;
  cout << "Current: " << current->getNumber() << endl;
  cout << "Newcurrent: " << newcurrent->getNumber() << endl;
  if (parent != NULL) {
    cout << "Parent: " << parent->getNumber() << endl;
  }
  if (gp != NULL) {
    cout << "Gp: " << gp->getNumber() << endl;
  }

  if (parent != NULL && parent != root) {
    gp = parent->getParent(root, parent->getNumber(), 0);
    
  }  
  current->setRight(newcurrent->getLeft());
  newcurrent->setRight(newcurrent->getLeft());
  if (gp != NULL && current->getNumber() != gp->getNumber()) {
  newcurrent->setLeft(current);
  }
  if (gp == NULL && current->getNumber() != gp->getNumber()) {
    // cout << "In this" << endl;
    if (newcurrent->getLeft() != NULL) {
    newcurrent->getLeft()->setLeft(NULL);
    newcurrent->getLeft()->setRight(NULL);
    }
    if (newcurrent->getRight() != NULL) {
    newcurrent->getRight()->setLeft(NULL);
    newcurrent->getRight()->setRight(NULL);
    }
    return newcurrent;
  }
  //  cout << "Test" << endl;
  //newcurrent->setRight(parent);
  //TreeNode* h = newcurrent->getParent(root, newcurrent->getNumber(), 0);
  //h = parent;
  /*
  if (current->getRight() != NULL) {
    TreeNode* holdparent = current->getRight()->getParent(root, current->getLeft()->getNumber(), 0);
    holdparent = current;
  }
  */
  // cout << "Test" << endl;
  if (parent != NULL) {
    if (current == parent->getRight()) {
          parent->setRight(newcurrent);
    }
    else if (current == parent->getLeft()) {
      parent->setLeft(newcurrent);
    }
    //TreeNode* holdparent2 = current->getLeft()->getParent(root, newcurrent->getNumber(), 0);
    //holdparent2 = parent;
  
  }
   
 if (gp != NULL) {
    //cout << gp->getNumber() << endl;
  if (gp->getNumber() > newcurrent->getNumber()) {
    gp->setLeft(newcurrent);
    gp->setRight(gp->getRight());
  }
  else if (gp->getNumber() < newcurrent->getNumber()) {
    gp->setRight(newcurrent);
    gp->setLeft(gp->getLeft());
  }
  
  if (gp->getParent(root, gp->getNumber(), 0) == NULL) {
    cout << gp->getNumber() << endl;
    //cout << "This" << endl;
    return gp;
  }

   }
 // cout << "Thissss" << endl;
  return realroot;
  //  return newcurrent;
  //  print(gp, 0);

}

void redblackupdate(TreeNode* root, TreeNode* parent) {
  char black[2] = "B";
  char red[2] = "R";
  if (root != NULL) {
  if (parent == NULL) {
    root->setRedBlack(black);
    if (root->getLeft() != NULL) {
      redblackupdate(root->getLeft(), root);
    }
    if (root->getRight() != NULL) {
      redblackupdate(root->getRight(), root);
    }
  }
  else {
    if (strcmp(parent->getRedBlack(), black) == 0) {
    root->setRedBlack(red);
    if (root->getLeft() != NULL) {
      redblackupdate(root->getLeft(), root);
    }
    if (root->getRight() != NULL) {
      redblackupdate(root->getRight(), root);
    }
    }
    else {
      root ->setRedBlack(black);
      if (root->getLeft() != NULL) {
	redblackupdate(root->getLeft(), root);
      }
      if (root->getRight() != NULL) {
	redblackupdate(root->getRight(), root);
      }
    }
  }
  }

}


int main() {
  bool running = true;
  int response = 0;
  cout << "Enter 1 for add, 2 for print, 3 for delete, 4 to find parent of a node" << endl;
  cin >> response;
  TreeNode* root = NULL;
  while (running != false) {
    //add
  if (response == 1) {
    int responset;
    cout << "Enter 1 to enter from command line, or 2 to have numbers read from file" << endl;
    cin >> responset;
    //command line
    if (responset == 1) {
    cout << "How many numbers do you want to enter?" << endl;
  int numofnum = 0;
  cin >> numofnum;
  cout << "Enter your numbers, seperate with spaces" << endl;
  int counter = 0;
  int num = 0;
  while (counter != numofnum) {
    cin >> num;
    if (root == NULL) {
root = insert(root, num);
    }
  else {
    insert(root, num);
  }
  counter++;
  }
  //  redblackupdate(root, NULL);
    }
    //file
  else if (responset == 2) {
    ifstream inData;
     cout << "Enter filename" << endl;
    char filename[1000];
    cin >> filename;
    inData.open(filename);
    int datanum;
    int num;
    while (inData >> num) {
      datanum = num;
      if (root == NULL) {
	//	root = add(root, datanum);
      }
      else {
	//add(root, datanum);
      }
    }

  }
  
   cout << "Enter 1 for add, 2 for print, 3 for delete, and 4 to find parent" << endl;
  cin >> response;
  }
  //print
  if (response == 2) {
    cout << "Tree:" << endl;
     print(root, 0);
 cout << "Enter 1 for add, 2 for print, 3 for delete, and 4 to find parent" << endl;
  cin >> response;
  }
  //delete
  if (response == 3) {
    int numofnum = 0;
    int num = 0;
  int delcounter = 0;
  cout << "Enter how many numbers you want to delete" << endl;
  cin >> numofnum;
  cout << "Enter your numbers, seperate with spaces" << endl;
  while (delcounter != numofnum) {
    cin >> num;
    root = remove(root, root, NULL, num, 0);
       delcounter = delcounter + 1;
      }
  cout << "Done deleting" << endl;
   cout << "Enter 1 for add, 2 for print, 3 for delete, and 4 to find parent" << endl;
  cin >> response;

  }
  if (response == 4) {
    int current = 0;
    cout << "Enter node to find parent of" << endl;
    cin >> current;
    TreeNode* holder = root->getParent(root, current, 4);
   cout << holder->getNumber() << endl;
   cout << "Enter 1 for add, 2 for print, 3 for delete, and 4 to find parent" << endl;
   cin >> response;
  }
  }
  if (response != 1 && response != 2 && response != 3) {
    running = false;
    return 0;
  }
}
