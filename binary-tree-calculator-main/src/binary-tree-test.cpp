#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "TreeParser.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

// trim from start (in place)
static inline void ltrim(std::string& s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch);}));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
  rtrim(s);
  ltrim(s);
}

//This helps with testing, comment it in when ready, but do not modify the code.
bool checkTest(int testNum, int& correct, string whatItShouldBe, string whatItIs) {
  trim(whatItIs);
  trim(whatItShouldBe);
  if (whatItShouldBe == whatItIs) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    if (whatItShouldBe == "") {
      cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been blank. " << endl;
    }
    else {
      cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    }
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

//This helps with testing, comment it in when ready, but do not modify the code.
bool checkTest(int testNum, int& correct, double whatItShouldBe, double whatItIs) {

  if (whatItShouldBe == whatItIs) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

bool checkTest(int testNum, int& correct, double whatItShouldBe, double whatItIs, double fudge) {

  if ((whatItShouldBe <= whatItIs && whatItShouldBe > whatItIs - fudge) || (whatItShouldBe >= whatItIs && whatItShouldBe < whatItIs + fudge)) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been close to " << whatItShouldBe << endl;
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

int test_SimpleExpressions(){

  cout << "--------test_SimpleExpressions Tests--------" << endl;

  int testNum  = 1;
  int correct = 0;
  TreeParser tp;
  stringstream buffer;

  
  string expression = "(4+7)";
  tp.processExpression(expression);
  
  std::streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  std::string inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "4 + 7 ", inOrderText); // 1

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  std::string postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "4 7 +", postOrderText); // 2

  double answer = tp.computeAnswer();
  checkTest(testNum++, correct, 11, answer); // 3

  
  expression = "(7-4)";
  tp.processExpression(expression);

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "7 - 4 ", inOrderText); // 4

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "7 4 - ", postOrderText); // 5

  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 3, answer); // 6

  
  expression = "(9*5)";
  tp.processExpression(expression);

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "9 * 5 ", inOrderText); // 7

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "9 5 * ", postOrderText); // 8

  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 45, answer); // 9

  
  expression = "(4^3)";
  tp.processExpression(expression);

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "4 ^ 3 ", inOrderText); // 10

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "4 3 ^ ", postOrderText); // 11

  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 64, answer); // 12

  return (testNum - 1 >= correct && correct > 0);
}


int test_TwoOrMoreOperators() {

  cout << "--------test_TwoOrMoreOperators Tests--------" << endl;

  int testNum = 1;
  int correct = 0;
  TreeParser tp;
  stringstream buffer;

  
  string expression = "((2-5)-5)";
  tp.processExpression(expression);
  
  std::streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  std::string inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "2 - 5 - 5 ", inOrderText); // 1

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  std::string postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "2 5 - 5 - ", postOrderText); // 2

  double answer = tp.computeAnswer();
  checkTest(testNum++, correct, -8, answer); // 3
  
  
  expression = "(5 * (6/2))";
  tp.processExpression(expression);

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "5 * 6 / 2 ", inOrderText); // 4

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "5 6 2 / * ", postOrderText); // 5

  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 15, answer); // 6

  
  expression = "((6 / 3) + (8 * 2))";
  tp.processExpression(expression);
  
  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "6 / 3 + 8 * 2 ", inOrderText); // 7

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "6 3 / 8 2 * + ", postOrderText); // 8

  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 18, answer); // 9

  return (testNum - 1 >= correct && correct > 0);
}

int test_MultiDigitNumbers() {

  cout << "--------test_MultiDigitNumbers Tests--------" << endl;

  int testNum = 1;
  int correct = 0;
  TreeParser tp;
  stringstream buffer;
  
  
  string expression = "(543+321)";
  tp.processExpression(expression);

  std::streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  std::string inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "543 + 321 ", inOrderText); // 1

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  std::string postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "543 321 + ", postOrderText); // 2

  double answer = tp.computeAnswer();
  checkTest(testNum++, correct, 864, answer); // 3

  
  expression = "(7.5-3.25)";
  tp.processExpression(expression);

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "7.5 - 3.25 ", inOrderText); // 4

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "7.5 3.25 - ", postOrderText); // 5

  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 4.25, answer); // 2

  return (testNum - 1 >= correct && correct > 0);
}

int test_BigExpressions() {


  cout << "--------test_BigExpressions Tests--------" << endl;

  int testNum = 1;
  int correct = 0;
  TreeParser tp;
  stringstream buffer;
  
  
  string expression = "(5 + (34 - (7 * (32 / (16 * 0.5)))))";
  tp.processExpression(expression);

  std::streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  std::string inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "5 + 34 - 7 * 32 / 16 * 0.5 ", inOrderText); // 1

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  std::string postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "5 34 7 32 16 0.5 * / * - + ", postOrderText); // 2

  double answer = tp.computeAnswer();
  checkTest(testNum++, correct, 11, answer); // 3
  std::cout.rdbuf(coutbuf);


  expression = "((5*(3+2))+(7*(4+6)))";
  tp.processExpression(expression);

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  inOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "5 * 3 + 2 + 7 * 4 + 6 ", inOrderText); // 4

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "5 3 2 + * 7 4 6 + * + ", postOrderText); // 5

  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 95, answer); // 6
  

  expression = "(((2+3)*4)+(7+(8/2)))";
  tp.processExpression(expression);

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  inOrderText = buffer.str();
  buffer.str(std::string());;
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "2 + 3 * 4 + 7 + 8 / 2 ", inOrderText); // 7

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "2 3 + 4 * 7 8 2 / + + ", postOrderText); // 8

  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 31, answer); // 9


  expression = "(((((3+12)-7)*120)/(2+3))^3)";
  tp.processExpression(expression);
  
  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  inOrderText = buffer.str();
  buffer.str(std::string());;
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "3 + 12 - 7 * 120 / 2 + 3 ^ 3 ", inOrderText); // 10

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "3 12 + 7 - 120 * 2 3 + / 3 ^ ", postOrderText); // 11
  
  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 7077888, answer); // 12


  expression = "(((((9 + (2 * (110 - (30 / 2)))) * 8) + 1000) / 2) + (((3 ^ 4) + 1) / 2))";
  tp.processExpression(expression);

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.inOrderTraversal();
  inOrderText = buffer.str();
  buffer.str(std::string());;
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "9 + 2 * 110 - 30 / 2 * 8 + 1000 / 2 + 3 ^ 4 + 1 / 2 ", inOrderText); // 13

  coutbuf = cout.rdbuf(buffer.rdbuf());
  tp.postOrderTraversal();
  postOrderText = buffer.str();
  buffer.str(std::string());
  std::cout.rdbuf(coutbuf);
  checkTest(testNum++, correct, "9 2 110 30 2 / - * + 8 * 1000 + 2 / 3 4 ^ 1 + 2 / + ", postOrderText); // 14

  answer = tp.computeAnswer();
  checkTest(testNum++, correct, 1337, answer); // 15
  return (testNum - 1 >= correct && correct > 0);

}

int main(int argc, char** argv) {


  int test = 0;
  int count = 0;

  if (argc > 1) {
    test = std::stoi(argv[1]);
  }
  switch (test) {
  case 0:
    if (test_SimpleExpressions()) count++;
    if (test_TwoOrMoreOperators()) count++;
    if (test_MultiDigitNumbers()) count++;
    if (test_BigExpressions()) count++;

    cout << "----------------" << endl;
    cout << "Passed " << count << " out of 4 group tests" << endl;
    cout << "--End of tests--" << endl;
    return count != 4;
  case 1:
    return !test_SimpleExpressions();
  case 2:
    return !test_TwoOrMoreOperators();
  case 3:
    return !test_MultiDigitNumbers();
  case 4:
    return !test_BigExpressions();
  }

  return 0;
}
