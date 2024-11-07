# 14195번 - DotB


===============

2 초

512 MB

49

24

21

56.757%

문제
--

The new DotA game is coming out soon. All the fans around the world are waiting to try the new version of DotA: ”DotB”.

There’s a lot of pressure on the developers of the game to add new heroes to it. They come up with ideas but not all of them are worth implementing. For one particular hero they are working on, they asked you to write a program to analyze one of its abilities. The hero’s name is ”Cave Man”, and his ability is to summon a crow to attack a line of enemies.

The line has n enemies with hitpoint h1h2...hn. The crow always starts at the first enemy and attacks each one and goes to the next. It attacks exactly n + 5 times in total, and if it reaches the end of the line, it continues the attack from the other end of the line.

The crow has the damage C. Which means C would be deducted from the enemy’s hitpoint if it receive an attack. If an enemy’s hitpoint hits zero or less, well ... he’s dead.

If the crow’s attack causes death of an enemy, the crow reverses its movement direction.

Now it’s your task to find which enemy receives the last attack of the crow, given the enemies’ hitpoint and the crow’s damage.

입력
--

The first line contains the number of test cases T.

Each test case begins with two space-separated integers n (2 ≤ n ≤ 32) and C (32 ≤ C ≤ 128). Then comes n integers indicating the initial hitpoint of the enemies. The ith integer indicates the hitpoint of ith enemy in the line.

출력
--

For each test case, print a single line containing the serial number of the enemy the crow finally attacks.

제한
--

예제 입력 1
-------

2
3 100
200 150 200
8 80
200 100 100 100 100 80 160 200

예제 출력 1
-------

2
3

힌트
--

출처
--

[ICPC](/category/1) > [Regionals](/category/7) > [Asia West Continent](/category/464) > [Iran](/category/163) > [Iran Internet Programming Contest](/category/172) > [IIPC 2016](/category/detail/1612) B번