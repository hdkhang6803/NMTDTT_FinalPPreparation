#include <iostream>
#include <vector>

using namespace std;

// Do phuc tap: tim cau O(E + V)
//              tim dinh co the toi O(E + V)
//              tong do phuc tap O(E(E + V))

void dfs(int node, int parent, int& timer, vector<bool>& visited, vector<int>& tin, vector<int>& low, vector<vector<int>>& graph, vector<pair<int, int>>& bridges) {
    visited[node] = true;
    tin[node] = low[node] = timer++;
    for (int neighbor : graph[node]) {
        if (neighbor == parent) {
            continue;
        }
        if (visited[neighbor]) {
            low[node] = min(low[node], tin[neighbor]);
        } else {
            dfs(neighbor, node, timer, visited, tin, low, graph, bridges);
            low[node] = min(low[node], low[neighbor]);
            if (low[neighbor] > tin[node]) {
                bridges.push_back({node, neighbor});
            }
        }
    }
}

void findBridges(vector<vector<int>>& graph, vector<pair<int, int>>& bridges) {
    int N = graph.size() - 1;
    vector<bool> visited(N + 1, false);
    vector<int> tin(N + 1, -1);
    vector<int> low(N + 1, -1);
    int timer = 0;

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i, -1, timer, visited, tin, low, graph, bridges);
        }
    }
}

void dfsCount(int node, int parent, int& count, vector<bool>& visited, vector<vector<int>>& graph) {
    visited[node] = true;
    count++;
    for (int neighbor : graph[node]) {
        if (neighbor == parent || visited[neighbor]) {
            continue;
        }
        dfsCount(neighbor, node, count, visited, graph);
    }
}

void dfsMark(int node, int parent, int& number, vector<bool>& visited, vector<int>& nodeNumbers, vector<vector<int>>& graph, vector<pair<int, int>>& bridges) {
    visited[node] = true;
    nodeNumbers[node] = number;
    for (int neighbor : graph[node]) {
        if (neighbor == parent) {
            continue;
        }
        if (visited[neighbor]) {
            continue;
        }
        bool isBridge = false;
        for (const auto& bridge : bridges) {
            if ((bridge.first == node && bridge.second == neighbor) || (bridge.first == neighbor && bridge.second == node)) {
                isBridge = true;
                break;
            }
        }
        if (isBridge) {
            number++;
        }
        dfsMark(neighbor, node, number, visited, nodeNumbers, graph, bridges);
    }
}

void markNodesWithNumbers(vector<vector<int>>& graph, vector<pair<int, int>>& bridges, vector<int>& nodeNumbers) {
    int N = graph.size() - 1;
    vector<bool> visited(N + 1, false);
    int number = 1;

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfsMark(i, -1, number, visited, nodeNumbers, graph, bridges);
        }
    }
}


void dfsSubtree(vector<vector<int>>& adj, vector<int>& sub, int u, int p) {
    sub[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfsSubtree(adj, sub, v, u);
        sub[u] += sub[v];
    }
    // sub[u] * (adj.size() - sub[u]) is total weight of edge p - u added to ans
    // ans += 1LL * sub[u] * (adj.size() - sub[u]);
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 1);
    vector<pair<int, int>> edges; // Store edges (u, v)

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back({u, v}); // Store the edge (u, v)
    }

    vector<pair<int, int>> bridges;
    findBridges(graph, bridges);
    vector<bool> visited(N + 1, false);
    int number = 1;

    vector<int> nodeNumber(N);

    dfsMark(1, -1, number, visited, nodeNumber, graph, bridges);

    // for (int i = 0; i < M; i++) {
    //     int u = edges[i].first;
    //     int v = edges[i].second;

    //     bool isBridge = false;
    //     for (const auto& bridge : bridges) {
    //         if ((bridge.first == u && bridge.second == v) || (bridge.first == v && bridge.second == u)) {
    //             isBridge = true;
    //             break;
    //         }
    //     }

    //     if (isBridge) {
    //         int x = 0;
    //         vector<bool> visited(N + 1, false);

    //         dfsCount(u, v, x, visited, graph);
    //         int n = N - x;
    //         result[i] = x * n;
    //     } else {
    //         result[i] = 0;
    //     }
    // }

    // Print the results
    // for (int i = 1; i <= N; i++) {
    //     cout << i << ' ' << nodeNumber[i] << endl;
    // }

    vector<vector<int>> graph2(N + 1);
    for (int i = 1; i <= M; i++) {
        // int u = edges[i].first;
        // int v = edges[i].second;

        int u = nodeNumber[bridges[i].first];
        int v = nodeNumber[bridges[i].second];

        graph2[u].push_back(v);
        graph2[v].push_back(u);
    }

    vector<int> sub(N + 1);
    dfsSubtree(graph2, sub, 1, -1);

    for (int i = 1; i <= M; i++) {
        cout << i << "\n";
        int u = nodeNumber[bridges[i].first];
        int v = nodeNumber[bridges[i].second];

        cout << u << ' ' << v << ' ' << sub[u] * (N - sub[u]) << endl;
    }


    return 0;
}
