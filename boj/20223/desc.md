# 20223번 - Kangaroo Commotion


=============================

7 초

512 MB

157

50

29

25.439%

문제
--

Bushfires are threatening your habitat! Being a kangaroo, you must inform the other kangaroos in your troop as fast as possible and flee to a safe area.

You are currently standing still, and you will jump to the other kangaroos' locations. You will visit the other kangaroos in a specific order so that all of them have sufficient time to escape. After visiting all other kangaroos you must continue jumping to the safe area, where you should come to a stop.

With each jump you move a (possibly negative) integer distance north and/or east. Because of your limited muscle power, you are only able to accelerate or decelerate at most $1$ in each direction each jump. Formally, if jump $i$ moves you $v\_{x,i}$ to the north and $v\_{y, i}$ to the east, the next jump $i+1$ must satisfy $|v\_{x, i+1} - v\_{x, i}| \\leq 1$ and $|v\_{y, i+1} - v\_{y, i}| \\leq 1$.

Find the minimal number of jumps needed to go from your current position to the safe area via all other kangaroos, without leaving the grid. It is very important to come to a full stop at the end, so the last jump must both start and end at the safe area.

The first sample is shown in figure K.1.

![](https://upload.acmicpc.net/25a66a91-ee18-4891-ae14-a0d2887a1888/-/preview/)

Figure K.1: Visualisation of Sample 1 showing one possible way to get to the safe area using $9$ jumps.

입력
--

The input consists of:

*   A line containing three integers $r$, $c$ ($1\\leq r, c \\leq 50$), the number of rows and columns of the grid, and $k$ ($1\\leq k\\leq 5$), the number of other kangaroos you need to warn.
*   $r$ lines each consisting of $c$ characters. A "`.`" indicates an open space and a "`#`" indicates a bush where you can't jump. Your start position is indicated by a "`0`" and the characters "$1$" to $k$ indicate the positions of the other kangaroos you need to warn _in this order_. The position indicated by $k+1$ indicates the safe area where you should come to a stop.

출력
--

If it is possible to reach the safe area, then output the minimal number of steps needed to reach the safe area. Otherwise, output "`impossible`".

제한
--

예제 입력 1
-------

5 5 1
0..2.
.###.
.....
.....
.#.#1

예제 출력 1
-------

9

예제 입력 2
-------

2 2 2
03
12

예제 출력 2
-------

4

예제 입력 3
-------

1 5 1
.0#21

예제 출력 3
-------

8

예제 입력 4
-------

3 4 1
#0##
#.#2
1###

예제 출력 4
-------

impossible

힌트
--

출처
--

[![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)](https://creativecommons.org/licenses/by-sa/4.0/)

[ICPC](/category/1) > [Regionals](/category/7) > [Europe](/category/10) > [Northwestern European Regional Contest](/category/15) > [Benelux Algorithm Programming Contest](/category/89) > [BAPC 2020 Preliminaries](/category/detail/2346) K번

*   문제를 만든 사람: Abe Wits