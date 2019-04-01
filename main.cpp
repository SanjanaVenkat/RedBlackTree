//Sanjana Venkat
//2.27.19
//Binary search tree, can add, print, and remove
#include <iostream>
#include <cstring>
#include "node.h"
#include <fstream>

using namespace std;  
//functions
TreeNode* add(TreeNode* root, int num);
void print(TreeNode* root, int level);
TreeNode* remove(TreeNode* realroot, TreeNode* root, TreeNode* parent, int num, int lr);
bool printlevel(TreeNode* root, int level, int startlevel);

//add to tree
TreeNode* add(TreeNode* root, int num) {
  //root
  if (root == NULL) {

    root = new TreeNode(num);
    return root;
  }
  //do nothing if number already exists
  else if (root->getNumber() == num) {
    
  }
  //less, add left
  else if (num < root->getNumber()) {

    if (root->getLeft() != NULL) {
    add(root->getLeft(), num);
    }
    else {

      TreeNode* newleft = new TreeNode(num);
      root->setLeft(newleft);
      return newleft;
    }
  }
  //greater, add right
  else if (num > root->getNumber()) {

    if (root->getRight() != NULL) {
    add(root->getRight(), num);
    }
    else {

      TreeNode* newright = new TreeNode(num);
      root->setRight(newright);
      return newright;
    }
  }
  
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
    cout << root->getNumber() << " ";
    check = true;
  }
  else {
    if (root->getLeft() != NULL) {
      check = printlevel(root->getLeft(), level, startlevel+1);
    }
    //fixed error in print where it looked like delete was not working correctly
    if (root->getRight() != NULL) {
      bool checkhold = printlevel(root->getRight(), level, startlevel+1);
      if (check == true) {
	return check;
      }
      else{
	return checkhold;
      }
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
	//		cout << "Case 1" << endl;
	parent->setLeft(NULL);
	delete root;
	done = true;
	return realroot;
      }
      //right
       if (lr == 2) {
	 //   cout << "Case 2" << endl;
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
	   // cout << "Case 5" << endl;
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
	//	cout << "Case 10" << endl;
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
	TreeNode* prev = NULL;
	while (rootmoverright->getLeft() != NULL) {
	  prev = rootmoverright;
	  rootmoverright = rootmoverright->getLeft();
      }
	if (rootmoverright->getNumber() == prev->getLeft()->getNumber()) {
	prev->setLeft(NULL);
	}
	else if (rootmoverright->getNumber() == prev->getRight()->getNumber()) {
	  prev->setRight(NULL);
	}
	if (rootmoverright->getLeft() != NULL) {
	  if (rootmoverright->getLeft()->getNumber() < prev->getNumber() && prev->getLeft() == NULL) {
	    prev->setLeft(rootmoverright->getLeft());
	  }
	  else if (rootmoverright->getLeft()->getNumber() > prev->getNumber() && prev->getRight() == NULL) {
	    prev->setRight(rootmoverright->getLeft());
	  }
	}
	if (rootmoverright->getRight() != NULL) {
          if (rootmoverright->getRight()->getNumber() < prev->getNumber() && prev->getLeft() == NULL) {
            prev->setLeft(rootmoverright->getRight());
          }
          else if (rootmoverright->getRight()->getNumber() > prev->getNumber() && prev->getRight() == NULL) {
            prev->setRight(rootmoverright->getRight());
          }
        }

	rootmoverright->setLeft(root->getLeft());
	rootmoverright->setRight(root->getRight());
      delete root;
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


int main() {
  bool running = true;
  int response = 0;
  cout << "Enter 1 for add, 2 for print, 3 for delete, and 4 to find the parent of a node" << endl;
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
root = add(root, num);
  }
  else {
    add(root, num);
  }
  counter++;
  }
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
	root = add(root, datanum);
      }
      else {
	add(root, datanum);
      }
    }

  }
  
   cout << "Enter 1 for add, 2 for print, 3 for delete, and 4 to find the parent of a node" << endl;
  cin >> response;
  }
  //print
  if (response == 2) {
    cout << "Tree:" << endl;
    print(root, 0);
 cout << "Enter 1 for add, 2 for print, 3 for delete, and 4 to find the parent of a node" << endl;
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
   cout << "Enter 1 for add, 2 for print, 3 for delete and 4 to find the parent of a node" << endl;
  cin >> response;

  }
  

  else if (response == 4) {
    int current = 0;
    cout << "Enter node to find parent of" << endl;
    cin >> current;
    TreeNode* holder = root->getParent(root, current, 4);
    if (holder != NULL) {
      cout << holder->getNumber() << endl;
    }
    else {
      cout << "Parent for this node doesn't exist" << endl;
    }
    cout << "Enter 1 for add, 2 for print, 3 for delete, and 4 to find parent of a node" << endl;
    cin >> response;
  }
}
}
