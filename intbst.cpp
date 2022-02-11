// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
  if (n){
    printInOrder(n->left);
    cout << n->info << " "; 
    printInOrder(n->right);
  }
    // IMPLEMENT HERE
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
  if (n){
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
    
  }
    // IMPLEMENT HERE
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
  if (n){
    return(n->info + sum(n->right) + sum(n->left));
  } else{ 
    return 0;
  } // REPLACE THIS NON-SOLUTION
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
  if (n){
    return(1 + count(n->right) + count(n->left));
  }
  return 0; // REPLACE THIS NON-SOLUTION
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
  if(!n) return nullptr;
  if (n->info == value) return n;
  if (getNodeFor(value, n->right)) return getNodeFor(value, n->right);
  if (getNodeFor(value, n->left)) return getNodeFor(value, n->left);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
  if(!this->root) return false;
  if (this->root->info == value) return true;
  IntBST* right = new IntBST;
  right->root = this->root->right;
  IntBST* left = new IntBST;
  left->root = this->root->left;
  if (left->contains(value) || right->contains(value)) return true;// REPLACE THIS NON-SOLUTION
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
  Node * n = new Node;
  n = getNodeFor(value, this->root);
  if(!n) return nullptr;
  if(n->left){
    n = n->left;
    while(n->right){
      n = n->right;
    }
    return(n);
  } else{
    while(n->parent){
      if(n->parent->info < n->info){
        return(n->parent);
      }
      else{
        n = n->parent;
      }
    }
  }
  return nullptr;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
  Node* n = getPredecessorNode(value);
  if(!n) return 0;
  return(n->info); // REPLACE THIS NON-SOLUTION
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
  Node* n = new Node;
  n = getNodeFor(value, this->root);
  if (!n) return nullptr;
  if(n->right){
    n = n->right;
    while(n->left){
      n = n->left;
    }
    return(n);
  }
  else{
    while(n->parent){
      if(n->parent->info > n->info){
        return(n->parent);
      }
      else{
        n = n->parent;
      }
    }
  }

  return nullptr; // REPLACE THIS NON-SOLUTION
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
  Node* n = getSuccessorNode(value);
  //cout << "makes here " << endl;
  if(!n) return 0;
  //cout << "does make here " << endl;
  return(n->info);// REPLACE THIS NON-SOLUTION
}


// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
  if(!this->contains(value)) return false;
  
  Node* n = new Node;
  n = getNodeFor(value, this->root);
  int val = 0;
  if(n->right && n->left){
    Node* t = getSuccessorNode(n->info);
    val = t->info;
    remove(t->info);
    n->info = val;
    return true;
  }
  else if(n->right || n->left){
    Node* t = n;
    if(n->right){
      if(n->parent->right){
        n->parent->right = n->right;
      }
      else{
        n->parent->left = n->right;
      }
    }
    else{
      if(n->parent->right){
        n->parent->right = n->left;
      }
      else{
        n->parent->left = n->left;
      }
    }
    delete t;
    return true;
  }
  else if((n->right == NULL) && (n->left == NULL)){
    if(n->parent->left){
      n->parent->left = nullptr;
    }
    else{
      n->parent->right = nullptr;
    }
    delete n;
    return true;
  }
  

   // REPLACE THIS NON-SOLUTION
}

/*
if(n == this->root){
    cout << "root function called" << endl;
    if(getSuccessorNode(n->info)){
      n = getSuccessorNode(n->info);
      if(n!= this->root->right){
        n->right = this->root->right
      }
    }
  }
  
  if(getSuccessor(n->info) != 0){
    n = getSuccessorNode(n->info);
  }else{
    n = getPredecessorNode(n->info);
  }
  if(root_checker){
    if(n != this->root->right){
      n->right = this->root->right;
    }
    if(n != this->root->left){
      n->left = this->root->left;
    }

    this->root = n;

  }
  delete delNode;
  */