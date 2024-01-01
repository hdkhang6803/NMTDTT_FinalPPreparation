#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

const long long INF = numeric_limits<long long>::max();

// Do phuc tap: O(n)

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
};

long long calculatePolygonArea(const vector<Point> &polygon) {
    long long area = 0;
    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        area += 1LL * (polygon[i].x - polygon[(i + 1) % n].x) * (polygon[i].y + polygon[(i + 1) % n].y);
    }
    return abs(area);
}

long long calculateTriangleArea(const Point &a, const Point &b, const Point &c) {
    return abs((b.x - a.x) * (b.y + a.y) + (c.x - b.x) * (c.y + b.y) + (a.x - c.x) * (a.y + c.y));
}

pair<int, int> findOptimalLineSegment(const vector<Point> &polygon) {
    int n = polygon.size();
    long long totalArea = calculatePolygonArea(polygon);
    
    int first = 0, second = 1;
    long long currentArea = 0, minAreaDifference = INF;

    for (int i = 0, j = 1; i < n; i++) {
        while (currentArea < totalArea - currentArea) {
            if (abs(totalArea - 2 * currentArea) < minAreaDifference) {
                minAreaDifference = abs(totalArea - 2 * currentArea);
                first = i;
                second = j;
            }
            currentArea += calculateTriangleArea(polygon[i], polygon[j], polygon[(j + 1) % n]);
            j = (j + 1) % n;
        }

        if (abs(totalArea - 2 * currentArea) < minAreaDifference) {
            minAreaDifference = abs(totalArea - 2 * currentArea);
            first = i;
            second = j;
        }

        currentArea -= calculateTriangleArea(polygon[i], polygon[(i + 1) % n], polygon[j]);
    }

    return {first + 1, second + 1};
}

int main() {
    int n;
    cin >> n;

    vector<Point> polygon(n);
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    pair<int, int> optimalLineSegment = findOptimalLineSegment(polygon);

    cout << optimalLineSegment.first << ' ' << optimalLineSegment.second << '\n';

    return 0;
}

// bien the 