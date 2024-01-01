#include <array>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
#define Tuple array<int, 3>

//Time complexity: O(klogk + nlogk). k is the number of arrays, n is the total number of elements in all arrays.
// Constructing the priority queue: The code iterates over each vector in the input vector a 
// and pushes a tuple into the priority queue. This operation takes O(k * log(k))
// Repeatedly extracts the minimum element from the priority queue until it becomes empty. 
// Each extraction takes O(log(k)).There are a total of n elements across all vectors in a,
//  the number of extractions is n. Therefore, this step takes O(n * log(k)) time.
vector<int> pq_mergeSortedArray(vector<vector<int>> a){
    priority_queue<Tuple, vector<Tuple>, greater<Tuple>> pq;
    int k = a.size();
    for (int i = 0; i < k; i++){
        Tuple tuple = {a[i][0], i, 0};
        pq.push(tuple);
    }

    vector<int> ans;
    while (!pq.empty()){
        auto [val, i, j] = pq.top(); pq.pop();
        ans.push_back(val);
        if (j + 1 < a[i].size()){
            pq.push({a[i][j + 1], i, j + 1});
        }
    }
    return ans;
}


int main(){
    vector<vector<int>> a = {{1, 4, 5, 7}, {2, 4, 6, 8}, {0, 9}};
    vector<int> ans = pq_mergeSortedArray(a);
    for (int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }
    return 0;
}
