
// O(n log n)
// space complexity: O(N)    Graham Scan

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};


int ccw(const Point& a, const Point& b, const Point& c) {
    double area2 = (b.x - a.x) * (c.y - a.y) - 
                   (b.y - a.y) * (c.x - a.x);
    if (area2 > 0) return 1;    // CCW
    if (area2 < 0) return -1;   // CW
    return 0;                   // collinear
}

// bool polarCmp(const Point& p0, const Point& a, const Point& b) {
//     int turn = ccw(p0, a, b);
//     if (turn == 0)
//         return hypot(a.x - p0.x, a.y - p0.y) < hypot(b.x - p0.x, b.y - p0.y);
//     return turn > 0;
// }

//from the book
bool polarCmp(const Point& p0, const Point& a, const Point& b) {
    double dy1 = a.y - p0.y;
    double dy2 = b.y - p0.y;

    // Determine precedence based on whether the point is above or below the axis
    if (dy1 >= 0 && dy2 < 0) return true;
    if (dy2 >= 0 && dy1 < 0) return false;

    int turn = ccw(p0, a, b);
    if (turn == 0)
        return hypot(a.x - p0.x, a.y - p0.y) < hypot(b.x - p0.x, b.y - p0.y);
    return turn > 0;
}



vector<Point> grahamScan(vector<Point> pts) {
    int n = pts.size();
    if (n < 3) return pts;

    // 1. Find the point with the lowest y-coordinate
    int p0_idx = 0;
    for (int i = 1; i < n; i++) {
        if (pts[i].y < pts[p0_idx].y || 
           (pts[i].y == pts[p0_idx].y && pts[i].x < pts[p0_idx].x)) {
            p0_idx = i;
        }
    }
    swap(pts[0], pts[p0_idx]);
    //calculate the angle for the ordering
    Point p0 = pts[0];    // the lowest point

    // 2. Sort by polar angle relative to p0
    auto cmp = [&p0](const Point& a, const Point& b){
        return polarCmp(p0, a, b);
    };
    sort(pts.begin() + 1, pts.end(), cmp);

    // 3. Stack for building the convex hull
    vector<Point> hull;
    hull.push_back(pts[0]);
    hull.push_back(pts[1]);

    for (int i = 2; i < n; i++) {
        while (hull.size() >= 2 &&
               ccw(hull[hull.size()-2], hull.back(), pts[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }

    return hull;
}

int main() {
    vector<Point> points = {
        {0,0}, {1,1}, {2,2}, {2,0}, {2,4}, {3,3}, {0,3}
    };

    vector<Point> hull = grahamScan(points);

    cout << "Convex Hull Points (CCW):\n";
    for (auto& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
}
