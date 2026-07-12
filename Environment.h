#ifndef ASSIGNMENT_5_ENVIRONMENT_H
#define ASSIGNMENT_5_ENVIRONMENT_H
#include <unordered_map>
#include <string>
#include <stdexcept>

class Environment {
private:
    std::unordered_map<std::string, double> variables;
public:
    void setVariable(const std::string& name, double value);

    double getVariable (const std::string& name) const;
};

#endif //ASSIGNMENT_5_ENVIRONMENT_H
