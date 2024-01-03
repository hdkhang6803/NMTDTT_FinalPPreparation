#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "utils.h" // Include the header file for utility functions

using namespace std;

//Naive function for the problem
//Complexity
//Time: O(n*k)
//Space: O(1)
int naive_findLargestGCDSubarray(const std::vector<int>& arr, int k){
    int n = arr.size();
    int max_gcd = 1;
    for(int i = 0; i < n - k + 1; i++){
        int currentGCD = arr[i];
        for(int j = i + 1; j < i + k; j++){
            currentGCD = gcd(currentGCD, arr[j]);
        }
        if(currentGCD > max_gcd){
            max_gcd = currentGCD;
        }
    }
    return max_gcd;
}

//Expand the problem such that k elements are not necessarily consecutive
//Có mảng count với count[i] là số lần phần tử của mảng a có ước là i
//Với mỗi giá trị a[i], ta lần lượt duyệt từ 1 tới sqrt(a[i]) để tìm các ước của a[i]
//Sau đó tăng count[ước] lên 1 đơn vị
//Sau khi duyệt xong, ta duyệt từ cuối mảng count về đầu mảng để tìm ước lớn nhất có count[ước] >= k. 
//Lúc đó ước đó chính là kết quả của bài toán (ước chung lớn nhất của k phần tử trong mảng)
// function to find GCD of sub sequence of 
// size k with max GCD in the array 
//Source: https://www.geeksforgeeks.org/subsequence-of-size-k-with-maximum-possible-gcd/
int findMaxGCD(int arr[], int n, int k) 
{ 
    // Computing highest element 
    int high = *max_element(arr, arr+n); 
  
    // Array to store the count of divisors 
    // i.e. Potential GCDs 
    int divisors[high + 1] = { 0 }; 
  
    // Iterating over every element 
    for (int i = 0; i < n; i++) { 
  
        // Calculating all the divisors 
        for (int j = 1; j <= sqrt(arr[i]); j++) { 
  
            // Divisor found 
            if (arr[i] % j == 0) { 
  
                // Incrementing count for divisor 
                divisors[j]++; 
  
                // Element/divisor is also a divisor 
                // Checking if both divisors are not same 
                if (j != arr[i] / j) 
                    divisors[arr[i] / j]++; 
            } 
        } 
    } 
  
    // Checking the highest potential GCD 
    for (int i = high; i >= 1; i--) 
        // If this divisor can divide at least k 
        // numbers, it is a GCD of at least one 
        // sub sequence of size k 
        if (divisors[i] >= k) 
            return i; 
    return 1;
} 

// //Using sparseTable
int findMaxGCD_ST(vector<int> a, int n, int k){
    SparseTable<int> st(a, [](int x, int y){
        return gcd(x, y);
    });

    int ans = 0;
    for (int i = 0; i < n - k + 1; i++){
        int cur = st.query(i, i + k - 1);
        if (cur > ans) ans = cur;
    }
    cout << ans << '\n';
    return 0;
}

int main() {
    int n, k;
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;
    std::cout << "Enter the value of k: ";
    std::cin >> k;

    std::vector<int> arr(n);
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    cout << "Naive maximum gcd: " << naive_findLargestGCDSubarray(arr, k) << endl;

    cout << "Maximum GCD of non-consecutive elements: " << findMaxGCD(arr.data(), n, k) << endl;

    cout << "Maximum GCD of non-consecutive elements (using sparse table): " << findMaxGCD_ST(arr, n, k) << endl;

    return 0;
}
