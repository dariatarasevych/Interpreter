#ifndef ASSIGNMENT_5_ENVIRONMENT_H
#define ASSIGNMENT_5_ENVIRONMENT_H
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <vector>
#include "Token.h"

struct FunctionSymbol {
    std::string name;
    std::vector<std::string> parameters;
    std::vector<Token> RPNtokens;

};

class Environment {
private:
    std::unordered_map<std::string, double> variables;
    std::unordered_map<std::string, FunctionSymbol> functions;
public:
    void setVariable(const std::string& name, double value);

    double getVariable (const std::string& name) const;

    void setFunction(const FunctionSymbol& func);
    FunctionSymbol getFunction(const std::string& name) const;

    bool hasFunction(const std::string& name) const;
};

#endif //ASSIGNMENT_5_ENVIRONMENT_H
