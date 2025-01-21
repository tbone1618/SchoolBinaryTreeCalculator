#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <chrono>
#include <stack>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stack;

struct Node
{
  string data;
  Node* left{ nullptr };
  Node* right{ nullptr };
};

class TreeParser
{
public:
  ~TreeParser();
  void clear();
  void inOrderTraversal() const;
  void postOrderTraversal() const;
  void processExpression(string& expression);
  double computeAnswer();
private:
  void clear(Node* p);
  void inOrderTraversal(Node* p) const;
  void postOrderTraversal(Node* p) const;
  bool isDigit(char c) const;
  bool isOperator(char c) const;
  void processExpression(Node* p);
  void computeAnswer(Node* ptr);
  Node* root{ nullptr };
  string expression;
  unsigned int position{ 0 };
  stack<double> mathStack;
};