#include "Token.h"
#include <string>

using namespace std;

Token::Token(TokenType type, const string& contents) : tokenType(type), tokenContents(contents) {}

Token::TokenType Token::getType() const {
    return tokenType;
}

std::string Token::getContents() const {
    return tokenContents;
}