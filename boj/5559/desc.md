# 5559번 - JOI 깃발


================

5 초

128 MB

393

137

74

30.705%

문제
--

일본 정보올림피아드 위원회는 일본 정보올림피아드(JOI)를 홍보하기 위해서 JOI로고를 모티브로 한 깃발을 만들었다. 깃발은 "좋은 깃발" 이어야 한다. "좋은 깃발"은 알파벳 J, O, I중 하나의 문자를 M행 N열 사각형 형태로 배치한 것으로, 아래 그림과 같이 배치되어 있는 곳이 깃발에 적어도 한 곳 있는 깃발이다.

![](/upload/images/joi1.png)

다음은 "좋은 깃발"의 예이다.

![](/upload/images/joi2.png)

다음은 "좋은 깃발"이 아닌 예이다.

![](/upload/images/joi3.png)

일부 위치에는 이미 그 칸을 채울 문자가 정해져 있다. 이때, M, N이 주어졌을 때, 좋은 깃발을 만들 수 있는 방법의 수를 구하는 프로그램을 작성하시오.

입력
--

첫째 줄에 깃발의 크기 M과 N이 주어진다. (2 ≤ M, N ≤ 20)

다음 M개 줄에는 깃발의 모양인 N개 문자가 주어진다. 각 문자는 J, O, I, ?중 하나이다. J, O, I인 경우에는 i행 j열 위치의 문자가 이미 그 문자로 정해져 있는 뜻이고, ?는 아직 정해져 있지 않다는 뜻이다.

출력
--

첫째 줄에 "좋은 깃발"을 만들 수 있는 방법의 수를 100000으로 나눈 나머지를 출력한다.

제한
--

예제 입력 1
-------

2 3
??O
IIJ

예제 출력 1
-------

4

예제 입력 2
-------

2 2
??
??

예제 출력 2
-------

3

예제 입력 3
-------

3 3
??I
???
O?J

예제 출력 3
-------

53

예제 입력 4
-------

5 4
JOI?
????
????
????
?JOI

예제 출력 4
-------

28218

힌트
--

예제 1의 경우 아래와 같이 좋은 깃발을 만들 수 있다.

![](/upload/images/joi4.png)

출처
--

[![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)](https://creativecommons.org/licenses/by-sa/4.0/)

[Olympiad](/category/2) > [Japanese Olympiad in Informatics](/category/100) > [Japanese Olympiad in Informatics Qualification Round](/category/101) > [JOI 2010/2011 예선](/category/detail/547) 6번

*   문제를 번역한 사람: [baekjoon](/user/baekjoon)