#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <tuple>
#include "utils.h" // Include the header file for utility functions

using namespace std;

//naive algorithm
//Vì n nhỏ (10^3) nên có thể cố định 1 điểm, duyệt qua từng điểm trong mảng và xây dựng đường thẳng với điểm đó.
//Sau đó kiểm tra từng điểm còn lại nằm về phía nào của đường thẳng 
//Time complexity: O(n^2)
pair<int, int> naive_findPoints(vector<Point> points){
    int n = points.size();
    int max_count = 0;
    Point p1 = points[0];
    for(int j = 1; j < n; j++){
        Point p2 = points[j];
        int count = 0;
        for(int i = 1;  i < n; i++){
            if (i == j) continue;
            Point p = points[i];
            if (checkOnLine(p1, p2, p) > 0){
                count++;
            }
        }
        if (n - count - 2 == count){
            return make_pair(0,j);
        }
    }
    return make_pair(-1,-1);
}

//Better solution: Use angle to bottom left point
//Time complexity: O(nlogn)
pair<int, int> angleBased_findPoints(vector<Point> points){
    int n = points.size();
    //find leftmost (bottomost) point
    Point most_x = points[0];
    int idx_most_x = 0;
    for(int i = 0; i < n; i++){
        if (points[i].x < most_x.x){
            most_x = points[i];
            idx_most_x = i;
        }
        if (points[i].x == most_x.x){
            if (points[i].y < most_x.y){
                most_x = points[i];
                idx_most_x = i;
            }
        }
    }
    
    //calculate alpha from other points to most_x
    vector<pair<double, int>> alpha;
    for(int i = 0; i < n; i++){
        if (points[i].x == most_x.x && points[i].y == most_x.y) continue;
        double a = 1.0 * (points[i].y - most_x.y) / (points[i].x - most_x.x);
        alpha.push_back(make_pair(a, i));
    }

    //Sort alpha ascendingly
    sort(alpha.begin(), alpha.end());
    //find median of alpha
    pair<double,int> median = alpha[alpha.size()/2];
    return make_pair(idx_most_x,median.second);
}

int main(){
    int n;
    cin >> n;
    vector<Point> points;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        Point p;
        p.x = x;
        p.y = y;
        points.push_back(p);
    }
    pair<int, int> res = naive_findPoints(points);
    cout << "res: " << res.first + 1 << " " << res.second + 1 << endl;
    pair<int, int> res2 = angleBased_findPoints(points);
    cout << "res2: " << res2.first + 1 << " " << res2.second + 1 << endl;

    return 0;
}
