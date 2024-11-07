# 20221번 - In-place Sorting


===========================

2 초

512 MB

96

43

39

52.000%

문제
--

Woe is you -- for your algorithms class you have to write a sorting algorithm, but you missed the relevant lecture! The subject was in-place sorting algorithms, which you deduce must be algorithms that leave each input number in its place and yet somehow also sort the sequence.

Of course you cannot change any of the numbers either, then the result would just be a different sequence. But then it hits you: if you flip a 6 upside-down, it becomes a 9, and vice versa! Certainly no one can complain about this since you changed none of the digits! The deadline to hand in the exercise is in five hours. Try to implement this sorting algorithm before then!

입력
--

The input consists of:

*   A line with an integer $n$ ($2 \\leq n \\leq 10\\,000$), the number of integers in the input sequence.
*   $n$ lines, the $i$th of which contains a positive integer $x\_i$ ($1\\leq x\_i \\leq 10^{18}$), the $i$th number of the sequence.

출력
--

If the sequence cannot be sorted in non-decreasing order by flipping some of the digits $6$ or $9$ in the input1, output "`impossible`". Otherwise, output "`possible`" followed by the sorted sequence -- each number on its own line.

If there are multiple valid solutions, you may output any one of them.

1Flipping any of the digits of $n$ is not allowed.

제한
--

예제 입력 1
-------

4
9
7
7
9

예제 출력 1
-------

possible
6
7
7
9

예제 입력 2
-------

4
97
96
66
160

예제 출력 2
-------

possible
67
69
99
190

예제 입력 3
-------

3
80
97
79

예제 출력 3
-------

impossible

예제 입력 4
-------

2
197
166

예제 출력 4
-------

possible
167
169

힌트
--

출처
--

[![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)](https://creativecommons.org/licenses/by-sa/4.0/)

[ICPC](/category/1) > [Regionals](/category/7) > [Europe](/category/10) > [Northwestern European Regional Contest](/category/15) > [Benelux Algorithm Programming Contest](/category/89) > [BAPC 2020 Preliminaries](/category/detail/2346) I번

*   문제를 만든 사람: Timon Knigge