#pragma once

#include <string>

using namespace std;

class Token {
public:
    enum TokenType {
        NUMBER,
        SYMBOL,
        KEYWORD,
        STRING,
        COMMENT,
        UNKNOWN
    };

    Token(TokenType type, const string& contents);

    TokenType getType() const;
    string getContents() const;

private:
    TokenType tokenType;
    string tokenContents;
};
