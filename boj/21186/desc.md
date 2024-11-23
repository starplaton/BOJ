# 21186번 - Early Orders


=======================

4 초

1024 MB

36

21

21

65.625%

문제
--

You are given a list of integers $x\_1, x\_2, \\ldots, x\_n$ and a number $k$. It is guaranteed that each $i$ from $1$ to $k$ appears in the list at least once.

Find the lexicographically smallest subsequence of $x$ that contains each integer from $1$ to $k$ exactly once.

입력
--

The first line will contain two integers $n$ and $k$, with $1\\le k\\le n\\le 200\\,000$. The following $n$ lines will each contain an integer $x\_i$ with $1\\le x\_i\\le k$.

출력
--

Write out on one line, separated by spaces, the lexicographically smallest subsequence of $x$ that has each integer from $1$ to $k$ exactly once.

제한
--

예제 입력 1
-------

6 3
3
2
1
3
1
3

예제 출력 1
-------

2 1 3

예제 입력 2
-------

10 5
5
4
3
2
1
4
1
1
5
5

예제 출력 2
-------

3 2 1 4 5

힌트
--

출처
--

[![](https://licensebuttons.net/l/by-sa/3.0/88x31.png)](https://creativecommons.org/licenses/by-sa/3.0/)

[ICPC](/category/1) > [Regionals](/category/7) > [North America](/category/8) > [North Central North America Regional](/category/167) > [NCNA 2019](/category/detail/2464) E번

*   문제를 만든 사람: Lewin Gan