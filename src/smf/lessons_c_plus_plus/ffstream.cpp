#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class abc {
    public:
    abc() {} 
    abc(int i, double d, float f, bool b, std::vector<int> vec, std::string str) : i(i), d(d), f(f), b(b) {
        this->str = str;
        for(auto a : vec) {
            vec.push_back(a);
        }
    }

    void print() {
        std::cout << i << ' ' << d << ' ' << f << ' ' << b << std::endl;
        for (size_t i = 0; i < str.size(); i++)
        {
            std::cout << str[i] << ' ';
        } 
        std::cout << std::endl;
        for(int a: vec) {
            std::cout << a  << ' ';
        }
        std::cout << std::endl;
    }

    private: 
    int i;
    double d;
    float f;
    bool b;
    std::vector<int> vec;
    std::string str;
};

void ffstream___1(abc& abc1) {
    std::fstream file;
    file.open("C:/project/projects_g++/src/smf/lessons_c_plus_plus/test.txt", std::ofstream::app);

    if(!file.is_open()) {
    } else { 
        file.write((char*)& abc1, sizeof(abc));
    }
}

abc ffstream___2(abc& abc1) {
    std::fstream file;
    file.open("C:/project/projects_g++/src/smf/lessons_c_plus_plus/test.txt");

    if(!file.is_open()) {        
    } else { 
        while (file.read((char*)& abc1, sizeof(abc)));
        {
            abc1.print();
        }
    }
    return abc1;
}

int main() {
    abc a(123, 123.032, 127.361, false, {1,2,3,4}, "adsadad");
    ffstream___1(a);
    ffstream___2(a);
}