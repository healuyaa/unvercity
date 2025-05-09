#include <iostream>
#include <string>
#include <map>

using std::string;

int romanToInt(string s) {
    std::map<char, int> alph = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
            
    int sum = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if(alph[s[i]] < alph[s[i + 1]])
        {
            sum += alph[s[i + 1]] - alph[s[i]];
            i++;
        } else {
            sum += alph[s[i]];
        }
    }
    return sum;
}

int main() {
    string s = "MCMXCIV";
    std::cout << romanToInt(s);
}