# 16153번 - 비트와 가희


=================

0.5 초 (추가 시간 없음)

256 MB

419

71

49

19.141%

문제
--

다음과 같은 조건이 _N_개 주어진다.

*   _i_번째 bit가 1이어야 한다. 즉, 어떠한 수 _X_가 있다면 _X_ & (1 << _i_)의 값이 0이 아니어야 한다.

1 이상 _B_ 이하의 정수 중 이러한 조건을 만족하는 _A_의 배수는 몇 개인지 구하는 프로그램을 작성하시오.

입력
--

첫째 줄에 _N_(0 ≤ _N_ < 32), _A_, _B_(0 < _A_, _B_ < 231)가 공백으로 구분되어 주어진다.

둘째 줄부터 _N_개의 각 줄에는 켜져야 하는 bit가 _N_개 주어진다. 이 값들은 30이하인 음이 아닌 정수이며, 켜져야 하는 bit는 중복으로 주어지지 않는 것이 보장된다.

출력
--

1이상 _B_이하의 정수 중 주어진 _N_개의 조건들을 만족하는 _A_의 배수의 개수를 출력하라.

제한
--

예제 입력 1
-------

1 2 15
1

예제 출력 1
-------

4

힌트
--

출처
--

[Contest](/category/45) > [BOJ User Contest](/category/984) > [네블컵](/category/421) > [제2회 네블컵](/category/detail/1918) B번

*   문제를 만든 사람: [chogahui05](/user/chogahui05)