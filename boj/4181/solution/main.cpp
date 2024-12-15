#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x;
    long long y;
};

// Cross product of OA and OB vectors
long long cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<Point> points;
    for (int i = 0; i < n; i++) {
        long long x, y;
        char c;
        cin >> x >> y >> c;
        if (c == 'Y') {
            points.push_back(Point{x, y});
        }
    }

    int m = points.size();
    if (m == 0) {
        cout << "0\n";
        return 0;
    }

    // Sort the points by x, then y
    sort(points.begin(), points.end(), [&](const Point& a, const Point& b) -> bool {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    // Build the lower hull
    vector<Point> lower;
    for (auto& p : points) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower[lower.size() - 1], p) <= 0) {
            lower.pop_back();
        }
        lower.push_back(p);
    }

    // Build the upper hull
    vector<Point> upper;
    for (int i = points.size() - 1; i >= 0; i--) {
        auto& p = points[i];
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper[upper.size() - 1], p) <= 0) {
            upper.pop_back();
        }
        upper.push_back(p);
    }

    // Concatenate lower and upper to get the full hull
    // Remove the last point of each list to avoid duplicates
    lower.pop_back();
    upper.pop_back();
    vector<Point> hull;
    for (auto& p : lower) {
        hull.push_back(p);
    }
    for (auto& p : upper) {
        hull.push_back(p);
    }

    // Now, hull is in counterclockwise order
    // To ensure starting point is the leftmost (smallest x, then y)
    // Find the starting point index
    int start_idx = 0;
    for (int i = 1; i < hull.size(); i++) {
        if (hull[i].x < hull[start_idx].x || (hull[i].x == hull[start_idx].x && hull[i].y < hull[start_idx].y)) {
            start_idx = i;
        }
    }

    // Rotate the hull to start from start_idx
    rotate(hull.begin(), hull.begin() + start_idx, hull.end());

    // To ensure CCW order, verify orientation
    // Compute the signed area (positive means CCW)
    long long area = 0;
    for (int i = 0; i < hull.size(); i++) {
        int j = (i + 1) % hull.size();
        area += (hull[i].x * hull[j].y - hull[j].x * hull[i].y);
    }
    if (area < 0) {
        // Reverse to make it CCW
        reverse(hull.begin(), hull.end());
        // After reversing, rotate again to start from start_idx
        // Find the new start point index
        start_idx = 0;
        for (int i = 1; i < hull.size(); i++) {
            if (hull[i].x < hull[start_idx].x || (hull[i].x == hull[start_idx].x && hull[i].y < hull[start_idx].y)) {
                start_idx = i;
            }
        }
        rotate(hull.begin(), hull.begin() + start_idx, hull.end());
    }

    // Output
    cout << hull.size() << "\n";
    for (auto& p : hull) {
        cout << p.x << " " << p.y << "\n";
    }

    return 0;
}
