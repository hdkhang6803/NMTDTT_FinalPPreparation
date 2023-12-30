#include "utils.h"


//the time complexity: O(log(a + b)).
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


int upper(vector<int> a, int x, int lo, int hi) {
    int pos = -1;
    while (lo <= hi) {
        int m = (lo + hi)/2;
        if (a[m] <= x) {
            if (a[m] == x) pos = m;
            lo = m+1;
        }
        else hi = m-1;
    }
    return pos;
}

int lower(vector<int> a, int x, int lo, int hi) {
    int pos = -1;
    while (lo <= hi) {
        int m = (lo + hi)/2;
        if (a[m] >= x) {
            if (a[m] == x) pos = m;
            hi = m-1;
        }
        else lo = m+1;
    }
    return pos;
}

int BinarySearch(vector<int> a, int x){
    int lo = 0;
    int hi = a.size() - 1;
    while (lo <= hi){
        int m = (lo + hi)/2;
        if (a[m] == x) return m;
        else if (a[m] < x) lo = m + 1;
        else hi = m - 1;
    }
    return -1;
}#include "utils.h"


// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}


// Function to generate prime numbers up to n using Sieve of Eratosthenes
std::vector<bool> generatePrimes(int n) {
    std::vector<bool> isPrime(n + 1, true);
    
    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }
    
    return isPrime;
}
