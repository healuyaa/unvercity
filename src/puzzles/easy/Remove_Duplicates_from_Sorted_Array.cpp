#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int removeDuplicates(vector<int>& nums) {
    vector<int> answer;
    int size = nums.size();
    answer.push_back(nums[0]);
    for (size_t i = 0; i < size - 1; i++)
    {
        if (nums[i] != nums[i + 1])
        {
            answer.push_back(nums[i + 1]);
            continue;
        } else {
            continue;
        }        
    }
    int k = answer.size();
    nums = answer;
    // for (size_t i = nums.size(); i < size; i++)
    // {
    //     nums.push_back(NULL);
    // }    
    return k;
}

int main() {
    vector<int> nums(10);
    for (size_t i = 0; i < 10; i++)
    {
        nums[i] = abs(rand() % 4);
        std::cout << nums[i] << ' ';
    } std::cout << std::endl;
    std::sort(nums.begin(), nums.end());
    std:: cout << removeDuplicates(nums) << std::endl;
    for (size_t i = 0; i < nums.size(); i++)
    {
        std::cout << nums[i] << ' ';
    } std::cout << std::endl;     
}