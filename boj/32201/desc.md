# 32201번 - 눈사람


==============

1 초

1024 MB

74

61

60

85.714%

문제
--

평창 동계 올림픽의 하이라이트를 장식할 눈사람 만들기 경기가 시작되었다! 이 경기에서는 주어진 시간동안 눈사람을 크게 만드는 사람이 우승한다.

애리가 중계 방송을 켰을 때, 경기가 시작한지 얼마 되지 않은 시점이었다. 중계 방송에서는 순위표를 방송하고 있었다. 순위표는 등수 순서대로 각 선수의 등번호를 나열한 표이다. 애리는 순위표에 나온 등번호를 순서대로 기억해 두었다.

애리가 잠시 딴짓을 하고 오자, 경기가 끝났다. 경기가 끝난 시점의 순위표가 주어젔을 때, 애리가 기억하는 시점에서의 등수와 비교해 가장 등수가 많이 상승한 선수들의 등번호를 구하여라.

입력
--

첫째 줄에는 경기에 참가한 선수의 수 $N$이 주어진다.

둘째 줄에는 애리가 중계 방송을 켠 시점에서 각 선수의 등번호를 나타내는 $N$개의 정수 $A\_1, \\cdots, A\_N$가 등수 순서대로 공백을 사이에 두고 주어진다.

셋째 줄에는 경기가 끝난 시점에서 각 선수의 등번호를 나타내는 $N$개의 정수 $B\_1, \\cdots, B\_N$가 등수 순서대로 공백을 사이에 두고 주어진다.

출력
--

가장 순위가 많이 상승한 선수들의 등번호들을 경기가 끝난 시점의 등수 순서대로 공백을 사이에 두고 출력한다.

제한
--

*   $1 \\le N \\le 100\\,000$
*   $1 \\le A\_i \\le 1\\,000\\,000\\,000$
*   $1 \\le B\_i \\le 1\\,000\\,000\\,000$
*   $A\_i$들은 모두 다르다. ($i \\neq j \\rightarrow A\_i \\neq A\_j$)
*   $B\_i$들은 모두 다르다. ($i \\neq j \\rightarrow B\_i \\neq B\_j$)
*   배열 $A$의 원소의 집합은 배열 $B$의 원소의 집합과 같다.

예제 입력 1
-------

4
411 101 1023 1030
1023 1030 101 411

예제 출력 1
-------

1023 1030

등 번호

처음 중계 방송을 켠 시점의 등수

경기가 끝난 시점의 등수

등수 변화

1023

3

1

+2

1030

4

2

+2

101

2

3

\-1

411

1

4

\-3

등 번호 1023과 1030인 두 선수의 등수가 2계단 상승했으며, 이는 모든 선수들 중 최대이다. 경기가 끝난 시점의 등수 순서대로 출력해야 한다!

예제 입력 2
-------

5
304 513 711 206 1030
304 513 711 206 1030

예제 출력 2
-------

304 513 711 206 1030

모든 선수의 등수가 0계단 상승했으며, 이는 모든 선수들 중 최대이다. 따라서 모든 선수들을 경기가 끝난 시점의 등수 순서대로 출력한다.

힌트
--

출처
--

[University](/category/5) > [강원도 대학생 코딩 경진대회](/category/1052) > [2024 강원도 대학생 코딩경진대회](/category/detail/4272) B번

*   문제를 검수한 사람: [ahgus89](/user/ahgus89), [onjo0127](/user/onjo0127), [silverwolf](/user/silverwolf)
*   문제를 만든 사람: [junie](/user/junie)