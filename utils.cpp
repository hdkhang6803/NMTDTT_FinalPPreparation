#include "utils.h"


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
