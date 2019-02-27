//
//  ExpressionManager.h
//  Lab 2
//
//  Created by Cam on 10/10/18.
//  Copyright © 2018 Cameron Brown. All rights reserved.
//

#ifndef ExpressionManager_h
#define ExpressionManager_h

#include <stdio.h>
#include <string>
#include "ExpressionManagerInterface.h"

using namespace std;

class ExpressionManager : public ExpressionManagerInterface {
public:
    void trim(string& s);
    bool parenChecker(string first, string second);
    int precedence(string op);
    bool isOpening(string paren);
    bool isClosing(string paren);
    bool isInvalid(string exp);
    bool isParentheses(string s);
    bool isOperator(string s);
    bool isNumber(const string& s);
    bool isBalanced(string expression);
    string postfixToInfix(string postfixExpression);
    string postfixEvaluate(string postfixExpression);
    string infixToPostfix(string infixExpression);
    string topItem;
    stack <string> mystack;
protected:
};

#endif /* ExpressionManager_h */
