/**
 *    author:    hungt1
 *    created:   01-01-2023   13:17:39
 *    Source: https://github.com/vanloc1808/algorithms-thinking-final/blob/master/src/P19.cpp
**/

#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false); cin.tie(0)

const long long INF = 1e18;
const int N = 1e5 + 1;
int n;
long long T, a[N], sum[N];


//Time complexity: O(n^2.logn)
int main()
{
    fastio;
    cin >> n >> T;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    long long low = -INF / n, high = *min_element(a + 1, a + n + 1);
    
    auto calc = [&](long long n) -> long long { //calculate the block that can not be digged
        return n * (n + 1) / 2;
    };

    auto check = [&](long long x) -> bool {
        // cout << x << endl;
        long long minCost = INF;
        int l = 1, r = 1;
        for (int i = 1; i <= n; i++){
            r = max(r, i);
            while (l < i && a[l + 1] <= (x + (i - l))) l++; //l tới được vị trí chiều cao cần có để đào xuống độ sâu x
            while (r < n && a[r + 1] > (x + (r - i + 1))) r++; //r tới được vị trí chiều cao cần có để đào xuống độ sâu x. 
            long long curCost = -x * (r - l + 1) + sum[r] - sum[l - 1] - calc(i - l) - calc(r - i);
            //x * (r - l + 1): This is the total amount of digging needed to get all blocks from l to r to the depth x. The negative sign is because the depth is negative.
            //sum[r] - sum[l - 1]: This is the total height of the blocks from l to r before any digging. 
            //calc(i - l): This is the total height of the blocks that can't be dug because they are to the left of the block i
            //calc(r - i): This is the total height of the blocks that can't be dug because they are to the right of the block i
            //sum[r] - sum[l - 1] - calc(i - l) - calc(r - i): Số block phảo dig để đưa block i về độ cao 0
            minCost = min(minCost, curCost);
        }
        return minCost <= T;
    };
    
    long long ans = high;
    while (low <= high){
        long long mid = (low + high) / 2;
        if (check(mid)){
            ans = mid;
            high = mid - 1;
        }
        else low = mid + 1;
    }

    cout << ans << '\n';
    return 0;
}
