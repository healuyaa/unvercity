#include "iterative_codes.hpp"
#include <iostream>
#include <ostream>

namespace lab {
    class App {
        public:
        static void run() {
            code::Iteratives app(8080, code::SIZES::size_square, code::Paritets::two);
            app.encode();
            std::cout << "Matrix: " << std::endl;
            app.print();
            std::cout << "-----------------------------" << std::endl;
            // app.SetCode(1, 1);
            // app.SetCode(1, 2);
            app.SetCode(1, 3);
            // app.SetCode(1, 1);
            // app.SetCode(2, 1);
            // app.SetCode(3, 1);
            std::cout << "Matrix with err: " << std::endl;
            app.print();
            std::cout << "-----------------------------" << std::endl;
            std::cout << "Find err: " << std::endl;
            app.decode();
            std::cout << "-----------------------------" << std::endl;
            std::cout << "Correct matrix: " << std::endl;
            app.print();
            std::cout << "---------------------------------------------------------------------------------------" << std::endl;
        }
    };
}