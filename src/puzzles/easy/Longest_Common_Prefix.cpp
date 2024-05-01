#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;

string longestCommonPrefix(vector<string>& strs) {
    string ans="";
    std::sort(strs.begin(), strs.end());
    int n = strs.size();
    string first = strs[0], last = strs[n - 1];

    for(int i = 0; i < std::min(first.size(), last.size()); i++){
        if(first[i] != last[i]){
            return ans;
        }
        ans += first[i];
    }                      
}

int main() {
    vector<string> strs = {"flower", "flow", "flight"};
    std::cout << longestCommonPrefix(strs);
}