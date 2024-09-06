#pragma once

#include <vector>

namespace lab {
    class Field {
        public:
        static constexpr int GF_SIZE = 256;
        static constexpr int POLYNOMIAL = 0x11D;

        Field();

        protected:
        int add(int a, int b) const;
        int subtract(int a, int b) const;
        int multiply(int a, int b) const;
        int divide(int a, int b) const;
        int power(int a, int n) const;
        int inverse(int a) const;

        private:
        int log_table[GF_SIZE]{};
        int exp_table[GF_SIZE]{};
    };

    class ReedSolomon : public Field {
        public:
        std::vector<int> encode(const std::vector<int>& msg, int m, int n, int k);
        std::vector<int> decoder(const std::vector<int>& encoded, int m, int n, int k);

        private:    
        std::vector<int> genpoly(int k, int n);

        std::vector<int> syndromes(const std::vector<int>& encoded, int n, int k);
        std::vector<int> euclidAlg(const std::vector<int>& syndromes, int max_errors);
        std::vector<int> findErrPos(const std::vector<int>& error_locator_poly, int n);
        std::vector<int> findErrMagnitude(const std::vector<int>& error_positions, const std::vector<int>& syndromes);
    };
}