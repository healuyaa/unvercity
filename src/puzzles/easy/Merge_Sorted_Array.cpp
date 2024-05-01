#include <iostream>
#include <vector>

using std::vector;

// void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
//      if (n == 0)
//     {
//         return;
//     }
//     if (m == 0)
//     {
//         for (size_t i = 0; i < (m + n); i++)
//         {
//             nums1[i] = nums2[i];
//         }
//         return;
//     }     
//     for (size_t i = 0; i < n; i++)
//     {
//         nums1[i + m] = nums2[i];
//     }    
// }

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;

    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }

    while (j >= 0) {
        nums1[k] = nums2[j];
        j--;
        k--;
    }
}

int main() {
    vector<int> nums1 = {4, 0, 0, 0, 0, 0};
    vector<int> nums2 = {1, 2, 3, 5, 6};
    int m = 1;
    int n = 5;
    merge(nums1, m, nums2, n);
    for (size_t i = 0; i < m + n; i++)
    {
        std::cout << nums1[i] << ' ';   
    }
}