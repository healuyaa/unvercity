#include <iostream>
#include <vector>

bool isPalindrome(int x) {
    if (x < 0)
    {
        return false;
    }

    long long original = x;
    long long reverse = 0;
    while (x > 0)
    {
        long long temp = x % 10;
        reverse = reverse * 10 + temp;
        x /= 10;
    }
    return original == reverse;    
}

int main() {
    int x = 101;
    std::cout << isPalindrome(x);
}