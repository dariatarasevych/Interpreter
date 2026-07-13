#include <iostream>
#include "Tokenization.h"
#include "Environment.h"
#include "ShuntingYard.h"
#include "Evaluator.h"

int main() {
    Environment environment;
    ShuntingYard shunting_yard;
    Evaluator evaluator;
    Tokenization tokenization;

    std::string input;
    std::cout << "> ";

    while (std::getline(std::cin, input)) {
        if (input == "exit" || input == "quit") {
            break;
        }

        if (input.empty()) {
            std::cout << "> ";
            continue;
        }

        try {
            std::vector<Token> tokens = tokenization.tokenize(input);
            if (tokens.empty()) {
                std::cout << "> ";
                continue;
            }

            if (tokens[0].type == TokensType::KeywordVar) {
                if (tokens.size() < 4 || tokens[1].type != TokensType::Variable || tokens[2].type != TokensType::Assign) {
                    throw std::runtime_error("Syntax error in variable declaration.");
                }

                std::string varName = tokens[1].value;

                std::vector<Token> expressionTokens(tokens.begin() + 3, tokens.end());

                auto rpn = shunting_yard.parseToRPN(expressionTokens);
                double value = evaluator.evaluate(rpn, environment);

                environment.setVariable(varName, value);
            } else if (tokens[0].type == TokensType::KeywordDef) {
                if (tokens.size() < 7 || tokens[1].type != TokensType::Variable || tokens[2].type != TokensType::LeftParen) {
                    throw std::runtime_error("Syntax error in function declaration.");
                }

                std::string funcName = tokens[1].value;
                std::vector<std::string> parameters;

                int i = 3;
                while (i < tokens.size() && tokens[i].type != TokensType::RightParen) {
                    if (tokens[i].type == TokensType::Variable) {
                        parameters.push_back(tokens[i].value);
                    }
                    i++;
                }

                while (i < tokens.size() && tokens[i].type != TokensType::LeftCurly) {
                    i++;
                }

                if (i >= tokens.size()) {
                    throw std::runtime_error("Missing '{'!");
                }
                i++;

                std::vector<Token> functionExpression;
                while (i < tokens.size() && tokens[i].type != TokensType::RightCurly) {
                    functionExpression.push_back(tokens[i]);
                    i++;
                }

                if (i >= tokens.size()) {
                    throw std::runtime_error("Missing '}'!");
                }

                auto rnpFunction = shunting_yard.parseToRPN(functionExpression);
                environment.setFunction(FunctionSymbol{funcName, parameters, rnpFunction});

            } else {
                auto rpn = shunting_yard.parseToRPN(tokens);
                double valueResult = evaluator.evaluate(rpn, environment);
                std::cout << valueResult << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        std::cout << "> ";
    }
    return 0;
}