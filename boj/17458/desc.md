# 17458번 - Good Set


===================

1 초

1024 MB

27

15

9

52.941%

문제
--

Seunghyun is a mathematician, and he likes good jokes. 

For a set $U = \\{0, 1, \\cdots, 2^k - 1\\}$, a nonempty subset $A \\subset U$ is _good_ if it satisfies the following rules. 

*   For any $x, y \\in S$, their bitwise-and $x \\And y$ should be in $S$. 
*   For any $x, y \\in S$, their bitwise-or $x \\mid y$ should be in $S$. 

You are given $n$ distinct integers in $\[0, 2^k-1\]$ range. Find the number of good sets which contains all $n$ integers. 

입력
--

The first line contains two integers $k, n$. ($1 \\le k \\le 7, 0 \\le n \\le 2^k$)

The next line contains $n$ distinct integers $a\_1, a\_2, \\cdots, a\_n$($0 \\le a\_i \\le 2^k - 1$).

출력
--

Print a single integer denoting the number of good sets.

제한
--

예제 입력 1
-------

2 1
0

예제 출력 1
-------

7

예제 입력 2
-------

4 3
1 2 7

예제 출력 2
-------

29

힌트
--

출처
--

[Contest](/category/45) > [Open Cup](/category/485) > [2018/2019 Season](/category/608) > [Stage 19: Grand Prix of Daejeon](/category/detail/2856) G번

*   문제를 만든 사람: [ainta](/user/ainta)