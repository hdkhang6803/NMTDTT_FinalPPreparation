#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "utils.h" // Include the header file for utility functions


using namespace std;

pair<int, int> solve(vector<pair<long long, int>> a, vector<pair<long long, int>> b){
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int n = a.size();
    int m = b.size();

    
    int aidx = 0;
    int bidx = 0;
    int minDiff = INT_MAX;
    if (a[0].first >=0 && b[0].first >= 0){
        return make_pair(a[0].second, b[0].second);
    }else if (a[a.size() - 1].first <= 0 && b[b.size() - 1].first <= 0){
        return make_pair(a[a.size() - 1].second, b[b.size() - 1].second);
    }else {
        
        for(int i = 0; i < n; i++){
            //Get the first element that is not less than -a[i].first
            vector<pair<long long, int>>::iterator it = lower_bound(b.begin(), b.end(), make_pair(-a[i].first, 0)); 
            if (it != b.end()){
                int pos = it - b.begin();
                if (b[pos].first == -a[i].first){
                    return make_pair(i, pos);
                }
                else if (pos >= 0){
                    //check the lower bound sum with the before-lower bound sum
                    if (pos != 0 && abs(b[pos].first + a[i].first) > abs(b[pos - 1].first + a[i].first)){
                        if (abs(b[pos - 1].first + a[i].first) < minDiff){
                            minDiff = abs(b[pos - 1].first + a[i].first);
                            aidx = i;
                            bidx = pos - 1;
                        }
                    }else{
                        if (abs(b[pos].first + a[i].first) < minDiff){
                            minDiff = abs(b[pos].first + a[i].first);
                            aidx = i;
                            bidx = pos;
                        }
                    }
                }
            }else{
                int pos = it - b.begin() - 1;
                if (abs(b[pos].first + a[i].first) < minDiff){
                    minDiff = abs(b[pos].first + a[i].first);
                    aidx = i;
                    bidx = pos;
                }
            }
        }
    }
    cout << "sum" << abs(a[aidx].first + b[bidx].first) << endl;
    return make_pair(a[aidx].second, b[bidx].second);
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<pair<long long, int>> a;
    vector<pair<long long, int>> b;
    for(int i = 0; i < n; i++){
        long long x;
        cin >> x;
        a.push_back(make_pair(x, i + 1));
    }
    for(int i = 0; i < m; i++){
        long long x;
        cin >> x;
        b.push_back(make_pair(x, i + 1));
    }

    pair<int, int> res = solve(a, b);
    cout << res.first << " " << res.second << endl;
    return 0;
}