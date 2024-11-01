# 25756번 - 방어율 무시 계산하기


======================

1 초

512 MB

1348

744

667

57.057%

문제
--

메이플스토리에는 방어율 무시라는 수치가 있다. 특정 보스를 잡기 위해서는 특정 방어율 무시 수치가 되어야 데미지가 정확히 들어가는 시스템으로 이루어져 있다. 물약 아이템을 사용하여 방어율 무시 수치를 증가시킬 수 있다.

현재 방어율 무시 수치가 $V$인 상태에서, 수치가 $A\_i$인 물약을 마시면 새로운 방어율 무시 수치는 아래와 같이 계산된다.

$1 - (1 - V)(1 - A\_i)$

주어지는 물약의 방어율 무시 값의 단위는 **퍼센트**이다.

기본 방어율 무시 수치는 $0\\%$라고 가정한다.

임스가 가지고 있는 물약 $N$개의 방어율 무시 수치가 주어졌을 때, 물약을 순서대로 마시면서 변화된 방어율 무시 수치를 모두 출력하시오.

입력
--

첫 번째 줄에는 임스가 가지고 있는 물약의 개수 $N$이 주어진다. $(1 \\le N \\le 40\\,000)$

두 번째 줄에는 임스가 가지고 있는 물약으로 인해 증가되는 방어율 무시 수치를 의미하는 정수 $A\_1, A\_2, \\dots, A\_N$가 공백으로 구분되어 주어진다. $(1 \\le A\_i \\le 30)$

출력
--

$N$개의 줄에 걸쳐 임스가 물약을 마시면서 증가된 방어율 무시 수치를 출력하시오. 절대/상대 오차는 $10^{-6}$까지 허용한다.

제한
--

예제 입력 1
-------

5
20 20 20 20 20

예제 출력 1
-------

20.0
36.0
48.8
59.04
67.232

힌트
--

출처
--

[University](/category/5) > [서울과학기술대학교](/category/674) > [제1회 서울과학기술대학교 컴퓨터공학과 알고리즘 대회](/category/detail/3207) B번

*   문제를 검수한 사람: [exponential\_e](/user/exponential_e), [jthis](/user/jthis), [leo020630](/user/leo020630), [tony9402](/user/tony9402), [wider93](/user/wider93)
*   문제를 만든 사람: [lms0806](/user/lms0806)