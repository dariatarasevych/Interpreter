#include "Evaluator.h"
#include <cmath>
#include <algorithm>

double Evaluator::evaluate(const std::vector<Token> &rpnTokens, const Environment &env) {
    std::stack<double> valuesStack;
    for (const auto &token: rpnTokens) {
        if (token.type == TokensType::Number) {
            valuesStack.push(std::stod(token.value)); //String TO Double
        } else if (token.type == TokensType::Variable) {
            if (env.hasFunction(token.value)) {
                FunctionSymbol func = env.getFunction(token.value);

                if (valuesStack.size() < func.parameters.size()) {
                    throw std::runtime_error("Not enough arguments for function: " + func.name);
                }

                std::vector<double> args(func.parameters.size());

                for (int j = (int) func.parameters.size() - 1; j >= 0; --j) {
                    args[j] = valuesStack.top();
                    valuesStack.pop();
                }

                Environment tempEnv = env;
                for (int j = 0; j < func.parameters.size(); ++j) {
                    tempEnv.setVariable(func.parameters[j], args[j]);
                }

                double result = evaluate(func.RPNtokens, tempEnv);
                valuesStack.push(result);
            } else {
                valuesStack.push(env.getVariable(token.value));
            }
        } else if (token.type == TokensType::Operator) {
            if (valuesStack.size() < 2) {
                throw std::runtime_error("Invalid expression.");
            }
            double b = valuesStack.top();
            valuesStack.pop();

            double a = valuesStack.top();
            valuesStack.pop();

            if (token.value == "+") {
                valuesStack.push(a + b);
            } else if (token.value == "-") {
                valuesStack.push(a - b);
            } else if (token.value == "*") {
                valuesStack.push(a * b);
            } else if (token.value == "/") {
                if (b == 0) {
                    throw std::runtime_error("Devision by zero.");
                } else {
                    valuesStack.push(a / b);
                }
            }
        } else if (token.type == TokensType::FunctionName) {
            if (token.value == "abs") {
                if (valuesStack.empty()) {
                    throw std::runtime_error("Stack is empty.");
                }
                double a = valuesStack.top();
                valuesStack.pop();

                valuesStack.push(std::abs(a));
            } else if (token.value == "max" || token.value == "min" || token.value == "pow") {
                if (valuesStack.size() < 2) {
                    throw std::runtime_error("Invalid expression.");
                }

                double b = valuesStack.top();
                valuesStack.pop();

                double a = valuesStack.top();
                valuesStack.pop();

                if (token.value == "max") {
                    valuesStack.push(std::max(a, b));
                } else if (token.value == "min") {
                    valuesStack.push(std::min(a, b));
                } else if (token.value == "pow") {
                    valuesStack.push(std::pow(a, b));
                }
            }
        }
    }
    if (valuesStack.size() != 1) {
        throw std::runtime_error("Error!");
    }

    return valuesStack.top();
}
