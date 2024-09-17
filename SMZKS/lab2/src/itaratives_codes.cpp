#include "iterative_codes.hpp"
#include <bitset>

namespace code {
    Iteratives::Iteratives(int number) : number(number) {
        v->matrix.resize(SIZE_MATRIX);
        for(auto& m: v->matrix) {
            m.resize(SIZE_MATRIX);
        }
        v->paritet_x.resize(SIZE_MATRIX);
        v->paritet_y.resize(SIZE_MATRIX);

        IntToMatrix(number);
    }

    void Iteratives::encode() {        
        for (int i = 0; i < SIZE_MATRIX; ++i) {
            int temp = 0;
            for(int j = 0; j < SIZE_MATRIX; ++j) {
                v->matrix[i][j] == 1 ? ++temp : temp;
            }
            v->paritet_x[i] = (number & 1) == 0 ? 0 : 1;
        }
    }

    void Iteratives::IntToMatrix(int number) {
        std::bitset<SIZE_BITS> binary(number);
        for(int i = 0; i < SIZE_MATRIX; ++i) {
            for(int j = 0; j < SIZE_MATRIX; ++j) {
                v->matrix[i][j] = binary[i * SIZE_MATRIX + j];
            }
        }
    }
}