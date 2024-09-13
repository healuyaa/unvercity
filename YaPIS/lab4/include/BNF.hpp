#pragma once

#include <regex>
#include <string>

namespace BNF {
    const std::regex labelRegex("[a-zA-Z][a-zA-Z0-9]*:");
    const std::regex commandRegex("(MOV|ADD|SUB|MUL|DIV|CMP|JMP|NOP)");
    const std::regex registerRegex("(AX|BX|CX|DX)");
    const std::regex numberRegex("(\\d+|0x[0-9A-Fa-f]+)");
    const std::regex operandRegex("([a-zA-Z][a-zA-Z0-9]*|AX|BX|CX|DX|\\d+|0x[0-9A-Fa-f]+)");

    const void printBNF();
    bool parseLine(const std::string& line);
}