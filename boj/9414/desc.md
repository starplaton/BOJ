# 9414번 - 프로그래밍 대회 전용 부지


========================

1 초

128 MB

652

389

363

62.051%

문제
--

상근이는 어렸을 때부터 항상 프로그래밍 캠프를 개최하고 싶어했다. 캠프를 개최할 때 가장 필요한 것은 장소이다. 지금까지 많은 사람들이 장소의 벽에 가로막혀 캠프를 주최할 수가 없었다.

상근이는 프로그래밍 캠프 전용 부지를 구입해 모든 사람의 장소 문제를 해결하려고 한다. 서울의 땅값은 매년 기하급수적으로 비싸진다. 예를 들어, 땅 i의 현재 땅값이 Li인 경우, t년이 지난 후 땅값은 2×(Li)t가 된다. 모든 땅값은 서로 다르다. 상근이는 일년에 땅 하나만 구입할 수 있다.

상근이가 구입하려고 하는 땅의 현재 가격이 주어졌을 때, 모든 땅을 구입하는데 드는 비용의 최솟값을 구하는 프로그램을 작성하시오. 상근이는 돈을 5×106 억원 가지고 있고, 1년이 지난 후부터 땅을 구입하기 시작한다. (누가 돈을 훔쳐가거나, 다른데에 돈을 쓰거나, 돈을 벌거나 하는 상황은 발생하지 않는다)

예를 들어, 땅의 가격이 7억, 2억, 10억일 때, 각 땅을 연속한 해에 구입하는데 필요한 금액은 다음과 같다.

(2×7) + (2×22) + (2×103) = 2022억

입력
--

첫째 줄에 테스트 케이스의 개수 T (1 ≤ T ≤ 10)가 주어진다. 각 테스트 케이스는 땅값 Li가 한 줄에 하나씩 주어지며, 0은 테스트 케이스의 마지막을 나타낸다. 각 테스트 케이스마다 상근이가 구매하려는 땅의 개수는 40개를 넘지 않는다. 모든 단위는 억단위이다.

출력
--

각 테스트 케이스마다 모든 땅을 구입하는데 필요한 최소 금액을 출력한다. 만약, 돈이 부족해서 땅을 모두 구입하지 못하는 경우에는 "Too expensive"를 출력한다. (단위: 억)

제한
--

예제 입력 1
-------

3
7
2
10
0
20
29
31
0
42
41
40
37
20
0

예제 출력 1
-------

134
17744
Too expensive

힌트
--

출처
--

[ICPC](/category/1) > [Regionals](/category/7) > [Asia Pacific](/category/42) > [Thailand](/category/102) > [Asia Thailand National Programming Contest](/category/278) > [2010 ACM-ICPC Thailand National Programming Contest](/category/detail/1164) G번

*   문제를 번역한 사람: [baekjoon](/user/baekjoon)
*   문제의 오타를 찾은 사람: [myungwoo](/user/myungwoo)