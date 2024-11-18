# 16282번 - Black Chain


======================

0.1 초

512 MB

2252

758

581

37.436%

문제
--

n개의 블랙 고리가 일렬로 연결된 체인이 있다. 블랙 고리 하나는 무게가 정확히 1g 이다. 이 고리들을 이용하여 1g 부터 _n_g 까지 가능한 모든 무게를 생성하려고 한다. 이를 위해 고리를 일부 풀어야 하는데, 고리를 푸는데 힘이 들어 최소 개의 고리만 풀기를 원한다. 예를 들어 아래의 그림 A.1 처럼 7 개의 고리로 구성된 블랙 체인이 있다고 하자. 이 체인에서 3 번 고리 하나를 풀어 내면 그림 A.2 처럼 3 번 고리 1 개와 두 개의 체인(1~2 번 고리가 연결된 체인과 4~7 번 고리가 연결된 체인)으로 분리된다. 이들을 이용하면 그림 A.3 처럼 1g 부터 7g 까지의 모든 무게를 생성할 수 있다.

![](https://upload.acmicpc.net/84c90735-fd4c-4678-80a1-9abf12a9fab6/-/preview/)

그림 A.1: 길이가 7 인 블랙 체인

![](https://upload.acmicpc.net/c77fe2b3-587c-4266-9c20-8a5129f6baad/-/preview/)

그림 A.2: 3 개로 분리된 블랙 체인

무게

1g

2g

3g

4g

5g

6g

7g

고리  
구성

`[3]`

`[1-2]`

`[3]`  
`[1-2]`

`[4-7]`

`[3]`  
`[4-7]`

`[1-2]`  
`[4-7]`

`[3]`  
`[1-2]`  
`[4-7]`

그림 A.3: 1g 부터 7g 까지 가능한 모든 무게를 생성하는 고리 구성

_n_개의 고리가 연결된 체인이 주어져 있을 때, 1g 부터 _n_g 까지 가능한 모든 무게를 생성하기 위해 풀어야 할 고리의 최소 개수를 구하는 프로그램을 작성하시오.

입력
--

입력은 표준입력을 사용한다. 첫 번째 줄에 블랙 고리의 개수를 나타내는 양의 정수 _n_ (3 ≤ _n_ ≤ 1018)이 주어진다.

출력
--

출력은 표준출력을 사용한다. 1g 부터 _n_g 까지 가능한 모든 무게를 생성하기 위해 풀어야 할 고리의 최소 개수를 출력한다.

제한
--

예제 입력 1
-------

7

예제 출력 1
-------

1

예제 입력 2
-------

20

예제 출력 2
-------

2

힌트
--

출처
--

[ICPC](/category/1) > [Regionals](/category/7) > [Asia Pacific](/category/42) > [Korea](/category/211) > [Nationwide Internet Competition](/category/256) > [Seoul Nationalwide Internet Competition 2018](/category/detail/1935) A번