#include <iostream>
#include <math.h>

#define e 2.718
#define ly -0.278


int main() {
    double arr[] = {0.2, 6.4, 12.6, 18.9, 37.6};
    double answer = 0;
    double answer1 = 0;
    for (size_t i = 1; i < sizeof(arr) / sizeof(double); i++)
    {
        answer = pow(e, (ly * arr[i - 1])) - pow(e, (ly * arr[i]));
        std::cout << answer * 200 << "        ";
        answer1 += answer * 200;
        answer = 0;
    }std::cout << std::endl << answer1;
    
}