#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.h"

using namespace std;

// Phuong phap: dem bang Merge sort
// Do phuc tap: O(nlog(n))

// long long merge(std::vector<int>& arr, int left, int mid, int right) {
//     std::vector<int> temp(right - left + 1);
//     int i = left, j = mid + 1, k = 0;
//     long long count = 0;

//     while (i <= mid && j <= right) {
//         if (arr[i] > arr[j]) {
//             count += mid - i + 1;
//             temp[k++] = arr[j++];
//         } else {
//             temp[k++] = arr[i++];
//         }
//     }

//     while (i <= mid) {
//         temp[k++] = arr[i++];
//     }

//     while (j <= right) {
//         temp[k++] = arr[j++];
//     }

//     std::copy(temp.begin(), temp.end(), arr.begin() + left);

//     return count;
// }

// long long mergeSort(std::vector<int>& arr, int left, int right) {
//     long long count = 0;

//     if (left < right) {
//         int mid = left + (right - left) / 2;
//         count += mergeSort(arr, left, mid);
//         count += mergeSort(arr, mid + 1, right);
//         count += merge(arr, left, mid, right);
//     }

//     return count;
// }

// int main() {
//     int n;
//     std::cin >> n;

//     std::vector<int> arr(n);
//     for (int i = 0; i < n; i++) {
//         std::cin >> arr[i];
//     }

//     long long count = mergeSort(arr, 0, n - 1);
//     std::cout << count << std::endl;

//     return 0;
// }

// ----------------------------------------------------------------------------------------------------------------

// Phuong phap: su dung binary indexed tree + anh xa gia tri (do ai co the am)
// O(logn)

// int countInversePairs(vector<int>& nums) {
//     int n = nums.size();
//     vector<int> sortedNums = nums;
//     sort(sortedNums.begin(), sortedNums.end());

//     BIT bit(n);
//     vector<int> mapping(n);

//     for (int i = 0; i < n; i++) {
//         mapping[i] = lower_bound(sortedNums.begin(), sortedNums.end(), nums[i]) - sortedNums.begin() + 1;
//     }

//     int count = 0;
//     for (int i = n - 1; i >= 0; i--) {
//         count += bit.query(mapping[i] - 1);
//         bit.update(mapping[i], 1);
//     }

//     return count;
// }

// int main() {
//     int n;
//     cin >> n;

//     vector<int> nums(n);
//     for (int i = 0; i < n; i++) {
//         cin >> nums[i];
//     }

//     int result = countInversePairs(nums);
//     cout << result << endl;

//     return 0;
// }


// Bien the: có thêm k: cặp số ai và aj trong dãy thỏa điều kiện i < j và ai > aj và j - i <= k
// -> merge sort khó làm
// BIT dễ làm hơn 


// Bien the: co the k va ak: đếm số bộ ba ai aj ak  thỏa điều kiện i < j < k và ai > aj > ak
