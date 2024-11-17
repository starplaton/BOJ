# 1501번 - 영어 읽기


===============

2 초

128 MB

2166

491

336

21.401%

문제
--

혹시 인터넷을 하다가, 다음과 같은 식의 문장을 본 적이 있는가?

It is itnersetnig taht pepole can raed smoe grabeld wrods.

원래의 문장은 'It is interesting that people can read some garbled words'이다. 각각의 단어들은 제일 첫 문자와 제일 끝 문자를 제외하고는 순서가 뒤섞여 있다. 한 대학에서 시행한 연구 조사 결과에 따르면, (영어 단어를 아는 사람의 경우) 첫 문자와 제일 끝 문자가 일치하고, 그 사이의 문자들은 순서가 어떻게 뒤바뀌어 있더라도 읽는 데 지장이 없다고 한다.

그렇다보니, 한 단어가 여러 단어로 해석될 수도 있다. 예를 들어 abcde와 같은 단어는, abcde, abdce, acbde, acdbe, adbce, adcbe 같은 단어들로 해석될 수도 있다. 물론 각각의 단어들이 실제로 존재하는 단어(사전에 존재하는 단어)일 경우에만 의미가 있다.

영어 문장이 주어졌을 때, 그 문장을 해석하는 방법의 경우의 수를 구하는 프로그램을 작성하시오. 각각의 단어는, 첫 글자와 끝 글자가 일치하는 다른 단어(사전에 존재하는)로 해석할 수 있다. 영어 문장은 하나 이상의 단어로 이루어져 있으며, 각 단어들은 공백으로 구분되어 있다.

입력
--

첫째 줄에 사전에 있는 단어들의 개수 N(0 ≤ N ≤ 10,000)이 주어진다. 다음 N개의 줄에는 각 줄에 하나씩, 영어 사전에 있는 단어들이 주어진다. 각 단어의 길이는 100자를 넘지 않는다. 다음 줄에 해석할 문장의 개수 M(0 ≤ M ≤ 10,000)이 주어진다. 다음 M개의 줄에는 각 줄에 하나씩 문장이 주어진다. 각 문장의 길이는 10,000자를 넘지 않는다. 영어 단어는 알파벳 대소문자(구별됨)로만 이루어진다.

출력
--

M개의 줄에, 각 문장을 해석하는 경우의 수를 출력한다. 답은 32-bit signed int 범위 안에 있다고 가정하자.

제한
--

예제 입력 1
-------

3
ababa
aabba
abcaa
2
ababa
abbaa

예제 출력 1
-------

2
2

예제 입력 2
-------

14
bakers
brakes
breaks
binary
brainy
baggers
beggars
and
in
the
blowed
bowled
barn
bran
1
brainy bakers and beggars bowled in the barn

예제 출력 2
-------

48

힌트
--

출처
--

[University](/category/5) > [Tu-Darmstadt Programming Contest](/category/213) > [TUD Contest 2005](/category/detail/905) 7번