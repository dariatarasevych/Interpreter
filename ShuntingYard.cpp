#include "ShuntingYard.h"
#include <vector>

int ShuntingYard::getPrecedence(const std::string& op) {
    if (op == "+" || op == "-") {
        return 1;
    } else if (op == "/" || op == "*") {
        return 2;
    } else {
        return 0;
    }
}

std::vector<Token> ShuntingYard::parseToRPN(const std::vector<Token> &tokens) {
    std::vector<Token> outputQueue;
    std::stack<Token> operatorStack;

    for (const auto& token : tokens) {
        if (token.type == TokensType::Number || token.type == TokensType::Variable) {
            outputQueue.push_back(token);
        } else if (token.type == TokensType::FunctionName) {
            operatorStack.push(token);
        } else if (token.type == TokensType::Comma) {
            while (!operatorStack.empty() && operatorStack.top().type != TokensType::LeftParen) {
                outputQueue.push_back(operatorStack.top());
                operatorStack.pop();
            }
        } else if (token.type == TokensType::Operator) {
            while (!operatorStack.empty() && getPrecedence(operatorStack.top().value) >= getPrecedence(token.value)) {
                outputQueue.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        } else if (token.type == TokensType::LeftParen) {
            operatorStack.push(token);
        } else if (token.type == TokensType::RightParen) {
            while (!operatorStack.empty() && operatorStack.top().type != TokensType::LeftParen) {
                outputQueue.push_back(operatorStack.top());
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top().type == TokensType::LeftParen) {
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top().type == TokensType::FunctionName) {
                outputQueue.push_back(operatorStack.top());
                operatorStack.pop();
            }
        }
    }
    while (!operatorStack.empty()) {
        outputQueue.push_back(operatorStack.top());
        operatorStack.pop();
    }
    return outputQueue;
}
