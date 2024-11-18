# 15566번 - 개구리 1


================

1 초

256 MB

802

237

181

29.194%

문제
--

연못 안에 개구리들이 있을 수 있는 연꽃 N개와, 연꽃 사이를 연결하는 다리 역할의 통나무 M개가 있다. 같은 연꽃 쌍을 연결하는 통나무의 개수는 1개 이하이다. 여기에 N마리의 개구리가 각각 하나의 연꽃에서 휴식을 취하려 한다.

통나무를 통해 연결된 두 연꽃에 있는 개구리들은 다툼이 없기 위해 대화가 잘 통해야 한다. 개구리들의 대화 주제는 4개로, 각각 음식, 취미, 가족, 철학이다. 각각의 개구리는 각 주제에 대해 흥미도를 1부터 5까지의 수 중 하나로 가진다.

각각의 통나무마다 대화 주제가 결정되어 있는데, 대화는 그 주제에 대해 두 개구리의 흥미도가 일치하면 이루어진다.

또한, 각 개구리는 선호하는 연꽃이 1개 또는 2개가 있으며, 그 외의 연꽃에서는 불만을 가져 난장판을 만들 것이므로 모든 개구리는 자기가 선호하는 연꽃에 가야 한다.

개구리를 적절히 배치해 모든 통나무에서 정해진 주제로 대화가 가능한지, 불가능한지와 가능하다면 그 방법을 알아내는 프로그램을 작성하여라.

입력
--

첫 줄에 _N_과 _M_이 입력된다. (1 ≤ N ≤ 15, 0 ≤ M ≤ min(N(N-1)/2, 100))

둘째 줄부터 _N_줄 동안 각각의 개구리의 음식, 취미, 가족, 철학에 대한 흥미도가 네 정수로 입력된다. 각각의 정수는 1부터 5사이에 있다.

다시 _N_개의 줄 동안 각각의 개구리가 선호하는 연꽃의 번호 _A_와 _B_가 주어진다. (1 ≤ _A_, _B_ ≤ _N_) 만약 어떤 개구리가 선호하는 연꽃이 하나라면 _A_ = _B_이다.

다음 _M_줄 동안 세 정수 _A_, _B_, _T_가 주어진다. (1 ≤ _A_, _B_ ≤ _N_, 1 ≤ _T_ ≤ 4) 이는 _A_번째 연꽃과 _B_번째 연꽃을 연결하는 통나무가 있으며, 통나무의 대화 주제가 _T_번째 주제임을 뜻한다. (주제는 음식, 취미, 가족, 철학 순이다.)

출력
--

가능한 배치 방법이 있다면 첫째 줄에 YES를 출력한다. 다음 줄에는 첫 번째 연꽃부터 각각의 연꽃에 배치할 개구리의 번호를 공백으로 구분해 출력한다. 방법이 여러 가지가 있다면 아무거나 출력해도 좋다.

가능한 배치 방법이 없다면 첫째 줄에 NO를 출력한다.

제한
--

예제 입력 1
-------

8 10
1 1 1 1
1 2 3 4
2 2 3 1
2 5 4 4
1 5 5 2
4 4 4 2
4 1 5 5
4 4 4 4
1 5
7 2
6 3
4 4
8 5
6 6
7 1
8 6
1 2 1
2 3 3
2 8 4
3 4 1
4 8 4
4 5 2
8 6 1
5 6 4
7 8 1
6 7 1

예제 출력 1
-------

YES
1 2 3 4 5 6 7 8

힌트
--

출처
--

[Contest](/category/45) > [BOJ User Contest](/category/984) > [웰노운컵](/category/416) > [제1회 웰노운컵](/category/detail/1851) E1번

*   문제를 만든 사람: [jh05013](/user/jh05013), [moonrabbit2](/user/moonrabbit2), [veydpz](/user/veydpz)