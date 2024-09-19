#pragma once

#include <memory>
#include <vector>

namespace code {
    constexpr int SIZE_BITS = 16;
    constexpr int SIZE_MATRIX_2 = 2;
    constexpr int SIZE_MATRIX_4 = 4;
    constexpr int SIZE_MATRIX_8 = 8;

    enum class SIZES {
        size_rectangle = 2,
        size_square = 4
    };

    enum class Paritets {
        two = 2,
        three = 3,
        four = 4,
        five = 5
    };

    struct Variant {
        std::vector<std::vector<int>> matrix;

        std::vector<int> paritet_x;
        std::vector<int> paritet_y;
        int paritet_xy;

        std::vector<int> paritet_lu;
        std::vector<int> paritet_lb;

        std::vector<std::vector<int>> paritets_z;
    };

    class Iteratives {
        public:
        Iteratives(int number, SIZES size, Paritets paritet);
        ~Iteratives() = default;

        void SetCode(int i, int j);
        void encode();
        void decode();
        void print();

        private:
        std::unique_ptr<Variant> v;
        int number;

        SIZES size;
        Paritets paritet;

        void IntToMatrix(int number);

        void InitParitets();
        void UseParitets();

        void ThreeParitet();
        void FourParitet();
        void FiveParitet();
    };
}