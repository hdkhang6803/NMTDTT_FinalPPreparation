#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

struct CompareWeight {
    bool operator()(Edge const& p1, Edge const& p2)
    {
        return p1.weight > p2.weight;
    }
};

void print_tree(vector<Edge> mst){
    for (const auto& edge : mst) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
    }
}
// Function to find the minimum spanning tree using Prim's algorithm
vector<Edge> findMinimumSpanningTree(vector<vector<int>>& graph) {
    int V = graph.size();

    // Priority queue to store the edges
    priority_queue<Edge, vector<Edge>, CompareWeight> pq;

    // Start with vertex 0
    int startVertex = 0;

    // Create a vector to track visited vertices
    vector<bool> visited(V, false);

    // Create a vector to store the minimum spanning tree
    vector<Edge> mst;

    // Mark the start vertex as visited
    visited[startVertex] = true;

    // Add all the edges from the start vertex to the priority queue
    for (int i = 0; i < V; i++) {
        if (graph[startVertex][i] != 0) {
            pq.push({startVertex, i, graph[startVertex][i]});
        }
    }

    // Loop until all vertices are visited
    while (!pq.empty()) {
        // Get the edge with the minimum weight
        Edge minEdge = pq.top();
        pq.pop();

        int src = minEdge.src;
        int dest = minEdge.dest;
        int weight = minEdge.weight;

        // If the destination vertex is already visited, skip this edge
        if (visited[dest]) {
            continue;
        }

        // Mark the destination vertex as visited
        visited[dest] = true;

        // Add the edge to the minimum spanning tree
        mst.push_back({src, dest, weight});

        // Add all the edges from the destination vertex to the priority queue
        for (int i = 0; i < V; i++) {
            if (graph[dest][i] != 0 && !visited[i]) {
                pq.push({dest, i, graph[dest][i]});
            }
        }
    }
    return mst;
}

vector<vector<int>> constructMSTMatrix(vector<Edge>& mst, int numVertices) {
    vector<vector<int>> mstMatrix(numVertices, vector<int>(numVertices, 0));
    
    for (const auto& edge : mst) {
        mstMatrix[edge.src][edge.dest] = edge.weight;
        mstMatrix[edge.dest][edge.src] = edge.weight;
    }
    
    return mstMatrix;
}

void dfs_mst(vector<vector<int>> mstMatrix, vector<int>& visited, int i = 0){
    if(visited[i] == 1) return;
    visited[i] = 1;
    for(int j = 0; j < mstMatrix.size(); j++){
        if(mstMatrix[i][j] != 0 && i != j){
            dfs_mst(mstMatrix, visited, j);
        }
    }
}



int return_K_mst(vector<vector<int>> graph, int k){
    vector<Edge> mst = findMinimumSpanningTree(graph); //Tốn O(ElogE + VlogV)
    print_tree(mst);
    vector<vector<int>> mstMatrix = constructMSTMatrix(mst, graph.size()); //Tốn O(E)

    int n = mst.size();
    int cnt = 0;
    while (cnt < k)
    {
        for(int i = 0; i < n; i++){
            Edge del_e = mst.back();
            mst.pop_back();
            mstMatrix[del_e.src][del_e.dest] = 0;
            mstMatrix[del_e.dest][del_e.src] = 0;
            graph[del_e.src][del_e.dest] = 0;
            graph[del_e.dest][del_e.src] = 0;
            vector<int> visited(graph.size(), 0);
            dfs_mst(mstMatrix, visited);
            vector<int> tplt_1;
            vector<int> tplt_2;
            for(int i = 0; i < visited.size(); i++){
                if(visited[i] == 1){
                    tplt_1.push_back(i);
                }
                else{
                    tplt_2.push_back(i);
                }
            }
            for(int i = 0; i < tplt_1.size(); i++){
                for(int j = 0; j < graph.size(); j++){
                    //Đi tìm cạnh tiếp theo
                }
            }

            mstMatrix[del_e.src][del_e.dest] = 1;
            mstMatrix[del_e.dest][del_e.src] = 1;
            graph[del_e.src][del_e.dest] = 1;
            graph[del_e.dest][del_e.src] = 1;

            
        }
    }
    
    return 0;
}

int main() {
    // Example usage
    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    vector<Edge> mst = findMinimumSpanningTree(graph);

    // Print the minimum spanning tree
    cout << "Minimum Spanning Tree:" << endl;
    for (const auto& edge : mst) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
    }

    return 0;
}
