#include <iostream>
#include <vector>

using std::vector;

vector<int> plusOne(vector<int>& digits) {
    digits[digits.size() - 1]++;
    for (size_t i = digits.size(); i > 0 ; i--)
    {
        if (digits[i] % 10 == 0)
        {
            digits[i - 1]++;
            digits[i] = 0;
        }
        if (digits[0] % 10 == 0)
        {
            digits.push_back(0);
            digits[0] = 0;
            for (size_t i = digits.size() - 1; i > 0 ; i--)
            {
                digits[i] = digits[i - 1];
            }
            digits[0] = 1;
            break;            
        }
    }
    return digits;    
}

int main() {
    vector<int> digits = {9, 0, 9, 9};
    plusOne(digits);
    for (size_t i = 0; i < digits.size(); i++)
    {
        std::cout << digits[i] << ' ';
    }    
}