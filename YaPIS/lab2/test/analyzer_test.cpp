#include "analyzer.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <unordered_set>

namespace lex {
    bool isRegister(const std::string &token) {
        return token == "AX" || token == "BX" || token == "CX" || token == "DX";
    }

    bool isHex(const std::string &token) {
        if (token.size() > 2 && token[0] == '0' && token[1] == 'x') {
            return std::all_of(token.begin() + 2, token.end(), [](unsigned char c) {
                return std::isxdigit(c);
            });
        }
        return false;
    }

    bool isDec(const std::string &token) {
        return std::all_of(token.begin(), token.end(), [](unsigned char c) {
            return std::isdigit(c);
        });
    }

    bool isCommand(const std::string &token) {
        return std::find(commands.begin(), commands.end(), token) != commands.end();
    }

    bool isLabel(const std::string &token) {
        if (token.empty() || token.back() != ':') return false;
        if (!std::isalpha(token[0]) && token[0] != '_') return false;
        return std::all_of(token.begin(), token.end() - 1, [](unsigned char c) {
            return std::isalnum(c) || c == '_';
        });
    }

    checkers_t token_check = {
        {"Label", isLabel},
        {"Command", isCommand},
        {"Register", isRegister},
        {"Hex", isHex},
        {"Dec", isDec},
    };

    std::unordered_set<std::string> labels;

    std::vector<Token> lexicalAnalysis(const std::string &line) {
        std::vector<Token> tokens;
        std::string delimiters = " ,:";
        size_t start = 0;
        size_t end = line.find_first_of(delimiters);

        while (end != std::string::npos) {
            std::string token = line.substr(start, end - start);
            if (!token.empty()) {
                bool matched = false;

                if (line[end] == ':' && end == start + token.length()) {
                    token += ':';
                    end++;
                }

                for (const auto& checker : token_check) {
                    if (checker.second(token)) {
                        tokens.push_back({checker.first, token});
                        matched = true;

                        if (checker.first == "Label") {
                            labels.insert(token.substr(0, token.length() - 1));
                        }
                        break;
                    }
                }

                if (!matched && labels.find(token) != labels.end()) {
                    tokens.push_back({"Label", token});
                    matched = true;
                }

                if (!matched) {
                    tokens.push_back({"Unknown", token});
                }
            }

            if (line[end] != ' ') {
                tokens.push_back({"Delimiter", std::string(1, line[end])});
            }

            start = end + 1;
            end = line.find_first_of(delimiters, start);
        }

        std::string last_token = line.substr(start);
        if (!last_token.empty()) {
            bool matched = false;
            for (const auto& checker : token_check) {
                if (checker.second(last_token)) {
                    tokens.push_back({checker.first, last_token});
                    matched = true;
                    break;
                }
            }

            if (!matched && labels.find(last_token) != labels.end()) {
                tokens.push_back({"Label", last_token});
                matched = true;
            }

            if (!matched) {
                tokens.push_back({"Unknown", last_token});
            }
        }
        return tokens;
    }

    void analyzeCode(const std::vector<std::string>& lines) {
        for (const std::string& line : lines) {
            std::vector<Token> tokens = lexicalAnalysis(line);

            std::cout << "Tokens for line: " << line << std::endl;
            for (const auto& token : tokens) {
                std::cout << token.type << ": " << token.value << std::endl;
            }

            if (!tokens.empty() && tokens[0].type == "Label") {
                std::cout << "Label found: " << tokens[0].value << std::endl;
                tokens.erase(tokens.begin());
            }

            if (!tokens.empty()) {
                if (!isCommandValid(tokens)) {
                    std::cerr << "err wrong token " << line << std::endl;
                } else {
                    std::cout << "correct token " << line << std::endl;
                }
            }
        }
    }

    bool isCommandValid(const std::vector<Token>& tokens) {
        if (tokens.empty()) return false;

        if (isLabel(tokens[0].value) ) {
            
        } else {
            if (isCommand(tokens[0].value)) {
                // return isRegister(tokens.)
            }
        }
    }

}
