#ifndef ASSIGNMENT_5_SHUNTINGYARD_H
#define ASSIGNMENT_5_SHUNTINGYARD_H
#include <string>
#include "Token.h"

class ShuntingYard {
private:
    int getPrecedence(const std::string& op);
public:
    std::vector<Token> parseToRPN(const std::vector<Token>& tokens);
};

#endif //ASSIGNMENT_5_SHUNTINGYARD_H
