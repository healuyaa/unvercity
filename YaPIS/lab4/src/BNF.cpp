#include <iostream>

#include "BNF.hpp"

namespace BNF {
    const void printBNF() {
        std::cout << "$ letter = \"A\"|\"B\"|\"C\"|\"D\"|\"E\"|\"F\"|\"G\"|\"H\"|\"I\"|\"J\"|\"K\"|\"L\"|\"M\"|"
                    "\"N\"|\"O\"|\"P\"|\"Q\"|\"R\"|\"S\"|\"T\"|\"U\"|\"V\"|\"W\"|\"X\"|\"Y\"|\"Z\"|"
                    "\"a\"|\"b\"|\"c\"|\"d\"|\"e\"|\"f\"|\"g\"|\"h\"|\"i\"|\"j\"|\"k\"|\"l\"|\"m\"|\"n\"|"
                    "\"o\"|\"p\"|\"q\"|\"r\"|\"s\"|\"t\"|\"u\"|\"v\"|\"w\"|\"x\"|\"y\"|\"z\".\n";
        std::cout << "$ num = \"0\"|\"1\"|\"2\"|\"3\"|\"4\"|\"5\"|\"6\"|\"7\"|\"8\"|\"9\".\n";
        std::cout << "$ id = letter {letter | num}.\n";
        std::cout << "$ mark = id \":\".\n";
        std::cout << "$ command = \"MOV\"|\"ADD\"|\"SUB\"|\"MUL\"|\"DIV\"|\"CMP\"|\"JMP\"|\"NOP\".\n";
        std::cout << "$ reg = \"AX\"|\"BX\"|\"CX\"|\"DX\".\n";
        std::cout << "$ data = num {num} | \"0x\" num {num}.\n";
        std::cout << "$ operand = id | reg | num.\n";
        std::cout << "$ term = [mark] command operand [\",\" operand].\n\n";
    }

    bool parseLine(const std::string& line) {
        std::smatch match;
        std::string remaining = line;

        if (std::regex_search(remaining, match, labelRegex)) {
            std::cout << "mark: " << match.str() << std::endl;
            remaining = match.suffix().str();
        }

        if (std::regex_search(remaining, match, commandRegex)) {
            std::cout << "command: " << match.str() << std::endl;
            remaining = match.suffix().str();
        } else {
            std::cerr << "Error: command not found in \"" << line << "\"" << std::endl;
            return false;
        }

        while (std::regex_search(remaining, match, operandRegex)) {
            std::cout << "operand: " << match.str() << std::endl;
            remaining = match.suffix().str();

            if (remaining.find(',') == 0) {
                remaining = remaining.substr(1);
            } else {
                break;
            }
        }

        return true;
    }
}