#include <iostream>
#include <fstream>

#include "BNF.hpp"

namespace lab {
    class App {
        public:
        static void run() {
            std::ifstream input_file("../input.asm");
            if (!input_file.is_open()) {
                std::cerr << "Error: Could not open file 'input.txt'" << std::endl;
            }

            BNF::printBNF();

            std::string line;
            while (std::getline(input_file, line)) {
                std::cout << "Analyzing: " << line << std::endl;
                if (!BNF::parseLine(line)) {
                    std::cerr << "Error analyzing: " << line << std::endl;
                }
                std::cout << std::endl;
            }
            input_file.close();
        }
    };
}