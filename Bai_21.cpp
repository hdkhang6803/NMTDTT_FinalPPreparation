#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Function to find the minimum spanning tree using Prim's algorithm
vector<Edge> findMinimumSpanningTree(vector<vector<int>>& graph) {
    int V = graph.size();

    // Priority queue to store the edges
    priority_queue<Edge, vector<Edge>, function<bool(Edge, Edge)>> pq(
        [](Edge a, Edge b) {
            return a.weight > b.weight;
        }
    );

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
