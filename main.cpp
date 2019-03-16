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
void rotate_right(TreeNode* root, TreeNode* current);
void insertrecursive(TreeNode* root, TreeNode* n);
TreeNode* insertrepairtree(TreeNode* root, TreeNode* current);
TreeNode* case1(TreeNode* current, TreeNode* root);
void case2(TreeNode* current, TreeNode* root);
void case3(TreeNode* current, TreeNode* uncle, TreeNode* root);
//void case4(TreeNode* current);
TreeNode* insert(TreeNode* root, int current);

//add to tree

TreeNode* insert(TreeNode* root, int current) {
  TreeNode* realroot = root;
  char black[2] = "B";
  TreeNode* n = new TreeNode(current, black);
  insertrecursive(root, n);

  //  cout << "Test1" << endl;
  // print(root, 0);
  root = insertrepairtree(root, n);
  //cout << "Root" << endl;
  if (root != NULL && root->getParent(root, root->getNumber(), 0) != NULL) {
    
    while (root->getParent(root, root->getNumber(), 0) != NULL) {
    
    root = root->getParent(root, root->getNumber(), 0);
     return root;
    }
  }
  return root;
  

  }


TreeNode* insertrepairtree(TreeNode* root, TreeNode* current) {

   TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* grandparent;
   if (parent != NULL) {
    grandparent = parent->getParent(root, parent->getNumber(), 0);
   }
  TreeNode* uncle;
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
  if (current->getParent(root, current->getNumber(), 0) == NULL) {
    //cout << "Test4" << endl;
    root = case1(current, root);
    return root;
    //    cout << "Test8" << endl;
  }
  //cout << "Test9" << endl;
  else if (strcmp(current->getParent(root, current->getNumber(), 0)->getRedBlack(), "B") == 0) {

    case2(current, root);
  }
  
    else if (uncle != NULL && strcmp(uncle->getRedBlack(), "R") == 0) {

      case3(current, uncle, root);
    }
  /*
    else {
    }
   */
  }


TreeNode* case1(TreeNode* current, TreeNode* root) {
  if(current->getParent(root, current->getNumber(), 0) == NULL) {
    //cout << "Test5" << endl;
    char black[2] = "B";
    current->setRedBlack(black);
    //cout << "Test6" << endl;
    return current;
    }
  }


void case2(TreeNode* current, TreeNode* root) {

  TreeNode* p = current->getParent(root, current->getNumber(), 0);
  char red[2] = "R";
  if (strcmp(p->getRedBlack(), "B") == 0) {
    if (p->getNumber() > current->getNumber()) {
      p->setLeft(current);
    }
    else if (p->getNumber() < current->getNumber()) {
      p->setRight(current);
      current->setRedBlack(red);
    }
  }
}

void case3(TreeNode* current, TreeNode* uncle, TreeNode* root) {
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
  bool done = false;
  if (root->getNumber() == num) {
    //node has no children
    if (root->getLeft() == NULL && root->getRight() == NULL) {
      //left
      if (lr == 1) {
	//	cout << "Case 1" << endl;
	parent->setLeft(NULL);
	delete root;
	done = true;
	return realroot;
      }
      //right
       if (lr == 2) {
	 //	cout << "Case 2" << endl;
	parent->setRight(NULL);
	delete root;
	done = true;
	return realroot;
      }
       //root
      if (lr == 0) {
	//cout << "Case 3" << endl;
	delete root;
	done = true;
	return NULL;
      }
    }
    //node has right child
    if (root->getLeft() == NULL && root->getRight() != NULL) {
      //left
      if (lr == 1) {
	  //cout << "Case 4" << endl;
	parent->setLeft(root->getRight());
	done = true;
	return realroot;
	}
      //right
	 if (lr == 2) {
	   //cout << "Case 5" << endl;
	  parent->setRight(root->getRight());
	  done = true;
	  return realroot;
	}
	 //root
	 if (lr == 0) {
	   //cout << "Case 6" << endl;
	root = root->getRight();
	done = true;
	return root;
	}
    }
    //node has left child
     if (root->getRight() == NULL && root->getLeft() != NULL) {
       //left
       if (lr == 1) {
	  //cout << "Case 7" << endl;
	parent->setLeft(root->getLeft());
	done = true;
	return realroot;
	}
       //right
	 if (lr == 2) {
	   //cout << "Case 8" << endl;
	  parent->setRight(root->getLeft());
	  done = true;
	  return realroot;
	 }
	 //	 root
	 if (lr == 0) {
	   //cout << "Case 9" << endl;
	root = root->getLeft();
	done = true;
	return root;
	}
    }
     //node has two children
    if (root->getLeft() != NULL && root->getRight() != NULL) {
      //left
      if (lr == 1) {
	//cout << "Case 10" << endl;
      TreeNode* moverright = root->getRight();
      while (moverright->getLeft() != NULL) {
	moverright = moverright->getLeft();
      }
      parent->setLeft(root->getRight());
      moverright->setLeft(root->getLeft());
      delete root;
      done = true;
      return realroot;
      }
      //right
      if (lr == 2) {
	//cout << "Case 11" << endl;
	TreeNode* moverleft = root->getLeft();
	while (moverleft->getRight() != NULL) {
	  moverleft = moverleft->getRight();
	}
	parent->setRight(root->getLeft());
	moverleft->setRight(root->getRight());
	delete root;
	done = true;
	return realroot;
      }
      //root
       if (lr == 0) {
	 //cout << "Case 12" << endl;
	TreeNode* rootmoverright = root->getRight();
	while (rootmoverright->getLeft() != NULL) {
	rootmoverright = rootmoverright->getLeft();
      }
      rootmoverright->setLeft(root->getLeft());
      root = rootmoverright;
      done = true;
      return root;
      }
      

      
    }



  }
  if (done == false) {
    //recursive, gets left or right of parent
  if (root->getLeft() != NULL) {
    //cout << "Test 1" << endl;
    remove (realroot, root->getLeft(), root, num, 1);
  }
  if (root->getRight() != NULL) {
    //cout << "Test 2" << endl;
    remove (realroot, root->getRight(), root, num, 2);

  }
  else {
    //    cout << "Number not found" << endl;
    return realroot;
  }
  }
  

}




void rotate_right(TreeNode* root, TreeNode* current)  {
  TreeNode* newcurrent = current->getLeft();
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  if (newcurrent->getLeft() != NULL && newcurrent->getRight() != NULL) {
  current->setLeft(newcurrent->getRight());
  newcurrent->setRight(current);
  parent = newcurrent;
  if (current->getLeft() != NULL) {
    TreeNode* holdparent = current->getLeft()->getParent(root, current->getLeft()->getNumber(), 0);
    holdparent = current;
  }
  if (parent != NULL)  {
    if (current == parent->getLeft()) {
      parent->setLeft(newcurrent);
    }
    else if (current == parent->getRight()) {
      parent->setRight(newcurrent);
    }
    TreeNode* holdparent2 = current->getRight()->getParent(root, newcurrent->getNumber(), 0);
   holdparent2 = parent;
  }
  }
}

void rotate_left(TreeNode* root, TreeNode* current) {
  TreeNode* newcurrent = current->getRight();
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  if (newcurrent->getLeft() != NULL && newcurrent->getRight()) {
  current->setRight(newcurrent->getLeft());
  newcurrent->setLeft(current);
  parent = newcurrent;
  if (current->getRight() != NULL) {
    TreeNode* holdparent = current->getRight()->getParent(root, current->getLeft()->getNumber(), 0);
    holdparent = current;
  }
  if (parent != NULL) {
    if (current == parent->getRight()) {
      parent->setRight(newcurrent);
    }
    else if (current == parent->getLeft()) {
      parent->setLeft(newcurrent);
    }
    TreeNode* holdparent2 = current->getLeft()->getParent(root, newcurrent->getNumber(), 0);
    holdparent2 = parent;
  }
  }
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
