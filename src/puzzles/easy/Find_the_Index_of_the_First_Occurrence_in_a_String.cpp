#include <iostream>
#include <string>

using std::string;

int strStr(string haystack, string needle) {
    size_t index = haystack.size();
    size_t maxValue = index;
    string answer;
    while (index != 0)
    {
        answer.insert(0, haystack, 0, needle.size());
        if (needle == answer)
        {
            return maxValue - index;
        }
        answer.clear();
        haystack.erase(0,1);        
        index--;   
    }
    return -1;
}

int main() {
    string haystack = "hello";
    string needle = "ll";
    std::cout << strStr(haystack, needle);
}