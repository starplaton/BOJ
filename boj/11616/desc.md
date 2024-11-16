# 11616번 - Digit Division


=========================

1 초

512 MB

286

137

115

46.559%

문제
--

We are given a sequence of n decimal digits. The sequence needs to be partitioned into one or more contiguous subsequences such that each subsequence, when interpreted as a decimal number, is divisible by a given integer m.

Find the number of different such partitions modulo 109 + 7. When determining if two partitions are different, we only consider the locations of subsequence boundaries rather than the digits themselves, e.g. partitions 2|22 and 22|2 are considered different.

입력
--

The first line contains two integers n and m (1 ≤ n ≤ 300 000, 1 ≤ m ≤ 1 000 000) – the length of the sequence and the divisor respectively. The second line contains a string consisting of exactly n digits.

출력
--

Output a single integer – the number of different partitions modulo 109 + 7.

제한
--

예제 입력 1
-------

4 2
1246

예제 출력 1
-------

4

예제 입력 2
-------

4 7
2015

예제 출력 2
-------

0

힌트
--

출처
--

[ICPC](/category/1) > [Regionals](/category/7) > [Europe](/category/10) > [Central European Regional Contest](/category/13) > [CERC 2015](/category/detail/1426) D번