#include <iostream>
#include <string>
#include <stack>

using std::string;

int comp() {}

bool isValid(string s) {
    std::stack<char> symb;
    for(char c: s) {
        if (c == '(' || c == '{' || c == '[')
        {
            symb.push(c);
        } else {
            if (symb.empty())
            {
                return false;
            }
            if (c == ')' && symb.top() == '(')
            {
                symb.pop();
            } else if (c == '}' && symb.top() == '{')
            {
                symb.pop();
            } else if (c == ']' && symb.top() == '[')
            {
                symb.pop();
            } else {
                return false;
            }            
        }
    }
    return symb.empty();         
}

int main() {
    string s = "{[]}";
    std::cout << isValid(s);
}