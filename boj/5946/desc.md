# 5946번 - The Trough Game


=========================

1 초

128 MB

73

45

43

65.152%

문제
--

Farmer John and Bessie are playing games again. This one has to do with troughs of water.

Farmer John has hidden N (1 <= N <= 20) troughs behind the barn, and has filled some of them with food. Bessie has asked M (1 <= M <= 100) questions of the form, "How many troughs from this list (which she recites) are filled?".

Bessie needs your help to deduce which troughs are actually filled.

Consider an example with four troughs where Bessie has asked these questions (and received the indicated answers):

    1) "How many of these troughs are filled: trough 1"
       -->  1 trough is filled

    2) "How many of these troughs are filled: troughs 2 and 3"
       -->  1 trough is filled

    3) "How many of these troughs are filled: troughs 1 and 4"
       -->  1 trough is filled

    4) "How many of these troughs are filled: troughs 3 and 4"
       -->  1 trough is filled

*   From question 1, we know trough 1 is filled.
*   From question 3, we then know trough 4 is empty.
*   From question 4, we then know that trough 3 is filled.
*   From question 2, we then know that trough 2 is empty.

입력
--

*   Line 1: Two space-separated integers: N and M
*   Lines 2..M+1: A subset of troughs, specified as a sequence of contiguous N 0's and 1's, followed by a single integer that is the number of troughs in the specified subset that are filled.

출력
--

*   Line 1: A single line with:
    *   The string "IMPOSSIBLE" if there is no possible set of filled troughs compatible with Farmer John's answers.
    *   The string "NOT UNIQUE" if Bessie cannot determine from the given data exactly what troughs are filled.
    *   Otherwise, a sequence of contiguous N 0's and 1's specifying which troughs are filled.

제한
--

예제 입력 1
-------

4 4
1000 1
0110 1
1001 1
0011 1

예제 출력 1
-------

1010

힌트
--

출처
--

[Olympiad](/category/2) > [USA Computing Olympiad](/category/106) > [2010-2011 Season](/category/121) > [USACO December 2010 Contest](/category/123) > [Silver](/category/detail/617) 3번