/**
 * @file validateInput.h
 * @author Muhammad Ahmad (muhammadathabet@gmail.com)
 * @brief This file contains the function prototypes for the validateInput.cpp file
 * @version 1.0.0-beta
 * @date 2022-05-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef VALIDATEINPUT_H
#define VALIDATEINPUT_H
#include<QString>
#include<QMap>
#include<QStack>
#include<QVector>
#include<qmath.h>
#include<QChar>

/**
 * @brief Checking if the character is an supported operation or not.
 * 
 * @param c Character to be checked.
 * @return true 
 * @return false 
 */
inline bool isOperator(QChar c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return 1;
    return 0;
}

/**
 * @brief Checking if the character is Digit or not.
 * 
 * @param c Character to be checked. 
 * @return true 
 * @return false 
 */
bool isDigit(QChar c){
    if(c >= '0' && c <= '9') return 1;
    return 0;
}

/**
 * @brief Checking if the character belongs to alphabet or not.
 * 
 * @param c Character to be checked. 
 * @return true 
 * @return false 
 */
bool isAlpha(QChar c){
    if(c >= 'a' && c <= 'z') return 1;
    else if(c >= 'A' && c <= 'Z') return 1;
    return 0;
}

/**
 * @brief Checking if the character is Alphanumeric
 * 
 * @param c Character to be checked.
 * @return true 
 * @return false 
 */
bool isAlNum(QChar c){
    if(isDigit(c) || isAlpha(c)) return 1;
    return 0;
}

/**
 * @brief Checking the validity of an exprission
 * 
 * @param expr The Math expression to be checked.
 * @return QVector<QString> 
 */
QVector<QString> isValid(QString expr){
    int length = expr.size();
    bool flag = false; // This flag to check that no more than on dot exists in single decimal number
    QVector<QString> errors; // Vector to store Errors found

    // Case 1: Expression is empty
    if(length == 0){
         errors.push_back("Your Expression is empty.");
         return errors;
    }

    // Case 2: Expression contains single & not alphanumeric character
    if(length == 1 && !isDigit(expr[length-1]) && expr[length-1] != 'x'){
         errors.push_back("Please insert one operand at least.");
         return errors;
    }

    // Case 3: Checking the start and the end of an Expression
    if(!isDigit(expr[0]) && expr[0] != 'x' && expr[0] != '-' && expr[0] != '('){
         errors.push_back("Inavlid element at the start of expression.");
    }
    if(!isDigit(expr[length-1]) && expr[length-1] != 'x' && expr[length-1] != ')' ){
          errors.push_back("Inavlid element at the end of expression.");
          return errors;
    }

    // Case 4: Checking that Parentheses are balanced 
    QStack<QChar>brackets;
    for (int i = 0; i < length; i++)
    {
          if(expr[i] == '('){
              brackets.push(expr[i]);
          }
          else if(expr[i] == ')'){
              if(brackets.empty()) errors.push_back("')' not opened.");
              else brackets.pop();
          }
    }
    if (!brackets.empty()) errors.push_back("'(' not closed.");

    // Case 5: Checking the validity of the upfront character
    for (int i = 0; i < length-1; i++)
    {
        if(isOperator(expr[i])) flag = 0;
        if(expr[i] != '.' && expr[i] != 'x' && expr[i] != '+' && expr[i] != '-' && expr[i] != '*' && expr[i] != '/' && expr[i] != '^' && expr[i] != '(' && expr[i] != ')' && !isDigit(expr[i])){errors.push_back("Inavlid character '" + QString(1 , expr[i]) + QString(1 , '\'') + " at index " + QString::number(i) + QString(1 , '.'));}
        else if(expr[i] == '/' && expr[i + 1] == '0') errors.push_back("Cannot Divide by Zero.");
        else if(expr[i] == '^' && expr[i - 1] == '0' && expr[i + 1] == '0') errors.push_back("Invalid operation \"0^0\".");
        else if((expr[i] == '+' ||  expr[i] == '-') && (isDigit(expr[i+1]) || expr[i+1] == 'x' || expr[i+1] == '(')){flag = 0; continue;}
        else if((expr[i] == '*' ||  expr[i] == '/' || expr[i] == '^')  && (isDigit(expr[i+1]) || expr[i+1] == 'x' || expr[i+1] == '(' || expr[i+1] == '-')){flag = 0; continue;}
        else if(expr[i] == '(' && (isDigit(expr[i+1]) || expr[i+1] == 'x' || expr[i+1] == '(' || expr[i+1] == '-')){flag = 0; continue;}
        else if(expr[i] == ')' && (expr[i+1] == '+' || expr[i+1] == '-' || expr[i+1] == '*' || expr[i+1] == '/' || expr[i+1] == '^' || expr[i+1] == ')')){flag = 0; continue;}
        else if(isDigit(expr[i]) && (expr[i+1] == '.' || isDigit(expr[i+1]) || expr[i+1] == '+' || expr[i+1] == '-' || expr[i+1] == '*' || expr[i+1] == '/' || expr[i+1] == '^' || expr[i+1] == ')')) continue;
        else if(expr[i] == 'x' && (expr[i+1] == '+' || expr[i+1] == '-' || expr[i+1] == '*' || expr[i+1] == '/' || expr[i+1] == '^' || expr[i+1] == ')' )) continue;
        else if(expr[i] == '.' && !flag && isDigit(expr[i+1])){flag = 1; continue;}
        else {errors.push_back("Inavlid character '" + QString(1 , expr[i + 1]) + QString(1 , '\'') + " at index " + QString::number(i + 1) + QString(1 , '.')); i++;}

    }
    return errors;
}

/**
 * @brief Make input String Spaces-free
 * 
 * @param original The Original String
 * @return QString The Spaces-free String
 */

QString input(QString original){
    QString cleaned = "";
    for(int i = 0; i < original.size(); i++){
        if(original[i] != ' ') cleaned += original[i];
    }
    return cleaned;
}

#endif // VALIDATEINPUT_H
