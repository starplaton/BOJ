#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

// 체크섬을 계산하고 비교하는 함수
char calculateChecksum(const string& id) {
    int weights[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    char checksumChars[11] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};

    int sum = 0;
    for (int i = 0; i < 17; i++) {
        sum += (id[i] - '0') * weights[i];
    }

    int modResult = sum % 11;
    return checksumChars[modResult];
}

// 유효한 생일인지 검사하는 함수
bool isValidDate(const string& date) {
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(4, 2));
    int day = stoi(date.substr(6, 2));

    if (year < 1900 || year > 2011) return false;
    if (month < 1 || month > 12) return false;

    // 각 월의 최대 일 수
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;  // 윤년의 경우 2월이 29일까지
    }

    return day >= 1 && day <= daysInMonth[month - 1];
}

int main() {
    string id;
    int n;
    cin >> id >> n;

    // 유효한 지역 코드를 저장하는 집합
    set<string> validRegions;
    for (int i = 0; i < n; i++) {
        string regionCode;
        cin >> regionCode;
        validRegions.insert(regionCode);
    }

    // 유효성 검사
    string regionCode = id.substr(0, 6);
    string birthDate = id.substr(6, 8);
    string sequenceCode = id.substr(14, 3);
    char expectedChecksum = calculateChecksum(id);

    // 지역 코드 검사
    if (validRegions.find(regionCode) == validRegions.end()) {
        cout << "I" << endl;
        return 0;
    }

    // 생일 코드 검사
    if (!isValidDate(birthDate)) {
        cout << "I" << endl;
        return 0;
    }

    // 순서 코드 검사
    if (sequenceCode == "000") {
        cout << "I" << endl;
        return 0;
    }

    // 체크섬 코드 검사
    if (id[17] != expectedChecksum) {
        cout << "I" << endl;
        return 0;
    }

    // 성별 판별
    int sequenceNumber = stoi(sequenceCode);
    if (sequenceNumber % 2 == 1) {
        cout << "M" << endl;  // 남성
    } else {
        cout << "F" << endl;  // 여성
    }

    return 0;
}
