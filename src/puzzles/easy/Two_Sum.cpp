#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> answer;
        for (size_t i = 0; i < nums.size(); i++)
        {           
            for (size_t k = i + 1; k < nums.size(); k++)
            {
                int probably = target - nums[i];
                if(probably == nums[k]) {
                    answer.push_back(i);
                    answer.push_back(k);
                }               
            }                       
        }
        
        for(auto a: answer) {
            std::cout << a << ' ';
        }
        return answer;       
    }
};

int main() {
    vector<int> test = {-3, 4, 3, 90};
    int target = 0;
    Solution app;
    app.twoSum(test, target);

}