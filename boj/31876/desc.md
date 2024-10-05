# 31876번 - 자존심 강한 두 천재의 대결


==========================

0.5 초 (추가 시간 없음)

1024 MB (추가 메모리 없음)

430

76

55

21.318%

문제
--

지금 한양대학교 ERICA캠퍼스는 에리-카드라는 게임이 선풍적인 유행을 끌고 있다! 에리-카드는 1:1 카드 대결게임으로, 각자 한 장씩 제시한 카드에 적힌 전투력이라는 수치를 비교하여 더 큰 쪽이 승리하는 게임이다.

자존심이 강한 두 천재인 라스와 아욱은 에리-카드를 통해서 서로의 서열을 정리하려고 한다. 다만 라스가 제시한 전투력 $A$는 $u$진법 정수, 아욱이 제시한 카드에 적힌 전투력 $B$는 $v$진법 정수로 표기되어 있어 게임을 진행하는 데 어려움을 겪고 있다. 각자 카드에 적힌 수의 길이는 같다. 즉, 각 전투력을 이루는 숫자의 개수는 동일하다.

두 사람을 위해 각자가 제시한 카드를 보고 둘 중 누가 승리하였는지 알려주도록 하자.

입력
--

첫 번째 줄에 정수 $u, v$가 공백을 사이에 두고 주어진다. $(2 \\leq u, v \\leq 10)$

두 번째 줄에 $u$진법으로 표기된 라스의 전투력 $A$가 주어진다. $(0 \\leq A < u^{3\\,000\\,000})$

세 번째 줄에 $v$진법으로 표기된 아욱의 전투력 $B$가 주어진다. $(0 \\leq B < v^{3\\,000\\,000})$

$A$, $B$는 값이 $0$일 때를 제외하고는 $0$으로 시작하지 않는다. 즉, leading zero는 없다.

출력
--

첫 번째 줄에 라스가 승리할 경우 `ras`를, 아욱이 승리할 경우 `auq`을, 전투력이 같아 승패를 가를 수 없다면 `rasauq`을 출력한다.

제한
--

예제 입력 1
-------

10 4
1122
2211

예제 출력 1
-------

ras

예제 입력 2
-------

3 4
1122
2211

예제 출력 2
-------

auq

예제 입력 3
-------

5 4
1234
3002

예제 출력 3
-------

rasauq

힌트
--

출처
--

[University](/category/5) > [한양대학교 ERICA 캠퍼스](/category/418) > [2024 한양대학교 ERICA 프로그래밍 경시대회 HEPC](/category/1036) > [Zero Division](/category/detail/4215) H번

[University](/category/5) > [한양대학교 ERICA 캠퍼스](/category/418) > [2024 한양대학교 ERICA 프로그래밍 경시대회 HEPC](/category/1036) > [One Division](/category/detail/4216) G번

[University](/category/5) > [한양대학교 ERICA 캠퍼스](/category/418) > [2024 한양대학교 ERICA 프로그래밍 경시대회 HEPC](/category/1036) > [Open Contest](/category/detail/4217) K번

*   문제를 검수한 사람: [bsyun0571](/user/bsyun0571), [firstin0907](/user/firstin0907), [gs22059](/user/gs22059), [hellogaon](/user/hellogaon), [hyoseok](/user/hyoseok), [khj20006](/user/khj20006), [kjmin622](/user/kjmin622), [putdata](/user/putdata), [qsccsq22](/user/qsccsq22), [rabbit007](/user/rabbit007), [tony9402](/user/tony9402)
*   문제를 만든 사람: [rasauq1122](/user/rasauq1122)