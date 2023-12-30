#include <iostream>
#include <set>
#include <cmath>

using namespace std;

void solve(int n) {
    int a = -1, b = -1;
    set<int> squares;

    for (int i = 0; i * i <= n; ++i) {
        squares.insert(i * i);

        int complement = n - i * i;
        if (squares.count(complement)) {
            a = i;
            b = static_cast<int>(sqrt(complement));
            break;
        }
    }

    if (a == -1 && b == -1) {
        cout << "Impossible\n";
    } else {
        int x = min(a, b);
        int y = max(a, b);

        cout << x << " " << x << "\n";
        cout << x + y << " " << 0 << "\n";
        cout << 2 * x << " " << x + y << "\n";
        cout << 2 * x + y << " " << y << "\n";
        
    }
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    solve(n);

    return 0;
}


// khong phai hinh vuong nua ?