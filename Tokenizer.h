#pragma once

#include "Token.h"
#include <string>
#include <vector>

using namespace std;

class Tokenizer {
public:
    vector<Token> tokenize(const string& line);

private:
    bool isNumber(char c) const;
    bool isSymbol(char c) const;
    bool isKeyword(const string& str) const;
};