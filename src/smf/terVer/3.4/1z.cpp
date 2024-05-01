#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

int main() {
    double arr[50] = {13.7, 15.7, 15.5, 11.8, 13.1, 16.4, 17.8, 18.2, 19.9, 12.3, 13.8, 11.8, 21, 7.7, 13.4,
                    13.3, 15.4, 11, 7.8, 16.6, 15.5, 17.9, 12.2, 11.5, 12.1, 16, 22.7, 16.6, 11, 14, 10.2,
                    15.3, 16, 16.7, 15.6, 15.5, 12.9, 17.4, 11, 13.4, 10.4, 14.7, 6.4, 16.1, 15.6, 14.5, 18,
                    19.3, 18.4, 16.4};
    double min = arr[0], max = arr[0];
    for (size_t i = 0; i < 50; i++)
    {
        min > arr[i] ? min = arr[i] : min = min;
        max < arr[i] ? max = arr[i] : max = max;
    }
    std::cout << "min: " << min << "        " << "max: " << max << std::endl;

    double h = (max - min) / (1 + 3.322 * log10l(50));
    std::cout << "value h: " << h << std::endl;

    std::vector<float> _xi;
    while(min < max) {
        _xi.push_back(min);
        min += 2.5;
    }
    _xi.push_back(min);
    std::cout << "arrays xi: ";
    for (auto xi : _xi)
    {
        std::cout << xi << " ";
    } std::cout << std::endl;

    double* first = &arr[0];
    double* last = &arr[49];
    std::sort(first, last);
    for(auto a: arr) {
        std::cout << a << " ";
    } std::cout << std::endl;

    double nNIh[] = {3 / (50 * 2.5), 5 / (50 * 2.5), 13 / (50 * 2.5), 14 / (50 * 2.5), 11 / (50 * 2.5), 3 / (50 * 2.5), 1 / (50 * 2.5)};
    double temp = nNIh[0];
    std::cout << temp << " ";
    for(int i = 1; i < sizeof(nNIh)/sizeof(double); i++) {
        temp += nNIh[i];
        std::cout << nNIh[i] << " ";
    } std::cout << std::endl;

    float _ai[7] = {(6.4 + 8.9) / 2, (8.9 + 11.4) / 2, (11.4 + 13.9) / 2, (13.9 + 16.4) / 2, (16.4 + 18.9) / 2, (18.9 + 21.4) / 2, (21.4 + 23.9) / 2};
    for(auto _a: _ai) {
        std::cout << "xi: " << _a << " " << std::endl;
    } std:: cout << std::endl;

    float _xini[7];
    float _xi2ni[7];
    float _N[7] = {3.0, 5.0, 13.0, 14.0, 11.0, 3.0, 1.0};

    float sumXI = 0;
    float sumXI2 = 0;
    for(int i = 0; i < 7; i++) {
        _xini[i] = _ai[i] * _N[i];
        _xi2ni[i] = _xini[i] * _ai[i];
        sumXI += _xini[i];
        sumXI2 += _xi2ni[i]; 
    }
    for(int i = 0; i < 7; i++) {
        std::cout << "xini: " << _xini[i] << "  xi2ni: " << _xi2ni[i] << std::endl;
    }
    std::cout << sumXI << "     " << sumXI2 << std::endl;
    double coordInt = 0;
    for (size_t i = 0; i < sizeof(_xi) / sizeof(double); i++)
    {
        coordInt = (_xi[i] - 14.55) / 3.37;
        std::cout << coordInt << " ";
        coordInt = 0;
    }
    
}