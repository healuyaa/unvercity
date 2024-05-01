#include <iostream>
#include <vector>

std::vector<int> sort_straight(std::vector<int> arr) {
    int x, j;
    for (size_t i{2}; i < arr.size() - 1; ++i)
    {
        x = arr[i];
        arr[0] = x;
        j = i - 1;
        while(x != arr[j]) {
            arr[j + 1] = arr[j]; 
            j -= 1;
        }
        arr[j + 1] = x;
    }   
    return arr;
}

int main() {
    std::vector<int> arr = {6,7,9,4,5};
    auto result = sort_straight(arr);
    for (auto& item : result){
        std::cout << item << " ";
    }
}