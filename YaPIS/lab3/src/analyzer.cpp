#include "analyzer.hpp"

#include <algorithm>
#include <regex>

namespace lex {
    bool isRegister(const std::string &token) {
        return token == "AX" || token == "BX" || token == "CX" || token == "DX";
    }

    bool isHex(const std::string &token) {
        return std::regex_match(token, std::regex("^0x[0-9A-Fa-f]+$"));
    }

    bool isDec(const std::string &token) {
        return std::regex_match(token, std::regex("^[0-9]+$"));
    }

    bool isCommand(const std::string &token) {
        return std::find(commands.begin(), commands.end(), token) != commands.end();
    }

    bool isLabel(const std::string &token) {
        return std::regex_match(token, std::regex("^[a-zA-Z_][a-zA-Z0-9_]*:$"));
    }

    checkers_t token_check = {
        {"Label", isLabel},
        {"Command", isCommand},
        {"Register", isRegister},
        {"Hex", isHex},
        {"Dec", isDec},
    };

    std::vector<Token> lexicalAnalysis(const std::string &line) {
        std::vector<Token> tokens;
        std::regex token_regex(R"(([a-zA-Z_][a-zA-Z0-9_]*:|0x[0-9A-Fa-f]+|\d+|AX|BX|CX|DX|MOV|ADD|SUB|JMP|NOP|CMP|,|:))");
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), token_regex);
        auto words_end = std::sregex_iterator();

        for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            std::string token = match.str();
            bool matched = false;

            for(const auto& checker: token_check) {
                if(checker.second(token)) {
                    tokens.push_back({checker.first, token});
                    matched = true;
                    break;
                }
            }

            if(!matched) {
                if(token == "," || token == ":") {
                    tokens.push_back({"Delimiter", token});
                } else {
                    tokens.push_back({"Unknown", token});
                }
            }
        }

        return tokens;
    }
}