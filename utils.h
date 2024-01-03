#pragma once

#include <vector>
#include <functional>
#include <cassert>
#include <math.h>

using namespace std;

#define ULLONG unsigned long long int 

struct Point {
    int x;
    int y;
};

int gcd(int a, int b);
int upper(vector<int> a, int x, int lo, int hi);
int lower(vector<int> a, int x, int lo, int hi);
int BinarySearch(vector<int> a, int x);


bool isPrime(int num);
std::vector<bool> generatePrimes(int n);

// Binary Indexed Tree (BIT) implementation
class BIT {
private:
    std::vector<int> tree;

public:
    BIT(int size) {
        tree.resize(size + 1, 0);
    }

    void update(int index, int value) {
        while (index < tree.size()) {
            tree[index] += value;
            index += index & -index;
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }
};


#define fastio ios_base::sync_with_stdio(false); cin.tie(0)

// tourist template
template <typename T, typename func = function<T(const T, const T)>>
struct SparseTable {
    func calc;
    int n;
    vector<vector<T>> ans;

    SparseTable() {}

    SparseTable(const vector<T>& a, const func& f) : n(a.size()), calc(f) {
        int last = trunc(log2(n)) + 1;
        ans.resize(n);
        for (int i = 0; i < n; i++){
            ans[i].resize(last);
        }
        for (int i = 0; i < n; i++){
            ans[i][0] = a[i];
        }
        for (int j = 1; j < last; j++){
            for (int i = 0; i <= n - (1 << j); i++){
                ans[i][j] = calc(ans[i][j - 1], ans[i + (1 << (j - 1))][j - 1]);    
            }
        }
    }

    T query(int l, int r){
        assert(0 <= l && l <= r && r < n);
        int k = trunc(log2(r - l + 1));
        return calc(ans[l][k], ans[r - (1 << k) + 1][k]);
    }
};

int checkOnLine(Point p1, Point p2, Point p);