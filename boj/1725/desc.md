# 1725번 - 히스토그램


===============

0.7 초

128 MB

29423

11118

7877

39.533%

문제
--

히스토그램에 대해서 알고 있는가? 히스토그램은 아래와 같은 막대그래프를 말한다.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/upload/201006/hist.PNG)

각 칸의 간격은 일정하고, 높이는 어떤 정수로 주어진다. 위 그림의 경우 높이가 각각 2 1 4 5 1 3 3이다.

이러한 히스토그램의 내부에 가장 넓이가 큰 직사각형을 그리려고 한다. 아래 그림의 빗금 친 부분이 그 예이다. 이 직사각형의 밑변은 항상 히스토그램의 아랫변에 평행하게 그려져야 한다.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/upload/201006/histo.PNG)

주어진 히스토그램에 대해, 가장 큰 직사각형의 넓이를 구하는 프로그램을 작성하시오.

입력
--

첫 행에는 N (1 ≤ N ≤ 100,000) 이 주어진다. N은 히스토그램의 가로 칸의 수이다. 다음 N 행에 걸쳐 각 칸의 높이가 왼쪽에서부터 차례대로 주어진다. 각 칸의 높이는 1,000,000,000보다 작거나 같은 자연수 또는 0이다.

출력
--

첫째 줄에 가장 큰 직사각형의 넓이를 출력한다. 이 값은 20억을 넘지 않는다.

제한
--

예제 입력 1
-------

7
2
1
4
5
1
3
3

예제 출력 1
-------

8

힌트
--

출처
--

[Contest](/category/45) > [University of Ulm Local Contest](/category/170) > [University of Ulm Local Contest 2003](/category/detail/750) H번

*   문제를 번역한 사람: [author5](/user/author5)
*   데이터를 추가한 사람: [bamgoesn](/user/bamgoesn), [boreng0817](/user/boreng0817), [kcan1416](/user/kcan1416), [wlsgur0717](/user/wlsgur0717), [yjinpark](/user/yjinpark)
*   빠진 조건을 찾은 사람: [sait2000](/user/sait2000)