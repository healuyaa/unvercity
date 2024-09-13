#include <iostream>
#include <fstream>

#include "analyzer.hpp"

namespace lab {
    class App {
        public:
        static void run() {
            std::string line;
            std::fstream file("../input.asm");

            while(std::getline(file, line)) {
                if(line.empty() || line[0] == ';') continue;
                std::vector<lex::Token> tokens = lex::lexicalAnalysis(line);

                for(const auto& token: tokens) {
                    std::cout << "Type: " << token.type << ", Value: " << token.value << std::endl;
                }
            }

            file.close();
        }
    };
}