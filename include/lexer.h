#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum TokenType {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_REPLACE,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_EOF
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string& input);

#endif