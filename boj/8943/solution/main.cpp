#include <bits/stdc++.h>
using namespace std;

// 2D 좌표 표현
struct Point {
    int x, y;
    bool operator==(const Point &o) const {
        return x == o.x && y == o.y;
    }
};

// 해시 함수 (unordered_set<Point> 용)
struct PointHash {
    size_t operator()(const Point &p) const {
        // 간단히 pair-hash처럼
        // x, y를 31 같은 적당한 수로 섞어서 해시를 만든다
        // (충돌 최소화를 위해 실제로는 더 복잡한 방식 쓸 수도 있음)
        return std::hash<long long>()(((long long)p.x << 32) ^ (p.y & 0xffffffffLL));
    }
};

// (start, end) 선분 구조체
struct Segment {
    Point s, e;
    bool operator==(const Segment &o) const {
        return (s == o.s && e == o.e);
    }
};

// 해시 함수 (unordered_set<Segment> 용)
struct SegmentHash {
    size_t operator()(const Segment &seg) const {
        // 두 점 s, e의 해시를 적절히 섞는다
        // 예시로 간단히:
        auto sx = (long long)seg.s.x, sy = (long long)seg.s.y;
        auto ex = (long long)seg.e.x, ey = (long long)seg.e.y;
        // s 해시와 e 해시를 결합
        // (더 복잡한 방식을 써도 좋음)
        auto shash = ((sx << 32) ^ (sy & 0xffffffffLL));
        auto ehash = ((ex << 32) ^ (ey & 0xffffffffLL));
        // 두 해시를 다시 xor
        return std::hash<long long>()(shash ^ ehash);
    }
};

// 최대공약수
int gcd(int a, int b) {
    if (b == 0) return (a > 0 ? a : -a);
    return gcd(b, a % b);
}

// 방향 벡터 정규화
pair<int, int> normalizeDirection(const Point &p1, const Point &p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int g = gcd(dx, dy);
    if (g == 0) {
        // 같은 점이면 (0,0) 반환
        return {0, 0};
    }
    dx /= g;
    dy /= g;
    // 보통 '대표 부호' 통일:
    // dx<0 이면 -1을 곱, dx=0인데 dy<0 이면 -1을 곱...
    // 여기서는 간단히 dx>0이거나 dx=0이고 dy>0이면 그대로,
    // 아니면 -1을 곱하겠다
    if (dx < 0) {
        dx = -dx;
        dy = -dy;
    } else if (dx == 0 && dy < 0) {
        dy = -dy;
    }
    return {dx, dy};
}

// 세 점 (p1, p2, p3)이 일직선(Collinear)인지 검사
bool isCollinear(const Point &p1, const Point &p2, const Point &p3) {
    // 외적(크로스곱) == 0
    // (x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1) == 0
    long long cross =
        (long long)(p2.x - p1.x) * (p3.y - p1.y) -
        (long long)(p2.y - p1.y) * (p3.x - p1.x);
    return (cross == 0);
}

// ---------------- 키패드 매핑 ----------------
static unordered_map<char, Point> keypad = {
    {'1', {0, 0}}, {'2', {0, 1}}, {'3', {0, 2}}, {'4', {1, 0}}, {'5', {1, 1}}, {'6', {1, 2}}, {'7', {2, 0}}, {'8', {2, 1}}, {'9', {2, 2}}, {'*', {3, 0}}, {'0', {3, 1}}, {'#', {3, 2}}};

// MNDS 계산 함수
int calculateMNDS(const string &number) {
    // 1) 각 문자 -> 좌표
    vector<Point> points;
    points.reserve(number.size());
    for (char c : number) {
        points.push_back(keypad[c]);
    }

    // 2) 연속 중복 좌표 제거
    vector<Point> uniq;
    uniq.push_back(points[0]);
    for (size_t i = 1; i < points.size(); i++) {
        if (!(points[i] == uniq.back())) {
            uniq.push_back(points[i]);
        }
    }
    if (uniq.size() < 2) {
        // 이동이 없으면 MNDS=0
        return 0;
    }

    // 3) 선분 중복 체크를 위한 set
    unordered_set<Segment, SegmentHash> usedSegments;

    // 4) MNDS 계산
    //    - "첫 선분"으로 MNDS = 1부터 시작
    //    - 이후 선분이 일직선이 아닌 경우(방향 전환) MNDS++
    //    - 단, 이미 사용된 선분이면 건너뜀

    int MNDS = 0;
    // "이전 선분"의 방향
    pair<int, int> lastDir = {0, 0};
    bool firstAccepted = false;  // 아직 첫 선분을 안 정했다

    for (size_t i = 0; i < uniq.size() - 1; i++) {
        Segment seg{uniq[i], uniq[i + 1]};

        // 이미 등장한 선분이면 무시
        if (usedSegments.find(seg) != usedSegments.end()) {
            continue;
        }
        // 새 선분이면 set에 추가
        usedSegments.insert(seg);

        // 이번 선분의 방향 계산
        auto dir = normalizeDirection(uniq[i], uniq[i + 1]);

        // 첫 '유효' 선분이면 MNDS=1로 시작
        if (!firstAccepted) {
            MNDS = 1;
            lastDir = dir;
            firstAccepted = true;
            continue;
        }

        // 방향이 바뀌었으면 전환 발생
        if (dir != lastDir) {
            MNDS++;
            lastDir = dir;
        }
    }
    return MNDS;
}

// MNDS로 분류
string classifyPhoneNumber(const string &number) {
    int val = calculateMNDS(number);
    if (val <= 3) return "EXCELLENT";
    if (val == 4) return "GOOD";
    return "BAD";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string phoneNumber;
        cin >> phoneNumber;
        cout << classifyPhoneNumber(phoneNumber) << "\n";
    }
    return 0;
}
