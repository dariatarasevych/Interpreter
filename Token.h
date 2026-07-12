#ifndef ASSIGNMENT_5_TOKEN_H
#define ASSIGNMENT_5_TOKEN_H

#include <iostream>

enum class TokensType{
    Number,
    Operator,
    LeftParen,
    RightParen,
    Comma,
    Dot,
    Assign,
    FunctionName,
    KeywordVar,
    Variable
};

struct Token {
    TokensType type;
    std::string value;
};

#endif //ASSIGNMENT_5_TOKEN_H
