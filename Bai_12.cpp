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

        cout << 0 << " " << 0 << "\n";
        cout << x << " " << y << "\n";
        cout << x + y << " " << y-x << "\n";
        cout << y << " " << -x << "\n";
        
    }
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    solve(n);

    return 0;
}


// Bien the: khong phai hinh vuong nua ?

// Bien the: dem so luong hinh vuong