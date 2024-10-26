#include "Tokenizer.h"
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

vector<Token> Tokenizer::tokenize(const string& line) {
    vector<Token> tokens;
    istringstream stream(line);
    string word;

    while (stream >> word) {
        if (word == "//") {
            tokens.emplace_back(Token::COMMENT, line.substr(stream.tellg()));
            break;
        } else if (isKeyword(word)) {
            tokens.emplace_back(Token::KEYWORD, word);
        } else if (word.front() == '"' && word.back() == '"') {
            tokens.emplace_back(Token::STRING, word);
        } else if (isNumber(word.front())) {
            tokens.emplace_back(Token::NUMBER, word);
        } else if (isSymbol(word.front())) {
            tokens.emplace_back(Token::SYMBOL, word);
        } else {
            tokens.emplace_back(Token::UNKNOWN, word);
        }
    }

    return tokens;
}

bool Tokenizer::isNumber(char c) const {
    return isdigit(c);
}

bool Tokenizer::isSymbol(char c) const {
    return ispunct(c) && c != '"';
}

bool Tokenizer::isKeyword(const string& str) const {
    static const vector<string> keywords = {"solve", "print", "println"};
    return find(keywords.begin(), keywords.end(), str) != keywords.end();
}