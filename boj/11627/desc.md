# 11627번 - Godzilla


===================

2 초

256 MB

77

27

20

32.258%

문제
--

Godzilla is rampaging through Tokyo again. Luckily, the Superior Defender Mech Force (SDMF) has sent its mech units to stop Godzilla’s attack. Mech units are gigantic bipedal robots, usually piloted by Japanese teenagers, that carry weapons of superior destruction. The weapons are so powerful that one hit should neutralize the Godzilla threat.

The SDMF faces two challenges. First, the mech units are so big that they cannot walk over any residential sectors, as they would then trample the people of Tokyo. Second, the weapons of the mech units are so powerful that the pilots cannot afford to fire them at Godzilla while there are any residential sectors between the firing mech and Godzilla.

The SDMF wants to run some simulations before it faces the Godzilla threat. The simulations are based on a two-dimensional map of the area of Tokyo where Godzilla is running amock. The passing of time happens between rounds, where in each round there are two turns. In the first turn, Godzilla gets to do a move. In the second turn, the mech units are allowed a move. In a single move, Godzilla moves one sector on the map in the directions North, East, South or West.

Godzilla is lacking in brain matter and has a very predictable movement scheme. First, Godzilla does not move into a sector that he already visited. Each round, on the first turn:

*   It looks for any houses to destroy that are adjacent to him. If the sector adjacent to him is a residential sector, it will move to that sector and destroy the sector. When a residential sector is destroyed, it becomes a ruined sector instead. Godzilla looks around him in the order North, East, South, West. So, it will first look to the North to see whether there is a residential sector. If so, it will move there. Otherwise, he will look East to see if there is a residential sector to destroy, and so on.
*   In the event that there are no residential sectors adjacent to Godzilla, he will try to move North. If that move would move him outside the map or into a sector he already visited, he will instead try to move East. If he cannot move East, he will move South. In the case that he cannot move South, he will try to move West instead. The terrifying presence of a mech will not stop Godzilla from moving into the sector that is occupied by a mech unit. In that case, Godzilla is considered to be in range of the mech unit’s weapons of superior destruction, in the next turn.
*   If Godzilla has no move options left, he will instead start roaring and wail his arms, inflicting no damage to Tokyo city.

Each round, on the second turn, each mech unit can either stay at its position, or move to an adjacent non-residential sector, or a ruined sector. It cannot move outside the map. When moving, a mech unit moves one sector in one of the directions North, East, South or West. It is allowed to move into the space of another mech unit. At the moment that a mech unit is able to fire its weapons at Godzilla, it will do so on the mech units’ turn. Mech units can move and fire in the same turn. A mech can fire its weapons at Godzilla if there is a straight horizontal or vertical line between the mech and Godzilla, and the line is not obstructed by any residential sectors.

Given a map of the Tokyo area where Godzilla is rampaging and the starting location of the mechs, determine the minimum number of residential sectors that will be destroyed before Godzilla can be neutralized by a mech unit.

입력
--

The input starts with a line containing an integer T, the number of test cases. Then for each test case:

*   One line containing two space-separated integers L (3 ≤ L ≤ 1000) and W (3 ≤ W ≤ 1000), the length and width of the map of Tokyo in sectors, respectively.
*   W lines, containing L characters, describing the map of Tokyo. The characters are:
    *   ‘.’: a non-residential sector;
    *   ‘R’: a residential sector;
    *   ‘G’: the starting position of Godzilla. This is always a non-residential sector;
    *   ‘M’: the starting position of a mech unit. This is always a non-residential sector.

The sector at the top-left corner of the map represents the North-West corner of Tokyo, while the sector at the bottom-right corner of the map represents the South-East corner of Tokyo.

The simulation will contain at most 100 mech units.

It will always be possible for Godzilla to be neutralized by a mech unit.

출력
--

For each test case, output one line containing a single integer: the minimum number of residential sectors that will be destroyed before Godzilla can be neutralized by a mech unit.

제한
--

예제 입력 1
-------

2
3 3
RR.
G..
M.R
7 5
M...RR.
...G...
...RRR.
.......
..RR..M

예제 출력 1
-------

1
2

힌트
--

출처
--

[![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)](https://creativecommons.org/licenses/by-sa/4.0/)

[ICPC](/category/1) > [Regionals](/category/7) > [Europe](/category/10) > [Northwestern European Regional Contest](/category/15) > [Benelux Algorithm Programming Contest](/category/89) > [BAPC 2015](/category/detail/1427) C번