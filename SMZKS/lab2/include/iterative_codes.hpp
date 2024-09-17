#pragma once

#include <vector>

namespace code {
    constexpr int SIZE_BITS = 16;
    constexpr int SIZE_MATRIX = 4;

    struct Variant {
        std::vector<std::vector<int>> matrix;
        std::vector<int> paritet_x;
        std::vector<int> paritet_y;
        int paritet_xy;
    };

    class Iteratives {
        public:
        Iteratives(int number);

        void encode();

        private:
        Variant *v;
        int number;

        void IntToMatrix(int number);
    };
}