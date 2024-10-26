#include "Interpreter.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Interpreter::Interpreter(ErrorHandler& errorHandler) : errorHandler(errorHandler) {}

void Interpreter::interpret(const map<int, vector<Token>>& tokens) {
    for (const auto& [lineNumber, lineTokens] : tokens) {
        if (lineTokens.empty()) continue;

        const Token& firstToken = lineTokens[0];
        if (firstToken.getType() == Token::KEYWORD) {
            if (firstToken.getContents() == "solve") {
                processSolve(lineTokens);
            } else if (firstToken.getContents() == "print" || firstToken.getContents() == "println") {
                processPrint(lineTokens);
            }
        } else if (firstToken.getType() == Token::UNKNOWN && lineTokens.size() > 1 && lineTokens[1].getContents() == "=") {
            processAssignment(lineTokens);
        } else {
            errorHandler.errorWithLine("Unknown statement", lineNumber);
        }
    }
}

void Interpreter::processSolve(const vector<Token>& tokens) {
    if (tokens.size() != 2 || tokens[1].getType() != Token::UNKNOWN) {
        errorHandler.error("Invalid solve statement");
        return;
    }

    const string& variable = tokens[1].getContents();
    if (variables.find(variable) == variables.end()) {
        errorHandler.error("Variable " + variable + " not defined");
        return;
    }

    cout << variable << " = " << variables[variable] << endl;
}

void Interpreter::processAssignment(const vector<Token>& tokens) {
    if (tokens.size() < 3 || tokens[1].getContents() != "=") {
        errorHandler.error("Invalid assignment statement");
        return;
    }

    const string& variable = tokens[0].getContents();
    size_t index = 2;
    double value = evaluateExpression(tokens, index);
    variables[variable] = value;
}

void Interpreter::processPrint(const vector<Token>& tokens) {
    if (tokens.size() != 2 || tokens[1].getType() != Token::STRING) {
        errorHandler.error("Invalid print statement");
        return;
    }

    const string& text = tokens[1].getContents();
    cout << text.substr(1, text.size() - 2) << endl; // Remove the double quotes
}

double Interpreter::evaluateExpression(const vector<Token>& tokens, size_t& index) {
    double result = 0;
    char operation = '+';

    while (index < tokens.size()) {
        const Token& token = tokens[index];
        double value;

        if (token.getType() == Token::NUMBER) {
            value = stod(token.getContents());
        } else if (token.getType() == Token::UNKNOWN) {
            if (variables.find(token.getContents()) == variables.end()) {
                errorHandler.error("Variable " + token.getContents() + " not defined");
                throw runtime_error("Undefined variable");
            }
            value = variables[token.getContents()];
        } else if (token.getType() == Token::SYMBOL) {
            operation = token.getContents()[0];
            index++;
            continue;
        } else {
            errorHandler.error("Invalid token in expression");
            throw runtime_error("Invalid token");
        }

        switch (operation) {
            case '+': result += value; break;
            case '-': result -= value; break;
            case '*': result *= value; break;
            case '/': result /= value; break;
            case '%': result = static_cast<int>(result) % static_cast<int>(value); break;
            default:
                errorHandler.error("Unknown operation " + string(1, operation));
                throw runtime_error("Unknown operation");
        }

        index++;
    }

    return result;
}