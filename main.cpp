#include <iostream>
#include <vector>

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

class Tokenization {
public:
    std::vector<Token> tokenize(std::string& input) {
        std::vector<Token> tokens;

        for (int i =0; i < input.length(); i++) {
            char c = input[i];

            if (std::isspace(c)) {continue;}

            // щоб зібралося ціле число, а не кожна цифра окремо
            if (std::isdigit(c)) {
                std::string numbersStr ="";
                while (i < input.length() && (std::isdigit(input[i]) || input[i] == '.')) {
                    numbersStr += input[i];
                    i++;
                }
                tokens.push_back(Token{TokensType::Number, numbersStr});
                i--;
            }

            else if (std::isalpha(c)) {
                std::string word ="";
                while (i < input.length() && (std::isalpha(input[i]) || input[i] == '_')) {
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
            }
        }
        return tokens;
    }
};

int main() {
    Tokenization tokenization;
    std::string testInput = "var a = max(5, 3) * 2";
    auto tokens = tokenization.tokenize(testInput);

    for (const auto& token : tokens) {
        std::cout << "Tokens: " << token.value << std::endl;
    }
    return 0;
}
