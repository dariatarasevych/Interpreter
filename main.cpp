#include <iostream>
#include "Tokenization.h"

int main() {
    Tokenization tokenization;
    std::string testInput = "var a = max(5, 3) * 2";
    auto tokens = tokenization.tokenize(testInput);

    for (const auto& token : tokens) {
        std::cout << "Token: " << token.value << std::endl;
    }
    return 0;
}
