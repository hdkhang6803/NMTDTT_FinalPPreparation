#include <iostream>
#include <vector>

using namespace std;

// Do phuc tap: O(V + E)

void dfs(vector<vector<int>>& adj, vector<int>& sub, long long& ans, int u, int p) {
    sub[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(adj, sub, ans, v, u);
        sub[u] += sub[v];
    }
    // sub[u] * (adj.size() - sub[u]) is total weight of edge p - u added to ans
    ans += 1LL * sub[u] * (adj.size() - sub[u]);
}

int main() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    long long ans = 0;
    vector<int> sub(n, 0);
    dfs(adj, sub, ans, 0, -1);
    cout << ans << '\n';
    return 0;
}
