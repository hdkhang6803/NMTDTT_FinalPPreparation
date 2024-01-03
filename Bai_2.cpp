#include <iostream>
#include <vector>

#include "utils.h"

using namespace std;

// // Do phuc tap: O(n^2 * sqrt(n))

// // Function to calculate gn
// int calculateGn(int n) {
//     int count = 0;
//     cout << "Dang xet n = " << n << endl;
//     for (int p = 2; p <= n; p++) {
//         int q = 2 * n - p;
//         if (isPrime(p) && isPrime(q)) {
//             count++;
//             cout << p << ' ' << q << endl;
//         }
        
//     }

//     return count;
// }

// // Function to calculate fn
// int calculateFn(int n) {
//     int sum = 0;
//     for (int i = 2; i <= n; i++) {
//         sum += calculateGn(i);
//         cout << i << " " << sum << endl;
//     }
//     return sum;
// }

// int main() {
//     int n;
//     cin >> n;
//     int result = calculateFn(n);
//     cout << result << endl;
//     return 0;
// }

// ----------------------------------------------------------------------------------------------------------------

// Do phuc tap: O(n^2) + O(nlog(log(n))) 
// Can be reduced to O(n) by constructing the primes only array

// Function to calculate gn
// int calculateGn(int n, vector<bool> &primesVector) {
//     int count = 0;
//     cout << "Dang xet n = " << n << endl;
//     for (int p = 2; p <= n; p++) {
//         int q = 2 * n - p;

//         if (primesVector[p] == 1 && primesVector[q] == 1) {
//             count++;
//             cout << p << ' ' << q << endl;
//         }
        
//     }

//     return count;
// }

// // Function to calculate fn
// int calculateFn(int n, vector<bool> &primesVector) {
//     int sum = 0;
//     for (int i = 2; i <= n; i++) {
//         sum += calculateGn(i, primesVector);
//     }
//     return sum;
// }

// int main() {
//     int n;
//     cin >> n;

    
//     vector<bool> primesVector = generatePrimes(2 * n);

//     int result = calculateFn(n, primesVector);
//     cout << result << endl;
//     return 0;
// }

// ------------------------------------------------------

// Do phuc tap: O(n^2 / log2(n))

// Phuong phap khac ngoai cach tinh gn va fn:
int cnt = 0;
int main() {
    int n;
    cin >> n;

    vector<bool> primesVector = generatePrimes(2 * n);
    vector<int> primes;
    
    for (int i = 2; i <= 2 * n; i++) {
        if (primesVector[i] == 1) {
            primes.push_back(i);
        }
    }

    vector<int> g(n + 1, 0);
    for (int i = 0; i < primes.size(); i++){
        for (int j = i; j < primes.size(); j++){
            int cur = primes[i] + primes[j];
            if (cur % 2 == 0 && cur <= 2 * n){
                g[cur / 2]++;
                cnt++;
            }


        }
    }

    int result = 0;
    for (int i = 2; i <= n; i++){
        result += g[i];
    }

    cout << result << ' ' << cnt << endl;
    return 0;
}