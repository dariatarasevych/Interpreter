#include "Environment.h"
#include <string>
#include <iostream>

void Environment::setVariable(const std::string &name, double value) {
    if (variables.find(name) != variables.end()) { // якщо знайшли, то викидаємо помилку що другої такої змінної вже бути не може
        throw std::runtime_error("Variable: " + name + " is immutable and cannot be reassigned!");
    } else {
        variables[name] = value;
    }
}

double Environment::getVariable(const std::string &name) const {
    auto fn = variables.find(name);
    if (fn == variables.end()) { //якщо знайшли
        throw std::runtime_error("Undefined variable: " + name);
    } else {
        return fn -> second; // second = value (number), first = name ("a")
    }
}
