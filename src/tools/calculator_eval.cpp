// src/tools/calculator_eval.cpp — YOU IMPLEMENT (spec §4.6).
//
// calc_evaluate: evaluate a well-formed token list with two stacks
// (one for numbers, one for operators and '('). See spec §4.6 and the
// worked trace in Appendix C. std::stack or std::vector are both fine.

#include "tools/calculator.h"
#include <stack> 
using Kind = CalcToken::Kind; 

static int precedence(Kind k) {
    switch(k){
        case Kind::Times:
        case Kind::Divide: return 2; 
        case Kind::Plus: 
        case Kind::Minus: return 1; 
        default: return 0; 
    }
}

static bool is_operator(Kind k) {
    return k == Kind::Plus || k==Kind::Minus || k==Kind::Times || k==Kind::Divide;
}

static bool apply_top(std::stack<double>& values, std::stack<Kind>& ops, std::string* error){
    if (ops.empty() || values.size() < 2) {
        *error = "Malformed";
        return false; 
    }
    Kind op = ops.top();
    ops.pop();

    double right = values.top();
    values.pop();
    double left = values.top();
    values.pop();

    double result = 0.0; 
    switch(op) {
        case Kind::Plus: result = left + right; break;
        case Kind::Minus: result = left - right; break; 
        case Kind::Times: result = left * right; break;
        case Kind::Divide: if (right ==0.0) {
            *error = "Cant divide by zero";
            return false; 
        }
        result = left / right; 
        break; 
        default: *error = "unknown token on stack";
        return false; 
    }
    values.push(result);
    return true; 
}

bool calc_evaluate(const std::vector<CalcToken>& tokens, double* out, std::string* error) {
    std::stack<double> values; 
    std::stack<Kind> ops; 
}
