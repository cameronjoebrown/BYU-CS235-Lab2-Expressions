//
//  ExpressionManager.cpp
//  Lab 2
//
//  Created by Cam on 10/10/18.
//  Copyright © 2018 Cameron Brown. All rights reserved.
//

#include "ExpressionManager.h"
#include <cctype>
#include <sstream>
#include <vector>

using namespace std;

bool ExpressionManager::parenChecker(string first, string second){
    if(first == "(" && second == ")"){
        return true;
    }
    else if(first == "{" && second == "}")
    {
        return true;}
    else if(first == "[" && second == "]")
    {
        return true;
    }
    else{
        return false;
    }
}

void ExpressionManager::trim(string& s)
{
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);
    
    p = s.find_last_not_of(" \t");
    if (string::npos != p)
        s.erase(p+1);
}

int ExpressionManager::precedence(string op){
    if (op == "+" || op == "-"){
        return 1;
    }
    else if (op == "*" || op == "/" || op == "%"){
        return 2;
    }
    else if (op == ")" || op == "}" || op == "]"){
        return 3;
    }
    else{
        return 0;
    }
}

bool ExpressionManager::isOpening(string paren){
    
    if (paren == "(" || paren == "[" || paren == "{"){
        return true;
    }
    else{
        return false;
    }
}

bool ExpressionManager::isClosing(string paren){
    if (paren == ")" || paren == "]" || paren == "}"){
        return true;
    }
    else{
        return false;
    }
}


bool ExpressionManager::isParentheses(string s){
    if (s == "(" || s == "{" || s == "[" || s == ")" || s == "}" || s == "]"){
        return true;
    }
    else{
        return false;
    }
}

bool ExpressionManager::isOperator(string s){
    string operators = "+-*/%";
    return operators.find(s) != string::npos;
}

bool ExpressionManager::isNumber(const string& s)
{
    return(strspn( s.c_str(), "0123456789") == s.size());
}

bool ExpressionManager::isInvalid(string exp){
    stringstream s(exp);
    string current;
    int numCount = 0;
    int opCount = 0;
    int parenCount = 0;
    
    while(s >> current){
        if (isNumber(current)){
            numCount++;
        }
        else if(isOperator(current)){
            opCount++;
        }
        else if(isParentheses(current)){
            parenCount++;
        }
    }
    if ((numCount - opCount) == 1){
        return false;
    }
    else{
        return true;
    }
}


bool ExpressionManager::isBalanced(string expression) {
    stack<string> parenthesesStack;
    stringstream stream(expression);
    string current;
    while(stream >> current) {
        if(current == "(" || current == "[" || current == "{"){
            parenthesesStack.push(current);
        }
        else if(current == ")" || current == "]" || current == "}"){
            if(parenthesesStack.empty()){
                return false;
                break;
            }
            else {
                string topItem = parenthesesStack.top();
                if(topItem == "(" && current == ")"){
                    parenthesesStack.pop();
                }
                else if(topItem == "{" && current == "}"){
                    parenthesesStack.pop();
                }
                else if(topItem == "[" && current == "]"){
                    parenthesesStack.pop();
                }
                else {
                    return false;
                    break;
                }
            }
           
        }
    }
    if (parenthesesStack.empty() == false) {
        return false;
    }
    else {
        return true;
    }
}

string ExpressionManager::postfixToInfix(string postfixExpression) {
    stack <string> mystack;
    stringstream ss(postfixExpression);
    string curr;
    string right;
    string left;
    string newExp;
    
    if (!isBalanced(postfixExpression)){
        return "invalid";
    }
    
    if (isInvalid(postfixExpression)){
        return "invalid";
    }
    
    while (ss >> curr){
        if (curr == "NULL"){
            return "invalid";
        }
        if (mystack.empty()){
        }
        if (isNumber(curr)){
            mystack.push(curr);
        }
        else if (isOperator(curr)){
            if (mystack.empty()){
                // if it's empty, go ahead and push onto the stack
                return "invalid";
            }
            else{
                right = mystack.top();
                mystack.pop();
                if (mystack.empty()){
                    return "invalid";
                }
                left = mystack.top();
                mystack.pop();
                newExp = "( " + left + " " + curr + " " + right + " " + ")";
                mystack.push(newExp);
            }
        }else{
            return "invalid";
        }
    }
    if (mystack.empty()){
        return "invalid";
    }
    newExp = mystack.top();
    return newExp;
}

string ExpressionManager::postfixEvaluate(string postfixExpression){
    stack<string> postfixStack;
    stringstream inSS(postfixExpression);
    string current;
    string right;
    string left;
    int answer;
    while (!postfixStack.empty()){
        postfixStack.pop();
    }
    if (isInvalid(postfixExpression)){
        return "invalid";
    }

    while(inSS >> current){
        if (isNumber(current)){
            postfixStack.push(current);
        }
        else if(isOperator(current)){
            if (postfixStack.empty()){
                return "invalid";
            }
            //eval_op(curr);
            right = postfixStack.top();
            postfixStack.pop();
            if (postfixStack.empty()){
                return "invalid";
            }
            left = postfixStack.top();
            postfixStack.pop();
            
            int R = atoi(right.c_str());
            int L = atoi(left.c_str());
            
            if (current == "+"){
                answer = L + R;
            }
            if (current == "-"){
                answer = L - R;
            }
            if (current == "*"){
                answer = L * R;
            }
            if (current == "%"){
                answer = L % R;
            }
            if (current == "/"){
                if(R == 0 ){
                    answer = 0;
                    return "invalid";
                }
                else{
                    answer = L / R;
                }
            }
            stringstream os;
            os << answer;
            // put on stack
            postfixStack.push(os.str());
            //return os.str();
        }
        
        else{
            return "invalid";
        }
    }
    string finalExp = postfixStack.top();
    return finalExp;
}

string ExpressionManager::infixToPostfix(string infixExpression){
    stack <string> mystack;
    stringstream ss(infixExpression);
    stringstream os;
    string curr;
    
    if (!isBalanced(infixExpression)){
        return "invalid";
    }
    
    if (isInvalid(infixExpression)){
        return "invalid";
    }
    
    while (ss >> curr){
        if (isNumber(curr)){
            os << curr << " ";
        }
        // if it's an operator
        else if (isOperator(curr)){
            if (mystack.empty()){
                // if it's empty, go ahead and push onto the stack
                mystack.push(curr);
            }
            // if the top is a paren, go ahead and push onto the stack
            else if (isParentheses(mystack.top())){
                mystack.push(curr);
            }
            // if the operator has higher precedence than the stack's top, push onto stack
            else if (precedence(curr) > precedence(mystack.top())){
                mystack.push(curr);
            }
            else {
                while (!mystack.empty() && (precedence(curr)) <= precedence(mystack.top())) {
                    topItem = mystack.top();
                    os << topItem << " ";
                    mystack.pop();
                }
                mystack.push(curr);
            }
        }
        // if it's a paren
        else if (isOpening(curr)){
            mystack.push(curr);
        }
        else if (isClosing(curr)){
            while (!parenChecker(mystack.top(), curr)){
                topItem = mystack.top();
                os << topItem << " ";
                mystack.pop();
            }
            mystack.pop();
        }
        // if it's not a paren, operator, or a number
        else{
            return "invalid";
        }
        
    }
    /*    if (isInvalid(os.str())){
     return "invalid";
     }*/
    while (!mystack.empty()){
        topItem = mystack.top();
        os << topItem << " ";
        mystack.pop();
    }
    string output;
    output = os.str();
    trim(output);
    return output;
}


