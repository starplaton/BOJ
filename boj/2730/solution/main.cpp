#include <bits/stdc++.h>
using namespace std;

/**
 * 윤년 판별 함수
 * 서력기(그레고리력) 기준:
 *  - 연도가 4로 나누어떨어지면 윤년
 *  - 단, 100으로 나누어떨어지면 평년
 *  - 단, 400으로 나누어떨어지면 윤년
 */
bool isLeapYear(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    return (year % 4 == 0);
}

/**
 * year년의 1월 1일부터 m월 d일까지 며칠이 지났는지(1-based) 반환
 */
int dayOfYear(int m, int d, int year) {
    static int md[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;
    for (int i = 0; i < m - 1; i++) {
        days += md[i];
    }
    // 윤년이고 m > 2면 2월 29일을 하루 더 추가
    if (isLeapYear(year) && m > 2) days += 1;
    days += d;
    return days;
}

/**
 * (y년 m월 d일)을 절대 일수(예: 특정 기준일로부터의 일수)로 변환
 * 여기서는 간단히 "연 단위 일수 + 윤년 개수 + dayOfYear"를 이용하는 방식
 * - 기준 연도가 달라도, 두 날짜 간의 차이만 일관되면 무방.
 * - 예시로 1년 1월 1일을 0일로 놓고 계산해도 됨.
 */
long long toAbsoluteDays(int y, int m, int d) {
    // 1년 1월 1일부터 (y-1)년까지의 일 수 합
    //   year*365 + 윤년 개수
    //   + 이번 해의 dayOfYear
    // 주의: y가 1보다 작을 일은 없다고 가정(문제 범위)해도 되고,
    //       혹시 모를 범위 확장 고려 시엔 다른 달력 수식 적용 가능
    long long days = 0;

    // (y-1)년까지의 연수 * 365
    days += 1LL * (y - 1) * 365;

    // 1년부터 (y-1)년까지 존재하는 윤년 개수
    // (문제 범위 2000~2200, 출력은 1999~2201 정도이므로 이 방법으로 충분)
    for (int year = 1; year < y; year++) {
        if (isLeapYear(year)) days += 1;
    }

    // 올해의 dayOfYear
    days += dayOfYear(m, d, y);
    return days;
}

/**
 * 두 날짜 간의 일수 차 (date2 - date1)를 구함
 */
long long diffDays(int m1, int d1, int y1, int m2, int d2, int y2) {
    long long abs1 = toAbsoluteDays(y1, m1, d1);
    long long abs2 = toAbsoluteDays(y2, m2, d2);
    return abs2 - abs1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    while (T--) {
        string due, report;
        cin >> due >> report;
        // due: "M/D/Y"  예: "11/20/2005"
        // report: "M/D" 예: "11/21"

        // 파싱
        int Dm, Dd, Dy;  // 마감일(월/일/년)
        int Rm, Rd;      // 제출 보고서(월/일)

        {
            // 마감일 파싱
            // "M/D/Y" 형태이므로, '/'로 split
            // C++17부터 가능: use std::stringstream
            // 또는 직접 find와 substr
            int pos1 = due.find('/');
            int pos2 = due.find('/', pos1 + 1);
            Dm = stoi(due.substr(0, pos1));
            Dd = stoi(due.substr(pos1 + 1, pos2 - (pos1 + 1)));
            Dy = stoi(due.substr(pos2 + 1));
        }
        {
            // 제출일(월/일) 파싱
            int pos = report.find('/');
            Rm = stoi(report.substr(0, pos));
            Rd = stoi(report.substr(pos + 1));
        }

        // 후보 년도: Dy, Dy-1, Dy+1
        // 각각에 대해 due일과의 day 차이 계산
        // 절댓값이 가장 작은 쪽을 선택
        // (문제 예시를 보면, 차이가 같아지는 경우는 주어지지 않는 것으로 보임)

        // 후보: (year, 일수차)
        vector<pair<int, long long>> candidates;
        // 범위 상 문제 없도록, Dy-1 >= 1, Dy+1 <= 어떤 큰 수 ...
        // 문제에서 2000 ~ 2200이지만, 출력은 1999 ~ 2201 가능
        // 안전하게 -1, +1은 1보다 클테고, 2201보다 작을테니 그냥 계산한다.
        for (int yCandidate : {Dy - 1, Dy, Dy + 1}) {
            // 단, yCandidate가 0 이하가 되지 않도록, 혹은 너무 크지 않도록 처리
            // 문제 조건상 1999~2201 범위를 벗어나면 무의미하므로 가볍게 범위 체크
            if (yCandidate < 1) continue;
            if (yCandidate > 3000) continue;

            long long diff = diffDays(Dm, Dd, Dy, Rm, Rd, yCandidate);
            candidates.push_back({yCandidate, diff});
        }

        // 가장 절대값이 작은 diff를 고른다
        // tie가 있으면 문제에서 별도 언급 없으니 그냥 먼저 오는 것 사용
        sort(candidates.begin(), candidates.end(),
             [](auto &a, auto &b) {
                 long long aa = llabs(a.second);
                 long long bb = llabs(b.second);
                 if (aa == bb) {
                     // 절대값 같으면 더 작은 연도를 우선
                     return a.first < b.first;
                 }
                 return aa < bb;
             });

        int bestY = candidates[0].first;
        long long bestDiff = candidates[0].second;  // reportDate - dueDate (일수)

        // 이제 출력 형식에 맞춰 처리
        // 출력: "M/D/Y" 꼴 (Y 범위는 1999 <= Y <= 2201 이어도 문제 없음)
        //  bestDiff < 0 => PRIOR, > 0 => AFTER, == 0 => SAME DAY
        //  |bestDiff| == 0 => SAME DAY
        //  1 <= |bestDiff| <= 7 => ~ DAYS PRIOR/AFTER
        //  |bestDiff| > 7 => OUT OF RANGE
        // 주의: 출력 시 보고서 날짜 m/d는 report(실제 찍힌) 말고,
        //       우리가 결정한 bestY와 Rm/Rd 이어야 함
        // 예) 1/2/2005 마감, 보고서 12/30 -> 12/30/2004

        // same day?
        if (bestDiff == 0) {
            cout << "SAME DAY\n";
        } else {
            // M/D/Y 출력
            long long gap = llabs(bestDiff);
            if (gap <= 7) {
                cout << Rm << "/" << Rd << "/" << bestY << " IS ";
                // PRIOR or AFTER
                if (bestDiff < 0) {
                    // PRIOR
                    cout << gap << " DAY";
                    if (gap > 1) cout << "S";
                    cout << " PRIOR\n";
                } else {
                    // AFTER
                    cout << gap << " DAY";
                    if (gap > 1) cout << "S";
                    cout << " AFTER\n";
                }
            } else {
                // out of range
                cout << "OUT OF RANGE\n";
            }
        }
    }
    return 0;
}
