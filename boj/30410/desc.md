# 30410번 - 접시 포개기


=================

1 초

1024 MB

328

122

86

36.910%

문제
--

춘배는 배가 너무 고파서 밥을 모두 먹어 치웠고 현재 춘배의 앞에는 $N$개의 접시가 있다. $i$번째 접시의 두께는 정수 $A\_i$로 표현되는데, 이제 배부르기 때문에 재미있는 놀이를 해보려고 한다.

![](https://upload.acmicpc.net/979b602e-9058-4fb8-92fa-a4a6cd640f84/-/preview/)

다음과 같이 접시를 포갤 수 있을 때, 마지막에 남는 가장 두꺼운 접시의 두께를 최대화하는 것이 목표이다.

*   두께가 같은 인접한 두 접시를 포개어 두께가 $2$배가 된 새로운 접시를 그 자리에 놓는다.

진짜로 접시를 포개면 깨질 수 있기 때문에 춘배는 당신의 도움을 얻고자 한다. 마지막에 남는 가장 두꺼운 접시의 두께를 최대화해보자!

입력
--

첫 번째 줄에 정수 $N$이 주어진다. $(1 \\le N \\le 2 \\times 10^5)$

두 번째 줄에 $N$개의 정수 $A\_1, A\_2, \\cdots, A\_N$이 공백을 사이에 두고 주어진다. $(1 \\le A\_i \\le 2)$

출력
--

남아있는 가장 두꺼운 접시의 두께의 최댓값을 출력한다.

제한
--

예제 입력 1
-------

4
1 1 2 2

예제 출력 1
-------

4

예제 입력 2
-------

8
2 2 2 2 2 2 2 2

예제 출력 2
-------

16

힌트
--

출처
--

[Contest](/category/45) > [BOJ User Contest](/category/984) > [춘배컵](/category/985) > [2023 제1회 춘배컵](/category/detail/4007) I번

*   문제를 만든 사람: [eric00513](/user/eric00513)
*   문제를 검수한 사람: [fs\_edge](/user/fs_edge), [gggkik](/user/gggkik), [ksoosung77](/user/ksoosung77), [naeby](/user/naeby), [pjshwa](/user/pjshwa), [pyb1031](/user/pyb1031), [utilforever](/user/utilforever)