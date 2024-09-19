#include "iterative_codes.hpp"

#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

namespace code {
    Iteratives::Iteratives(int number, SIZES size, Paritets paritet) : number(number), v(std::make_unique<Variant>()), size(size), paritet(paritet) {
        if(size == SIZES::size_square) {
            v->matrix.resize(SIZE_MATRIX_4);
            for(auto& m: v->matrix) {
                m.resize(SIZE_MATRIX_4);
            }

            v->paritet_x.resize(SIZE_MATRIX_4);
            v->paritet_y.resize(SIZE_MATRIX_4);

        } else if(size == SIZES::size_rectangle) {
            v->matrix.resize(SIZE_MATRIX_8);
            for(auto& m: v->matrix) {
                m.resize(SIZE_MATRIX_2);
            }

            v->paritet_x.resize(SIZE_MATRIX_8);
            v->paritet_y.resize(SIZE_MATRIX_2);

        }

        IntToMatrix(number);
        InitParitets();
    }

    void Iteratives::SetCode(int i, int j) {
        v->matrix[i][j] ^= 1;
    }

    void Iteratives::encode() {     
        if(size == SIZES::size_square) {
            for (int i = 0; i < SIZE_MATRIX_4; ++i) {
                int temp_x = 0;
                int temp_y = 0;

                for(int j = 0; j < SIZE_MATRIX_4; ++j) {
                    v->matrix[i][j] == 1 ? ++temp_x : temp_x;
                    v->matrix[j][i] == 1 ? ++temp_y : temp_y;
                }

                v->paritet_y[i] = (temp_x & 1) == 0 ? 0 : 1;
                v->paritet_x[i] = (temp_y & 1) == 0 ? 0 : 1;
            }

            int count = 0;
            for(int i = 0; i < SIZE_MATRIX_4; ++i) {
                if((v->paritet_x[i] & 1) == 0) ++count;
                if((v->paritet_y[i] & 1) == 0) ++count;
            }

            v->paritet_xy = (count & 1) == 0 ? 0 : 1;

            UseParitets();
        } else if(size == SIZES::size_rectangle) {
            for (int i = 0; i < SIZE_MATRIX_2; ++i) {
                int temp_x = 0;

                for (int j = 0; j < SIZE_MATRIX_8; ++j) {
                    v->matrix[i][j] == 1 ? ++temp_x : temp_x;
                }

                v->paritet_y[i] = (temp_x & 1) == 0 ? 0 : 1;
            }

            for (int j = 0; j < SIZE_MATRIX_8; ++j) {
                int temp_y = 0;

                for (int i = 0; i < SIZE_MATRIX_2; ++i) {
                    v->matrix[i][j] == 1 ? ++temp_y : temp_y;
                }

                v->paritet_x[j] = (temp_y & 1) == 0 ? 0 : 1;
            }

            int count = 0;
            for(int i = 0; i < SIZE_MATRIX_8; ++i) {
                if((v->paritet_x[i] & 1) == 0) ++count;
            }
            for(int i = 0; i < SIZE_MATRIX_2; ++i) {
                if((v->paritet_y[i] & 1) == 0) ++count;
            }

            v->paritet_xy = (count & 1) == 0 ? 0 : 1;

            UseParitets();
        }        
    }

    void Iteratives::decode() {
        bool errorFound = true;

        if(size == SIZES::size_square) {
            while (errorFound) {
                errorFound = false;
                int error_x = -1;
                int error_y = -1;

                for (int i = 0; i < SIZE_MATRIX_4; ++i) {
                    int temp_x = 0;
                    int temp_y = 0;

                    for (int j = 0; j < SIZE_MATRIX_4; ++j) {
                        v->matrix[i][j] == 1 ? ++temp_x : temp_x;
                        v->matrix[j][i] == 1 ? ++temp_y : temp_y;
                    }

                    temp_x = (temp_x & 1) == 0 ? 0 : 1;
                    temp_y = (temp_y & 1) == 0 ? 0 : 1;

                    if (temp_x != v->paritet_y[i]) {
                        error_x = i;
                    }
                    if (temp_y != v->paritet_x[i]) {
                        error_y = i;
                    }

                    if (error_x != -1 && error_y != -1) {
                        std::cout << "Error pos: " << error_x << ' ' << error_y << std::endl;
                        SetCode(error_x, error_y);
                        errorFound = true;
                    }
                }
            }
        } else if(size == SIZES::size_rectangle) {
            while (errorFound) {
                errorFound = false;
                int error_x = -1;
                int error_y = -1;

                for (int i = 0; i < SIZE_MATRIX_2; ++i) {
                    int temp_x = 0;

                    for (int j = 0; j < SIZE_MATRIX_8; ++j) {
                        v->matrix[i][j] == 1 ? ++temp_x : temp_x;
                    }

                    temp_x = (temp_x & 1) == 0 ? 0 : 1;

                    if (temp_x != v->paritet_y[i]) {
                        error_x = i;
                    }
                }

                for (int j = 0; j < SIZE_MATRIX_8; ++j) {
                    int temp_y = 0;

                    for (int i = 0; i < SIZE_MATRIX_2; ++i) {
                        v->matrix[i][j] == 1 ? ++temp_y : temp_y;
                    }

                    temp_y = (temp_y & 1) == 0 ? 0 : 1;

                    if (temp_y != v->paritet_x[j]) {
                        error_y = j;
                    }
                }
                
                if (error_x != -1 && error_y != -1) {
                    std::cout << "Error pos: " << error_x << ' ' << error_y << std::endl;
                    SetCode(error_x, error_y);
                    errorFound = true;
                }
            }            
        }

        std::cout << "No more errors" << std::endl;
    }

    void Iteratives::print() {
        if(size == SIZES::size_square) {
            for(int i = 0; i < SIZE_MATRIX_4; ++i) {
                for(int j = 0; j < SIZE_MATRIX_4; ++j) {
                    std::cout << v->matrix[i][j] << ' ';
                }
                std::cout << "  " << v->paritet_y[i];
                std::cout << std::endl;
            }
            std::cout << std::endl;

            for(auto x: v->paritet_x) {
                std::cout << x << ' ';
            }
            std::cout << "  " << v->paritet_xy;
            std::cout << std::endl;
        } else if(size == SIZES::size_rectangle) {
            for(int i = 0; i < SIZE_MATRIX_2; ++i) {
                for(int j = 0; j < SIZE_MATRIX_8; ++j) {
                    std::cout << v->matrix[i][j] << ' ';
                }
                std::cout << "  " << v->paritet_y[i];
                std::cout << std::endl;
            }
            std::cout << std::endl;

            for(auto x: v->paritet_x) {
                std::cout << x << ' ';
            }
            std::cout << "  " << v->paritet_xy;
            std::cout << std::endl;
        }
    }

    void Iteratives::IntToMatrix(int number) {
        std::bitset<SIZE_BITS> binary(number);

        if(size == SIZES::size_square) {            
            for(int i = 0; i < SIZE_MATRIX_4; ++i) {
                for(int j = 0; j < SIZE_MATRIX_4; ++j) {
                    v->matrix[i][j] = binary[i * SIZE_MATRIX_4 + j];
                }
            }
        } else if(size == SIZES::size_rectangle) {
            for(int i = 0; i < SIZE_MATRIX_2; ++i) {
                for(int j = 0; j < SIZE_MATRIX_8; ++j) {
                    v->matrix[i][j] = binary[i * SIZE_MATRIX_8 + j];
                }
            }
        }
    }

    void Iteratives::InitParitets() {
        if (size == SIZES::size_square) {
            switch (paritet) {
                case Paritets::two:
                    break;

                case Paritets::three:
                    v->paritet_lu.reserve(SIZE_MATRIX_4);
                    break;

                case Paritets::four:
                    v->paritet_lu.reserve(SIZE_MATRIX_4);
                    v->paritet_lb.reserve(SIZE_MATRIX_4);
                    break;

                case Paritets::five:
                    v->paritet_lu.reserve(SIZE_MATRIX_4);
                    v->paritet_lb.reserve(SIZE_MATRIX_4);

                    // v->paritets_z.resize(SIZE_MATRIX_4);
                    // for(auto& z: v->matrix) {
                    //     z.resize(SIZE_MATRIX_4);
                    // }
                    break;
            }
        } else if(size == SIZES::size_rectangle) {
            // switch (paritet) {
            //     case Paritets::two:
            //         break;

            //     case Paritets::three:
            //         v->paritet_lu.reserve(SIZE_MATRIX_4);
            //         break;

            //     case Paritets::four:
            //         v->paritet_lu.reserve(SIZE_MATRIX_4);
            //         v->paritet_lb.reserve(SIZE_MATRIX_4);
            //         break;

            //     case Paritets::five:
            //         v->paritet_lu.reserve(SIZE_MATRIX_4);
            //         v->paritet_lb.reserve(SIZE_MATRIX_4);

            //         // v->paritets_z.resize(SIZE_MATRIX_4);
            //         // for(auto& z: v->matrix) {
            //         //     z.resize(SIZE_MATRIX_4);
            //         // }
            //         break;
            // }
        }
    }

    void Iteratives::UseParitets() {
        switch (paritet) {
            case Paritets::two:
                break;

            case Paritets::three:
                ThreeParitet();
                break;

            case Paritets::four:
                ThreeParitet();
                FourParitet();
                break;

            case Paritets::five:
                ThreeParitet();
                FourParitet();
                FiveParitet();

                // v->paritets_z.resize(SIZE_MATRIX_4);
                // for(auto& z: v->matrix) {
                //     z.resize(SIZE_MATRIX_4);
                // }
                break;
        }
    }

    void Iteratives::ThreeParitet() {

    }

    void Iteratives::FourParitet() {

    }

    void Iteratives::FiveParitet() {

    }
}