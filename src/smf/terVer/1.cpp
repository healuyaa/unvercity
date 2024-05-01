#include <iostream>
#include <math.h>

int main() {
    double xi[] = {-0.6, 1.6, 3.8, 6.0, 8.2, 10.4, 12.6};
    double ni[] = {4.0, 1.0, 9.0, 4.0, 7.0, 3.0, 1.0};
    double* xini = new double;
    double* xi2ni = new double;
    double sumNi = 0;
    double sumXini = 0;
    double sumXi2ni = 0;
    double dxB = 0;
    double DB = 0;
    double S2 =0;
    double S = 0;
    double lner = 0;
    double pner = 0;
    double ty = 2.756;
    double lner2 = 0;
    double pner2 = 0;
    double q = 0.43;
    double lner3 = 0;
    double pner3{};

    for (size_t i{1}; i < 7; ++i)
    {
        xini[i] = xi[i] * ni[i];
        xi2ni[i] = pow(xi[i], 2) * ni[i];
        sumNi += ni[i];
        sumXini += xini[i];
        sumXi2ni += xi2ni[i];
        std::cout << xini[i] << "       " << xi2ni[i] << std::endl;
    }
    std::cout << "ni: " << sumNi << "       " << "xini: " << sumXini << "       " << "xi2ni: " << sumXi2ni << std::endl;
    dxB = sumXini / sumNi;
    DB = (sumXi2ni / sumNi) - pow(dxB, 2);
    S2 = (sumNi / (sumNi - 1)) * DB;
    S = sqrt(S2);
    std::cout << "dxb: " << dxB << "        " << "DB: " << DB << "      " << "S2: " << S2 << "      " << "S: " << S << std::endl;   
    lner = dxB - ((ty * S) / sqrt(sumNi));
    pner = dxB + ((ty * S) / sqrt(sumNi));
    std::cout << lner << "<a<" << pner << std::endl;
    lner2 = S * (1 - q);
    pner2 = S * (1 + q);
    std::cout << lner2 << "<sigma<" << pner2 << std::endl;
    lner3 = 16.8 - ((2.58*5) / sqrt(25));
    pner3 = 16.8 + ((2.58*5) / sqrt(25));
    std::cout << lner3 << "<a<" << pner3 << std::endl;
}