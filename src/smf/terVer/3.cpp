#include <iostream>
#include <math.h>

int main() {
    double ni[] = {120.0, 48.0, 20.0, 12.0};
    double ni1[] = {155.42, 22.74, 4.98, 1.04};
    double answer[6];
    double answer1 = 0;

    for (size_t i = 0; i < sizeof(ni) / sizeof(double); i++)
    {
        answer[i] = (pow((ni[i] - ni1[i]), 2)) / ni1[i];    
        std::cout << answer[i] << "        ";
        answer1 += answer[i];
    }    std::cout << std::endl << answer1;
    std::cout << std::endl << (pow((48.0 - 22.74), 2) / 22.74);
}