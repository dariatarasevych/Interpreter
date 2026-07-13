#include <vector>
#include <string>
#include <cctype>
#include "Tokenization.h"

std::vector<Token> Tokenization::tokenize(const std::string& input) {
    std::vector<Token> tokens;

    for (int i =0; i < input.length(); i++) {
        char c = input[i];

        if (std::isspace(c)) {continue;}

        bool isUnaryMinus = (c == '-' && (tokens.empty() || tokens.back().type == TokensType::LeftParen || tokens.back().type == TokensType::RightParen || tokens.back().type == TokensType::Operator));


        // щоб зібралося ціле число, а не кожна цифра окремо
        if (std::isdigit(c) || isUnaryMinus) {
            std::string numbersStr ="";

            if (c == '-') {
                numbersStr += input[i];
                i++;
            }

            while (i < input.length() && (std::isdigit(input[i]) || input[i] == '.')) {
                numbersStr += input[i];
                i++;
            }
            tokens.push_back(Token{TokensType::Number, numbersStr});
            i--;
        }

        else if (std::isalpha(c)) {
            std::string word ="";
            while (i < input.length() && (std::isalnum(input[i]) || input[i] == '_')) {
                word += input[i];
                i++;
            }
            if (word == "var") {
                tokens.push_back(Token{TokensType::KeywordVar, word});
            }
            else if (word == "max" || word == "min" || word == "pow" || word == "abs") {
                tokens.push_back(Token{TokensType::FunctionName, word});
            }
            else {
                tokens.push_back(Token{TokensType::Variable, word});
            }
            i--;
        }

        else if (c == '+' || c == '-' || c == '/' || c == '*') {
            tokens.push_back(Token{TokensType::Operator, std::string(1, c)});
        } else if (c == '(') {
            tokens.push_back(Token{TokensType::LeftParen, std::string(1, c)});
        } else if (c == ')') {
            tokens.push_back(Token{TokensType::RightParen, std::string(1, c)});
        } else if (c == '=') {
            tokens.push_back(Token{TokensType::Assign, std::string(1, c)});
        } else if (c == ',') {
            tokens.push_back(Token{TokensType::Comma, std::string(1, c)});
        } else if (c == '.') {
            tokens.push_back(Token{TokensType::Dot, std::string(1, c)});
        } else if (c == '{') {
            tokens.push_back(Token{TokensType::LeftCurly, std::string(1, c)});
        } else if (c == '}') {
            tokens.push_back(Token{TokensType::RightCurly, std::string(1, c)});
        }
    }
    return tokens;
}