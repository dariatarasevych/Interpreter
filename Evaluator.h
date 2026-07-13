#ifndef ASSIGNMENT_5_EVALUATOR_H
#define ASSIGNMENT_5_EVALUATOR_H
#include <vector>
#include <stack>
#include "Token.h"
#include "Environment.h"
#include <string>

class Evaluator {
public:
    double evaluate(const std::vector<Token>& rpnTokens, const Environment& env);
};

#endif //ASSIGNMENT_5_EVALUATOR_H
