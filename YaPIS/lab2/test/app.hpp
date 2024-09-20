#include <iostream>
#include <fstream>

#include "analyzer.hpp"

namespace lab {
    class App {
        public:
        static void run() {
            std::string line;
            std::vector<std::string> lines;
            std::fstream file("../input.asm");

            if (!file.is_open()) {
                std::cerr << "Ошибка: не удалось открыть файл." << std::endl;
            }

            while (std::getline(file, line)) {
                if (!line.empty() && line[0] != ';') {
                    lines.push_back(line);
                }
            }

            file.close();

            lex::analyzeCode(lines);

        }
    };
}