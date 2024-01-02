#pragma once

#include <vector>

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

int checkOnLine(Point p1, Point p2, Point p);