#pragma once

#include "reed-solomon.hpp"
#include <iostream>

class DoReedSolomon {
    public:
    static void start() {
        lab::ReedSolomon rs;

        std::vector<int> msg = {84, 101, 115, 116};
        std::cout << "Message: ";
        for (int val : msg) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        int m = 8;
        int n = 12;
        int k = msg.size();

        std::cout << "Bit size character: " << m << "\nCodeword length: " << n << "\nOriginal message length: " << k << std::endl;

        std::vector<int> encoded = rs.encode(msg, m, n, k);

        std::cout << "Encoded message: ";
        for (int val : encoded) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        std::vector<int> decoded = rs.decoder(encoded, m, n, k);

        std::cout << "Decoded message: ";
        for (int val : decoded) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};