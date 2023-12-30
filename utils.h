
#ifndef UTILS_H
#define UTILS_H

#include <vector>

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

#endif // UTILS_H
