#include <bits/stdc++.h>
using namespace std;

// 점을 표현하는 구조체
struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        // x좌표 기준으로 정렬, x가 같으면 y좌표 기준
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};

// 두 점 간의 벡터의 외적을 계산
long long cross(const Point& O, const Point& A, const Point& B) {
    // OA x OB
    long long val = (long long)(A.x - O.x) * (B.y - O.y) - (long long)(A.y - O.y) * (B.x - O.x);
    return val;
}

// 볼록 껍질을 구하는 함수 (Andrew's Monotone Chain 알고리즘)
vector<Point> convex_hull(vector<Point>& points) {
    int n = points.size();
    if (n == 1)
        return points;

    sort(points.begin(), points.end());

    vector<Point> lower, upper;

    // 하부 껍질 생성
    for (int i = 0; i < n; ++i) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower[lower.size() - 1], points[i]) <= 0)
            lower.pop_back();
        lower.push_back(points[i]);
    }

    // 상부 껍질 생성
    for (int i = n - 1; i >= 0; --i) {
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper[upper.size() - 1], points[i]) <= 0)
            upper.pop_back();
        upper.push_back(points[i]);
    }

    // 하부 껍질과 상부 껍질을 합침 (양 끝 점 중복 제거)
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());

    return lower;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<Point> points(N);
    for (int i = 0; i < N; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    vector<Point> hull = convex_hull(points);

    // 볼록 껍질의 꼭짓점 개수 출력
    cout << hull.size();
}
