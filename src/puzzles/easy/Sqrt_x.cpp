#include <iostream>
#include <math.h>

int mySqrt(int x) {
    if (x == 0 || x == 1)
        return x;

    int start = 1;
    int end = x;
    int answer = 0;

    while(start <= end) {
        answer = start + (end - start) / 2;

        if ((long long)answer * (long long)answer > x)
        {
            end = answer - 1;
        } else if(answer * answer == x) {
            return answer; 
            } else {
                start = answer + 1;
            } 
    }
    return std::floor(end);
}

int main() {
    int x = 2;
    std::cout << mySqrt(x);
}