#include <iostream>
#include <string>
#include <stack>
#include <cmath>

#include "TreeParser.h"

using std::stack;
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::pow;

//string of operators for use in private isOperator() method.
//global variable so that we don't need to initialize every time isOperator is called
static std::string operators_ = "+-*/^";

//Destructor
TreeParser::~TreeParser() {
    clear();
}

//public clear()
void TreeParser::clear() {
    clear(this->root);
}

//private clear()
void TreeParser::clear(Node *p) {
    //check if p is null pointer
    if(!p){
        return;
    }

    //if p is not nullptr, clear left and right children and set delete p
    clear(p->left);
    clear(p->right);
    delete p;
}

//public inOrderTraversal()
void TreeParser::inOrderTraversal() const {
    inOrderTraversal(this->root);
}

//private inOrderTraversal()
void TreeParser::inOrderTraversal(Node *p) const {
    //if nullptr, return
    if(!p){
        return;
    }

    //if not a nullptr, do in order traversal
    inOrderTraversal(p->left);
    cout << p->data << " ";
    inOrderTraversal(p->right);
}

//public postOrderTraversal()
void TreeParser::postOrderTraversal() const {
    postOrderTraversal(this->root);
}

//private postOrderTraversal()
void TreeParser::postOrderTraversal(Node *p) const {
    if(!p){
        return;
    }

    postOrderTraversal(p->left);
    postOrderTraversal(p->right);
    cout << p->data << " ";
}

//isDigit()
bool TreeParser::isDigit(char c) const {
    //check if char is between 0 and 9
    if(c >= '0' && c <= '9'){
        return true;
    }

    return false;
}

//isOperator
bool TreeParser::isOperator(char c) const {
    //for loop used on global operators_ variable
    for(int i = 0; i < operators_.length(); i++){
        if(c == operators_[i]){
            return true;
        }
    } //end for loop
    //if we made it out of the for loop, then c is not an operator
    return false;
}

//public processExpression()
void TreeParser::processExpression(std::string &expression) {
    //clear tree of any previous data
    clear();

    //check if expression is not empty
    //if so, load into this->expression
    if(!expression.empty()){
        this->expression = expression;
        this->position = 0;
        this->root = new Node;
        processExpression(this->root);
    }
}

//private processExpression()
void TreeParser::processExpression(Node *p) {
    //while loop for position being less than length
    while(this->position < expression.length()){
        //create a tempChar variable that is the current character at expression[position]
        char tempChar = expression[position];

        //check if tempChar is '('
        if(tempChar == '('){
            Node *tempNode = new Node;
            p->left = tempNode;
            position++;
            processExpression(tempNode);
        }

            //else check if tempChar isDigit or '.'
        else if (isDigit(tempChar) || tempChar == '.'){
            //create a tempString to concatenate to
            std::string tempString;
            while(isDigit(tempChar) || tempChar == '.'){
                tempString += tempChar;
                position++;
                tempChar = expression[position];
            }//end of while loop
            //the string now contains the number we need, store in node and return
            p->data = tempString;
            return;
        }

            //check if tempChar is an operator
        else if (isOperator(tempChar)){
            p->data = tempChar;
            Node *tempnode = new Node;
            p->right = tempnode;
            position++;
            processExpression(tempnode);
        }

            //check if tempChar is ')'
        else if(tempChar == ')'){
            position++;
            return;
        }

            //check if tempChar is ' '
        else if(tempChar == ' '){
            position++;
        }
        //end of if/else chain
    }
}

//public computeAnswer()
double TreeParser::computeAnswer() {
    //start the recursion
    computeAnswer(this->root);
    //after the tree has been iterated through, the only item in the stack is the answer
    return mathStack.top();
}

//private computeAnswer()
void TreeParser::computeAnswer(Node *ptr) {
    if(ptr){
        computeAnswer(ptr->left);
        computeAnswer(ptr->right);
        std::string data = ptr->data;
        double result; //variable to store the result data in

        //we need to check whether the data is a double or an operator.
        //We will assume no garbage data has been entered.
        //it will be easier to check if the data is an operator than if it is a double
        if(isOperator(data[0])){
            //pull the top two numbers off of the stack.
            double rightNum = mathStack.top();
            mathStack.pop();
            double leftNum = mathStack.top();
            mathStack.pop();

            //if/else change to figure out what operator we're using
            if(data[0] == '+'){
                result = leftNum + rightNum;
            }
            else if(data[0] == '-'){
                result = leftNum - rightNum;
            }
            else if(data[0] == '*'){
                result = leftNum * rightNum;
            }
            else if(data[0] == '/'){
                result = leftNum / rightNum;
            }
            else if(data[0] == '^'){
                result = pow(leftNum, rightNum);
            } //end of if/else chain
        } //end of if(isOperator)
            //if the data is not an operator, then it must be a double
        else {
            result = std::stod(data);
        }

        //put number back on mathStack
        mathStack.push(result);

    }//end of if(ptr)
}