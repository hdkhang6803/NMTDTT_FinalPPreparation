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
}