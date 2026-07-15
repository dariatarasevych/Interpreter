#include "Evaluator.h"
#include <cmath>
#include <algorithm>

double Evaluator::evaluate(const std::vector<Token> &rpnTokens, const Environment &env) {
    std::stack<double> valuesStack;
    for (const auto &token: rpnTokens) {
        if (token.type == TokensType::Number) {
            valuesStack.push(std::stod(token.value)); //String TO Double
        }

        else if (token.type == TokensType::Variable) {
            if (env.hasFunction(token.value)) {

                bool hasIntegral = false;
                for (const auto& t : rpnTokens) {
                    if (t.value == "integral") {
                        hasIntegral = true;
                    }
                }

                if (hasIntegral) {
                    continue;
                }

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
        }

        else if (token.type == TokensType::Operator) {
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
        }

        else if (token.type == TokensType::FunctionName) {
            if (token.value == "abs") {
                if (valuesStack.empty()) {
                    throw std::runtime_error("Stack is empty.");
                }
                double a = valuesStack.top();
                valuesStack.pop();

                valuesStack.push(std::abs(a));
            } else if (token.value == "max" || token.value == "min" || token.value == "pow" || token.value == "integral") {
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
                } else if (token.value == "integral"){

                    int n = 1000;
                    double dx = (b-a)/n;
                    double sum = 0.0;

                    std::string funcName = "";
                    for (const auto& t : rpnTokens) {
                        if (t.type == TokensType::Variable && env.hasFunction(t.value)) {
                            funcName = t.value;
                            break;
                        }
                    }

                    if (funcName.empty()) {
                        throw std::runtime_error("No function provided for integral.");
                    }

                    FunctionSymbol targetFunc = env.getFunction(funcName);

                    std::string paramName = targetFunc.parameters[0];

                    Environment envA = env;
                    envA.setVariable(paramName, a);
                    double fa = evaluate(targetFunc.RPNtokens, envA);

                    Environment envB = env;
                    envB.setVariable(paramName, b);
                    double fb = evaluate(targetFunc.RPNtokens, envB);

                    for (int i = 1; i < n; ++i) {
                        double xi = a + i * dx;

                        Environment tempEnv = env;
                        tempEnv.setVariable(paramName, xi);
                        sum += evaluate(targetFunc.RPNtokens, tempEnv);
                    }

                    double trapezoidalRuleResult = dx * (((fa + fb) / 2.0) + sum); // за формулою трапецій: півсума основ крайніх точок + сума всіх внутрішніх точок, помножене на ширину dx
                    valuesStack.push(trapezoidalRuleResult);
                }
            }
        }
    }
    if (valuesStack.size() != 1) {
        throw std::runtime_error("Error!");
    }

    return valuesStack.top();
}
