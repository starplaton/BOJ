# 24552번 - 올바른 괄호


=================

1 초 (추가 시간 없음)

1024 MB (추가 메모리 없음)

670

290

248

53.333%

문제
--

$\\texttt{(}$, $\\texttt{)}$로 구성된 문자열 $S$에서 정확히 하나의 괄호를 지워 올바른 괄호열을 만들 수 있는 경우의 수를 출력하자.

올바른 괄호열은 다음과 같이 정의된다.

1.  $\\texttt{()}$는 올바른 괄호열이다.
2.  $\\texttt{A}$가 올바른 괄호열이면 $\\texttt{(A)}$는 올바른 괄호열이다.
3.  $\\texttt{A}$와 $\\texttt{B}$가 올바른 괄호열이면 $\\texttt{AB}$는 올바른 괄호열이다.

입력
--

첫번째 줄에 문자열 $S$가 공백 없이 주어진다. ($3 \\leq \\vert S \\vert \\leq 100\\,000$, $\\vert S \\vert$는 홀수이다.)

답은 $1$ 이상이다. 즉, 지웠을 때 올바른 괄호열이 되는 문자가 적어도 하나 존재한다.

출력
--

올바른 괄호열을 만들 수 있는 경우의 수를 출력한다.

제한
--

예제 입력 1
-------

()(()

예제 출력 1
-------

2

예제 입력 2
-------

()(()))

예제 출력 2
-------

4

힌트
--

출처
--

[University](/category/5) > [신촌지역 대학생 프로그래밍 대회 동아리 연합](/category/497) > [2022 신촌지역 대학생 프로그래밍 대회 동아리 연합 겨울 대회 (SUAPC 2022 Winter)](/category/detail/3032) K번

*   문제를 만든 사람: [chansol](/user/chansol)
*   문제를 검수한 사람: [cheetose](/user/cheetose), [eaststar](/user/eaststar), [gumgood](/user/gumgood), [heeda0528](/user/heeda0528), [jh05013](/user/jh05013), [jwvg0425](/user/jwvg0425), [lky7674](/user/lky7674), [myyh1234](/user/myyh1234), [pichulia](/user/pichulia), [pjshwa](/user/pjshwa)