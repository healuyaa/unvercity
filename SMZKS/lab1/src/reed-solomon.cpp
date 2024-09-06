#include "reed-solomon.hpp"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace lab {
    Field::Field() {
        int x = 1;
        for(int i = 0; i < GF_SIZE - 1; ++i) {
            exp_table[i] = x;
            log_table[x] = i;
            x <<= 1;
            if(x & GF_SIZE) {
                x ^= POLYNOMIAL;
            }
        }
        exp_table[GF_SIZE - 1] = exp_table[0];
    }

    int Field::add(int a, int b) const {
        return a ^ b;
    }

    int Field::subtract(int a, int b) const {
        return a ^ b;
    }

    int Field::multiply(int a, int b) const {
        if(a == 0 || b == 0) return 0;
        return exp_table[(log_table[a] + log_table[b]) % (GF_SIZE - 1)];
    }

    int Field::divide(int a, int b) const {
        if(b == 0) throw std::runtime_error("Division by zero in GF(2^8)");
        if(a == 0) return 0;
        return exp_table[(log_table[a] - log_table[b] + (GF_SIZE - 1)) % (GF_SIZE - 1)];
    }

    int Field::power(int a, int n) const {
        return exp_table[(log_table[a] * n) % (GF_SIZE - 1)];
    }

    int Field::inverse(int a) const {
        if(a == 0) throw std::runtime_error("No inverse exists for zero in GF(2^8)");
        return exp_table[(GF_SIZE - 1 - log_table[a])];
    }

    std::vector<int> ReedSolomon::encode(const std::vector<int>& msg, int m, int n, int k) {
        std::vector<int> g_x = genpoly(k, n);

        std::vector<int> msg_padded = msg;
        msg_padded.resize(n, 0);

        std::vector<int> temp(msg_padded);

        for (int i = 0; i < k; ++i) {
            int coef = temp[i];
            if (coef != 0) {
                for (size_t j = 0; j < g_x.size(); ++j) {
                    if (i + j < temp.size()) {
                        msg_padded[i + j] ^= multiply(coef, g_x[j]);
                    }
                }
            }
        }

        return msg_padded;
    }

    std::vector<int> ReedSolomon::decoder(const std::vector<int>& encoded, int m, int n, int k) {
        int max_errors = (n - k) / 2;
    
        std::vector<int> S = syndromes(encoded, n, k);

        if (std::all_of(S.begin(), S.end(), [](int s) { return s == 0; })) {
            return std::vector<int>(encoded.begin(), encoded.begin() + k);
        }

        std::vector<int> error_locator_poly = euclidAlg(S, max_errors);

        std::vector<int> error_positions = findErrPos(error_locator_poly, n);

        if (error_positions.empty()) {
            return std::vector<int>(encoded.begin(), encoded.begin() + k);
        }

        std::vector<int> error_magnitudes = findErrMagnitude(error_positions, S);

        std::vector<int> decoded(encoded);
        for (size_t i = 0; i < error_positions.size(); ++i) {
            decoded[error_positions[i]] = subtract(decoded[error_positions[i]], error_magnitudes[i]);
        }

        return std::vector<int>(decoded.begin(), decoded.begin() + k);
    }

    std::vector<int> ReedSolomon::genpoly(int k, int n) {
        std::vector<int> g = {1};
        for (int i = 0; i < n - k; ++i) {
            std::vector<int> term = {1, power(2, i)};
            std::vector<int> temp(g.size() + 1);
            
            for (size_t j = 0; j < g.size(); ++j) {
                temp[j] = multiply(g[j], term[0]);
                temp[j + 1] ^= multiply(g[j], term[1]);
            }
            g = temp;
        }
        return g;
    }

    std::vector<int> ReedSolomon::syndromes(const std::vector<int>& encoded, int n, int k) {
        std::vector<int> syndromes(n - k);
        for (int i = 0; i < n - k; ++i) {
            int sum = 0;
            for (int j = 0; j < n; ++j) {
                sum = add(sum, multiply(encoded[j], power(2, i * j)));
            }
            syndromes[i] = sum;
        }
        return syndromes;
    }

    std::vector<int> ReedSolomon::euclidAlg(const std::vector<int>& syndromes, int max_errors) {
        std::vector<int> r0(2 * max_errors + 1, 0);
        r0[0] = 1;

        std::vector<int> r1 = syndromes;

        std::vector<int> g0(2 * max_errors + 1, 0);
        g0[0] = 1;

        std::vector<int> g1(2 * max_errors + 1, 0);

        while (true) {
            int r0_degree = r0.size() - 1;
            int r1_degree = r1.size() - 1;

            if (r1_degree < 0 || std::all_of(r1.begin(), r1.end(), [](int coeff) { return coeff == 0; })) {
                break;
            }

            std::vector<int> quotient(r0_degree - r1_degree + 1, 0);

            if (r1[0] != 0) {
                int divisor_leading = r1[0];
                for (size_t i = 0; i < quotient.size(); ++i) {
                    if (i < r0.size()) {
                        quotient[i] = divide(r0[i], divisor_leading);
                    }
                }

                std::vector<int> tmp(r1.size() + quotient.size() - 1, 0);
                for (size_t i = 0; i < r1.size(); ++i) {
                    for (size_t j = 0; j < quotient.size(); ++j) {
                        if (i + j < tmp.size()) {
                            tmp[i + j] = add(tmp[i + j], multiply(r1[i], quotient[j]));
                        }
                    }
                }

                std::vector<int> new_r0(r0.size(), 0);
                for (size_t i = 0; i < r0.size(); ++i) {
                    if (i < tmp.size()) {
                        new_r0[i] = subtract(r0[i], tmp[i]);
                    } else {
                        new_r0[i] = r0[i];
                    }
                }

                std::vector<int> new_g0(g0.size() + quotient.size() - 1, 0);
                for (size_t i = 0; i < g0.size(); ++i) {
                    for (size_t j = 0; j < quotient.size(); ++j) {
                        if (i + j < new_g0.size()) {
                            new_g0[i + j] = add(new_g0[i + j], multiply(g0[i], quotient[j]));
                        }
                    }
                }

                r0 = r1;
                r1 = new_r0;

                g0 = g1;
                g1 = new_g0;
            } else {
                break;
            }
        }

        return g1;
    }

    std::vector<int> ReedSolomon::findErrPos(const std::vector<int>& error_locator_poly, int n) {
        std::vector<int> error_positions;
        for (int i = 0; i < n; ++i) {
            int eval = 0;
            for (size_t j = 0; j < error_locator_poly.size(); ++j) {
                eval = add(eval, multiply(error_locator_poly[j], power(2, j * i)));
            }
            if (eval == 0) {
                error_positions.push_back(n - 1 - i);
            }
        }
        return error_positions;
    }

    std::vector<int> ReedSolomon::findErrMagnitude(const std::vector<int>& error_positions, const std::vector<int>& syndromes) {
        std::vector<int> error_magnitudes(error_positions.size(), 0);
        for (size_t i = 0; i < error_positions.size(); ++i) {
            int pos = error_positions[i];
            int magnitude = syndromes[0];
            for (size_t j = 1; j < syndromes.size(); ++j) {
                magnitude = add(magnitude, multiply(syndromes[j], power(pos, j)));
            }
            error_magnitudes[i] = magnitude;
        }
        return error_magnitudes;
    }
}