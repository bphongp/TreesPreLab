// Bamphiane Annie Phongphouthai
// bp8qg
// October 3, 2017
// TreeCalc.cpp:  CS 2150 Tree Calculator method implementations

#include "TreeCalc.h"
#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

//Constructor
TreeCalc::TreeCalc() {
  mystack = stack<TreeNode*>();
}

//Destructor- frees memory
TreeCalc::~TreeCalc() {
  while(mystack.size()!= 0){
    cleanTree(mystack.top());
    mystack.pop();
  }
}

//Deletes tree/frees memory
void TreeCalc::cleanTree(TreeNode* ptr) {
  if (ptr->left!=NULL){
    cleanTree(ptr->left);  //delete pointer to left
    cleanTree(ptr->right); //delete pointer to right
  }
  else{
    delete ptr;
  }
}

//Gets data from user DO NOT ALTER
void TreeCalc::readInput() {
    string response;
    cout << "Enter elements one by one in postfix notation" << endl
         << "Any non-numeric or non-operator character,"
         << " e.g. #, will terminate input" << endl;
    cout << "Enter first element: ";
    cin >> response;
    //while input is legal
    while (isdigit(response[0]) || response[0]=='/' || response[0]=='*'
            || response[0]=='-' || response[0]=='+' ) {
        insert(response);
        cout << "Enter next element: ";
        cin >> response;
    }
}

//Puts value in tree stack
void TreeCalc::insert(const string& val) {
    // insert a value into the tree
  TreeNode *node = new TreeNode(val);
  if(val=="+" || val =="*" || val== "-" || val == "/"){ //check if operator
    node->right=mystack.top();
    mystack.pop();
    node->left=mystack.top();
    mystack.pop();
    mystack.push(node);
  }
  else{
    node->value =val;
    mystack.push(node);
  }
}

//Prints data in prefix form
void TreeCalc::printPrefix(TreeNode* ptr) const {
    // print the tree in prefix format
  if(ptr != NULL){
    cout<< ptr->value<<" ";
    printPrefix(ptr->left);
    printPrefix(ptr->right);
  }
}

//Prints data in infix form
void TreeCalc::printInfix(TreeNode* ptr) const {
    // print tree in infix format with appropriate parentheses
  if(ptr != NULL && (ptr->value=="+" || ptr->value=="*"
  || ptr->value=="-" || ptr->value =="/")){
    cout<<"( ";
    printInfix(ptr->left);
    cout<< " "<<ptr->value<<" ";
    printInfix(ptr->right);
    cout<<" )";
  }
  else{
    cout<<ptr->value;
  }
}

//Prints data in postfix form
void TreeCalc::printPostfix(TreeNode* ptr) const {
    // print the tree in postfix form
  if(ptr!=NULL){
    printPostfix(ptr->left);
    printPostfix(ptr->right);
    cout<<ptr->value<< " ";
  }
}

// Prints tree in all 3 (pre,in,post) forms
// ONLY ALTER is to implement printPrefix(), printPostfix(), and printInoder()
void TreeCalc::printOutput() const {
    if (mystack.size()!=0 && mystack.top()!=NULL) {
        cout << "Expression tree in postfix expression: ";
        printPostfix(mystack.top());// call your implementation of printPostfix()
        cout << endl;
        cout << "Expression tree in infix expression: ";
        printInfix(mystack.top());// call your implementation of printInfix()
        cout << endl;
        cout << "Expression tree in prefix expression: ";
        printPrefix(mystack.top());// call your implementation of printPrefix()
        cout << endl;
    } else
        cout<< "Size is 0." << endl;
}

//Evaluates tree, returns value
// private calculate() method
int TreeCalc::calculate(TreeNode* ptr) const {
    // Traverse the tree and calculates the result
  if(ptr->left==NULL){
    return atoi(ptr->value.c_str());
  }
  else if(ptr ->value=="+"){
    return(calculate(ptr->left)+calculate(ptr->right));
  }
  else if(ptr ->value=="*"){
    return(calculate(ptr->left)*calculate(ptr->right));
  }
  else if(ptr ->value=="-"){
    return(calculate(ptr->left)-calculate(ptr->right));
  }
  else if(ptr ->value=="/"){
    return(calculate(ptr->left)/calculate(ptr->right));
  }
  else{
    return atoi(ptr->value.c_str());
  }
}

//Calls calculate, sets the stack back to a blank stack
// public calculate() method. Hides private data from user
int TreeCalc::calculate() {
    int i = 0;
    while(mystack.size() !=0){ // call private calculate method here
      i+=calculate(mystack.top());
      mystack.pop();
    }
    return i;
}
