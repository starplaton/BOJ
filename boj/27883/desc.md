# 27883번 - 가희와 노선 건설 놀이


=======================

1 초

1024 MB

197

66

62

44.286%

문제
--

가희는 지하철을 매우 좋아합니다. 그래서, 이번에도 지하철 게임을 샀습니다. 이 게임은 규칙이 매우 간단합니다.

*   `n`개의 역이 있습니다. 이들을 각각 `1`번 역, ... , `n`번 역이라고 부릅니다.
*   `a` < `b`일 때, `a`번 역과 `b`번 역의 거리는 `b` - `a`입니다.
*   컴퓨터는 매 턴마다 `x`번 역의 고도를 변화시키거나, 플레이어에게 질문을 합니다.
    *   모든 역 쌍 중 고도 차이가 가장 큰 역 쌍들이 있습니다. 그 중, 쌍을 이루는 두 역 사이의 거리가 가장 먼 쌍의 거리는 얼마인가요?
*   처음 `n`개의 역의 고도는 모두 0입니다.

이 게임이 모두 끝난 후, 가희는 컴퓨터가 변화시킨 지하철 노선을 감상하곤 했습니다. 그런데, 어느 날 잠수함 패치가 되면서, 게임이 끝나면 바로 초기 게임 화면으로 돌아가게 되었습니다. 실망한 가희는 이것 저것 둘러보다가, 이전 게임 기록에 가희가 질문에 답한 결과만이 남아 있음을 알게 되었습니다.

가희가 질문에 답한 결과가 주어졌을 때, 컴퓨터가 매 턴마다 어떤 행동을 했는지 알려주세요.

입력
--

첫 번째 줄에 역의 개수 `n`과 가희가 질문에 답한 횟수 `m`이 공백으로 구분되어 주어집니다.

그 다음 줄부터 `m`개의 줄에 가희의 답이 주어집니다.

출력
--

첫 번째 줄에 턴의 개수 `Q`를 출력해 주세요.

그 다음 줄부터 `Q`개의 줄에 아래 형식 중 하나로 쿼리를 출력해 주세요.

*   `U` `x` `h`
    *   `x`번째 역의 고도를 `h`로 업데이트 합니다. `h`가 0보다 크거나 같으면 지상역이고, 그렇지 않으면 지하역입니다.
*   `P`
    *   컴퓨터가 질문을 합니다.

출력 결과는 아래 조건을 만족해야 합니다.

*   역의 고도를 업데이트 하는 연산은 `8200`개 이하여야 합니다.
*   역의 고도는 `-10000` 보다 낮아질 수 없고, `10000` 보다 높아질 수 없습니다.

**답이 여러 개인 경우, 조건을 만족하는 것 아무 것이나 출력해도 정답으로 인정됩니다.**

제한
--

*   `5` ≤ `n` ≤ `7400`
*   `1` ≤ `m` ≤ `7400`
*   **가능한 경우**만 주어집니다.

예제 입력 1
-------

5 1
4

예제 출력 1
-------

1
P

힌트
--

출처
--

[Contest](/category/45) > [BOJ User Contest](/category/984) > [가희와 함께 하는 코딩 테스트](/category/529) > [가희와 함께 하는 5회 코딩테스트](/category/detail/3565) C번

*   문제를 검수한 사람: [chansol](/user/chansol), [eaststar](/user/eaststar), [egod1537](/user/egod1537), [kiwiyou](/user/kiwiyou), [utilforever](/user/utilforever)
*   문제를 만든 사람: [chogahui05](/user/chogahui05)