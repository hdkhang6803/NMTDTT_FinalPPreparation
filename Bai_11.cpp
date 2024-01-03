/**
 *    author:    hungt1
 *    created:   30-12-2022   20:48:23
 * https://github.com/vanloc1808/algorithms-thinking-final/blob/master/src/P11.cpp
**/

#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

int N3_maxClustersWeight (int k, int n, int m, vector<int> a, vector<int> b){
    int t = k - n - m;
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(t + 1, 0)));
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            for (int l = 0; l <= t; l++){
                int idx = i + j + l; // 0-based
                if (i + 1 <= n) dp[i + 1][j][l] = max(dp[i + 1][j][l], dp[i][j][l] + a[idx]);
                if (j + 1 <= m) dp[i][j + 1][l] = max(dp[i][j + 1][l], dp[i][j][l] + b[idx]);
                if (l + 1 <= t) dp[i][j][l + 1] = max(dp[i][j][l + 1], dp[i][j][l]);
            }
        }
    }
    cout << dp[n][m][t] << '\n';
    return dp[n][m][t];
}

//Cách 2: Dùng mảng 2 chiều
//dp[i][j]: Đã duyệt tới i cluster và đã chọn j nhóm b
int N2_maxClustersWeight (int k, int n, int m, vector<pair<int,int>> cluster){
    sort(cluster.begin(), cluster.end(), greater<pair<int,int>>());
    vector<vector<int>> dp(cluster.size() + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= k; i++){
        for (int j = 0; j <= m; j++){
            if (i <= j + n){ // Số lượng nhóm a đã chọn không quá n
                if (j - 1 >=0 && i == j){ //Các đỉnh đã xét bằng với số đỉnh nhóm b đã chọn
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1] + cluster[i-1].second); //Vậy trạng thái khi xét đỉnh u - 1 phải chọn thêm nhóm b
                }
                else if( i > j) // 0 < i - j <= n: đã có chọn b nhưng ko suy luận thêm được thông tin gì
                {
                    if (j > 0){
                        dp[i][j] = max(dp[i][j], dp[i-1][j-1] + cluster[i-1].second);
                    }
                    dp[i][j] = max(dp[i][j], dp[i-1][j] + cluster[i-1].first);
                    dp[i][j] = max(dp[i][j], dp[i-1][j]);
                }
            }
            else{ //i > j + n: đã chọn đủ nhóm a => không thêm nhóm a vào nữa
                if(i - 1 >= 0){
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1] + cluster[i-1].second);
                }
                dp[i][j] = max(dp[i][j], dp[i-1][j]);
            }
        }
    }
    
    cout << dp[k][m] << '\n';
    return dp[k][m];
}

int main()
{
    fastio;
    int k, n, m; cin >> k >> n >> m;
    vector<int> a(k), b(k);
    vector<pair<int, int>> cluster(k);
    for (int i = 0; i < k; i++){
        cin >> a[i] >> b[i];
        cluster.push_back(make_pair(a[i], b[i]));
    }

    N3_maxClustersWeight(k, n, m, a, b);
    N2_maxClustersWeight(k, n, m, cluster);
    
    
    return 0;
}