#include <bits/stdc++.h>

using namespace std;

// Do phuc tap: O(N^2)

void calcFactorial(vector<long long>& fact, int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
    }
}

void readInput(vector<int>& a, int& n, int& y) {
    int t;

    vector<int> tmp;
    while (cin >> t) {
        tmp.push_back(t);
    }

    y = tmp.back(); 
    tmp.pop_back();

    a = tmp;
    n = tmp.size();
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    vector<int> a;
    int y;

    readInput(a, n, y);
    
    vector<long long> fact(n + 1, 1);
    calcFactorial(fact, n);

    long long res = 0;
    vector<bool> used(n + 1, 0);
    for (int i = 0; i < n; i++){
        int cnt = 0;
        for (int x = 1; x < a[i]; x++){
            if (!used[x]) cnt++;
        }
        res += cnt * fact[n - i - 1];
        used[a[i]] = true;
    }

    y--;
    vector<int> per;
    used.assign(n + 1, 0);
    for (int i = 0; i < n; i++){
        int cnt = 0;
        for (int x = 1; x <= n; x++){
            if (used[x]) continue;
            if (cnt == y / fact[n - i - 1]) {
                per.push_back(x);
                used[x] = true;
                break;
            }
            cnt++;
        }
        y %= fact[n - i - 1];
    }   

    cout << res + 1 << '\n';
    for (int x : per) cout << x << ' '; cout << '\n';
}

