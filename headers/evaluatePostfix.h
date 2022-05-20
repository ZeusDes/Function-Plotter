/**
 * @file evaluatePostfix.h
 * @author Muhammad Ahmad (muhammadathabet@gmail.com)
 * @brief This File contains the function to evaluate the postfix expression
 * @version 1.0.0-beta
 * @date 2022-05-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef EVALUATEPOSTFIX_H
#define EVALUATEPOSTFIX_H
#include "validateInput.h"
#include <QObject>

/**
 * @brief Convert valid expression into vactor of elements that can be processed by evaluate functions
 * 
 * @param expr The expression to be converted to postfix notation
 * @return QVector<QString> 
 */
QVector<QString> infix2Postfix(QString expr){
    QVector<QString> postfix;
    QStack<QChar> op;
    QMap<QChar, int> order;
    const int STR_SIZE = 1;
    order['('] = order[')'] = 5; // Order of brackets
    order['!'] = 4;                                        // Order of unary negative sign
    order['^'] = 3;                                        // Order of exponent
    order['*'] = order['/'] = 2;                           // Order of  Multiplication and Division
    order['+'] = order['-'] = 1;                           // Order of Addition and Subtraction
    QString acc;
    for(int i = 0; i < expr.size(); i++){
        acc = "";
        if(expr[i] == '(') op.push(expr[i]);               // push '(' into the stack
        else if(expr[i] == ')'){                           // if char is ')' pop all operators before '('
            while(op.top() != '('){
                postfix.push_back(QString(STR_SIZE, op.top()));
                op.pop();
            }
            op.pop();
        }
        else if(isAlNum(expr[i]) || expr[i] == '.'){       // if char is alphanumeric or decimal point then continue reading the whole number
            while(i < expr.size() && (isAlNum(expr[i]) || expr[i] == '.')){
                acc += expr[i++];
            }
            i--;
            postfix.push_back(acc);
        }
        else if(expr[i] == '-' && (i == 0 || !isAlNum(expr[i - 1]))){// if char is unary negative then pop all higher order elements from the stack and push '!' instead
            while(!op.empty() && (order[op.top()] >= order['!'] && op.top() != '(')){
                postfix.push_back(QString(STR_SIZE, op.top()));
                op.pop();
            }
            op.push('!');
        }
        else if(isOperator(expr[i])){                      // if the char is an operator then check order then psh into stack
            while(!op.empty() && (order[op.top()] >= order[expr[i]]) && op.top() != '('){
                if(expr[i] == '^' && op.top() == '^') break;
                postfix.push_back(QString(STR_SIZE, op.top()));
                op.pop();
            }
            op.push(expr[i]);
        }
    }

    // if the stack is not empty yet, then pop all its elements into postfix vector
    while(!op.empty()){
        postfix.push_back(QString(STR_SIZE, op.top()));
        op.pop();
    }
    return postfix;
}

/**
 * @brief Evaluate expression according to a given value
 * 
 * @param pF The postfix notation of the expression
 * @param val The value of x in the expression
 * @return double 
 */ 
double evaluate(QVector<QString> pF, double val){
    QStack<double> operands;
    double A, B;
    for(int j = 0; j < pF.size(); j++)            // putting the value instead of x in vector
        if(pF[j] == "x") pF[j] = QString::number(val);

    for(int i = 0; i < pF.size(); i++){
        if(isDigit(pF[i][pF[i].size()-1])){       // if current element is a number, then push it into the stack
            operands.push(pF[i].toDouble());
        }
        else if(pF[i] == "!"){                    // if the operator is unary negative, then it affects only the top operand
            A = -1 * operands.top();
            operands.pop();
            operands.push(A);
        }
        else if(isOperator(pF[i][pF[i].size()-1])){ // if element is operator, then push the last two operand, execute the operation and then push the result into the stack again
            B = operands.top();
            operands.pop();
            A = operands.top();
            operands.pop();
            if(pF[i] == "+") A += B, operands.push(A);
            else if(pF[i] == "-") A -= B, operands.push(A);
            else if(pF[i] == "*") A *= B, operands.push(A);
            else if(pF[i] == "/"){
                if(B == 0) return 0;
                A /= B, operands.push(A);
            }
            else{
                if(A == 0 && B == 0) return 0;
                A = pow(A, B), operands.push(A);
            }
        }
    }
    return operands.top();
}
#endif // EVALUATEPOSTFIX_H
