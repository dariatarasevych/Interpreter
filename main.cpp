#include <iostream>
#include "Tokenization.h"
#include "Environment.h"
#include "ShuntingYard.h"
#include "Evaluator.h"

int main() {
    Tokenization tokenization;
    std::string testInput = "var a = max(5, 3) * 2";
    auto tokens = tokenization.tokenize(testInput);

    for (const auto& token : tokens) {
        std::cout << "Token: " << token.value << std::endl;
    }

    try {
        Environment env;
        env.setVariable("a", 10.0);

        std::string expression = "max(a, 5) + 3 * 2";
        std::cout << "Original Expression: " << expression << std::endl;

        Tokenization tok;
        auto tokens = tok.tokenize(expression);

        ShuntingYard sy;
        auto rpn = sy.parseToRPN(tokens);

        Evaluator evaluator;
        double result = evaluator.evaluate(rpn, env);

        std::cout << "RPN Output: ";
        for (const auto& token : rpn) {
            std::cout << token.value << " ";
        }
        std::cout << std::endl;

        std::cout << "Final Result: " << result << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}