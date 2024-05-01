#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

string convert(string s, int numRows) {
    string answer;
    string temp_s;
    vector<string> temporary;
    int size_s_iter = s.size() / (numRows - 1);
    int size_s_iter_last = s.size() % (numRows - 1);    

    for (size_t i = 0; i < size_s_iter; i++)
    {
        temp_s.insert(0, s, 0, numRows - 1);
        temporary.push_back(temp_s);        
        temp_s.clear();
        s.erase(0, numRows - 1);
    }
    temp_s.insert(0, s, 0, size_s_iter_last);
    temporary.push_back(temp_s);    
    temp_s.clear();
    s.erase(0, size_s_iter_last);

    // P     I    N
    // A   L S  I G
    // Y A   H R
    // P     I

    // int iter_answer_i = 0;
    // int iter_answer_j = 0;
    // while(!temporary.empty()) {
    //     answer.push_back(temporary[iter_answer_i][iter_answer_j]);

    // }

    return answer;
}

int main() {
    int numRows = 4;
    string s = "PAYPALISHIRING";
    convert(s, numRows);
}