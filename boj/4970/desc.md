# 4970번 - 디지털 회로 개론


===================

1 초

128 MB

222

111

77

46.386%

문제
--

3차 논리는 논리값이 "true", "false", "unknown"을 가지는 논리 체계이다. 이 체계에서는 "false"는 0의 값을 가지고, "unknown"은 1, "true"는 2의 값을 갖는다.

"-"을 단항 연산자, "\*"와 "+"는 이항 연산자라고 하자. 이 연산자는 각각 NOT, AND, OR을 의미한다. 3차 논리에서 3개 연산자는 다음과 같이 정의되어 있다.

![](/upload/images/tv.png)

P, Q, R을 3차 논리값을 갖는 변수라고 하자. 이때, 식이 주어졌을 때, 식의 값을 2로 만드는 (P,Q,R)쌍의 개수를 구하는 프로그램을 작성하시오. 식은 다음 중 하나의 형태를 갖는다. (X와 Y는 식을 의미한다)

*   상수: 0, 1, 2
*   변수: P, Q, R
*   NOT: -X
*   AND: (X\*Y)
*   OR: (X+Y)

AND와 OR은 항상 괄호로 둘러싸여 있다.

예를 들어, (P\*Q)가 주어졌을 때, 식의 값을 2로 만드는 (P,Q,R)쌍은 (2,2,0), (2,2,1), (2,2,2) 3가지이다.

입력
--

입력은 여러 개의 테스트 케이스로 이루어져 있다. 각 테스트 케이스는 한 줄로 이루어져 있고, 식을 나타낸다. 식은 0, 1, 2, P, Q, R, -, \*, +, (, )로만 이루어져 있다.

식의 BNF형 문법은 다음과 같다.

<formula> ::= 0 | 1 | 2 | P | Q | R |
              -<formula> | (<formula>\*<formula>) | (<formula>+<formula>)

입력은 80글자를 넘지 않는다. 마지막 줄에는 '.'이 주어진다.

출력
--

각 테스트 케이스에 대해서, 입력으로 주어진 식의 값을 2로 만드는 (P,Q,R) 쌍의 개수를 출력한다.

제한
--

예제 입력 1
-------

(P\*Q)
(--R+(P\*Q))
(P\*-P)
2
1
(-1+(((---P+Q)\*(--Q+---R))\*(-R+-P)))
.

예제 출력 1
-------

3
11
0
27
0
7

힌트
--

출처
--

[ICPC](/category/1) > [Regionals](/category/7) > [Asia Pacific](/category/42) > [Japan](/category/43) > [Japan Domestic Contest](/category/44) > [2008 Japan Domestic Contest](/category/detail/204) C번

*   문제를 번역한 사람: [baekjoon](/user/baekjoon)
*   문제의 오타를 찾은 사람: [dlaud5379](/user/dlaud5379)