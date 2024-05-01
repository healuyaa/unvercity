#include <iostream>
#include <vector>

using std::vector;

int removeElement(vector<int>& nums, int val) {
    int i = 0;
    while (i < nums.size()) {
        if (nums[i] == val) {
            nums.erase(nums.begin() + i);
        } else {
            i++;
        }
    }
    int k = nums.size();
    return k;    
}

int main() {
    vector<int> nums(10);
    for (size_t i = 0; i < 10; i++)
    {
        nums[i] = abs(rand() % 4);
        std::cout << nums[i] << ' ';
    } std::cout << std::endl;

    std::cout << removeElement(nums, 0) << std::endl;
    for (size_t i = 0; i < nums.size(); i++)
    {
        std::cout << nums[i] << ' ';
    } std::cout << std::endl;   
}