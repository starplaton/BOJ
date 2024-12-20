# 21918번 - 전구


=============

1 초

512 MB

2582

1515

1240

58.824%

문제
--

$N$개의 전구가 있고 맨 왼쪽에 있는 전구를 첫 번째라고 하자. **전구의 상태**는 두 가지가 있으며 이를 숫자로 표현한다.

$1$은 전구가 켜져 있는 상태를 의미하고, $0$은 전구가 꺼져 있는 상태를 의미한다.

전구를 제어하는 명령어가 1번부터 4번까지 4개가 있다. 아래 표는 각 명령어에 대한 설명이다.

1번 명령어 **\[$i$ $x$\]** $(1 \\le i \\le N, 0 \\le x \\le 1)$

$i$ 번째 전구의 상태를 $x$로 변경한다.

2번 명령어 **\[$l$ $r$\]** $(1 \\le l \\le r \\le N)$

$l$번째부터 $r$번째까지의 전구의 상태를 변경한다. (켜져있는 전구는 끄고, 꺼져있는 전구는 킨다.)

3번 명령어 **\[$l$ $r$\]** $(1 \\le l \\le r \\le N)$

$l$번째부터 $r$번째까지의 전구를 끈다.

4번 명령어 **\[$l$ $r$\]** $(1 \\le l \\le r \\le N)$

$l$번째부터 $r$번째까지의 전구를 킨다.

주어지는 명령어를 다 수행한 결과 전구는 어떤 상태인지 알아보자.

입력
--

첫 번째 줄에 전구의 개수 $N$와 입력되는 명령어의 개수 $M$이 주어진다.

두 번째 줄에는 $N$개의 전구가 현재 어떤 상태 $s$인지 주어진다. ($0$은 꺼져있는 상태, $1$은 켜져있는 상태)

$3$ 번째 줄부터 $M + 2$ 번째 줄까지 세 개의 정수 $a, b, c$가 들어온다.

$a$는 $a$번째 명령어를 의미하고 $b, c$는 $a$가 1인 경우는 각각 $i, x$를 의미하고 $a$가 $2, 3, 4$ 중 하나면 각각 $l, r$을 의미한다.

출력
--

모든 명령어를 수행한 후 전구가 어떤 상태인지 출력한다.

제한
--

*   $1 \\le N, M \\le 4,000$
*   $1 \\le a \\le 4$
*   $0 \\le s, x \\le 1$
*   $1 \\le l \\le r \\le N$
*   $1 \\le i \\le N$

예제 입력 1
-------

8 3
0 0 0 0 0 0 0 0
1 2 1
1 4 1
2 2 4

예제 출력 1
-------

0 0 1 0 0 0 0 0

![](https://upload.acmicpc.net/b4f011d9-ee3d-460e-aab9-97d4fd61e6cf/-/crop/1920x332/0,392/-/preview/)

위 그림은 처음에 전구는 다 꺼져있는 상태이다.

![](https://upload.acmicpc.net/d184a7f3-a9f5-459f-802c-ef1acbd4564c/-/crop/1920x324/0,383/-/preview/)

그 다음 그림은 첫 번째 명령어를 수행한 결과이다.  
![](https://upload.acmicpc.net/cd49968f-6c51-4bfe-bccd-1d0e6efa1a8b/-/crop/1920x319/0,385/-/preview/)

두 번째 명령어를 수행한 결과이다.  
![](https://upload.acmicpc.net/5e4d2c97-0714-42f0-ac79-6bbfe7e57b6e/-/crop/1920x312/0,388/-/preview/)

마지막 명령어를 수행한 결과이다.

예제 입력 2
-------

8 6
0 0 0 0 0 0 0 0
1 2 1
1 4 1
2 2 4
2 1 7
3 5 8
4 4 6

예제 출력 2
-------

1 1 0 1 1 1 0 0

힌트
--

출처
--

*   문제를 검수한 사람: [melon940925](/user/melon940925), [rhs0266](/user/rhs0266)
*   문제를 만든 사람: [tony9402](/user/tony9402)