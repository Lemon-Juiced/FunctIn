#pragma once

#include "Token.h"
#include "ErrorHandler.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

class Interpreter {
public:
    Interpreter(ErrorHandler& errorHandler);
    void interpret(const map<int, vector<Token>>& tokens);

private:
    ErrorHandler& errorHandler;
    map<string, double> variables;

    void processSolve(const vector<Token>& tokens);
    void processAssignment(const vector<Token>& tokens);
    void processPrint(const vector<Token>& tokens);
    double evaluateExpression(const vector<Token>& tokens, size_t& index);
};