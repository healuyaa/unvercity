#pragma once

#include <functional>
#include <string>
#include <vector>

namespace lex {
    using checkers_t = std::vector<std::pair<std::string, std::function<bool(const std::string&)>>>;

    struct Token {
        std::string type;
        std::string value;
    };

    const std::vector<std::string> commands = {"MOV", "ADD", "SUB", "JMP", "NOP", "CMP"};

    bool isRegister(const std::string& token);
    bool isHex(const std::string& token);
    bool isDec(const std::string& token);
    bool isCommand(const std::string& token);
    bool isLabel(const std::string& token);

    std::vector<Token> lexicalAnalysis(const std::string& line);
}