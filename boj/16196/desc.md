# 16196번 - 중국 신분증 번호


====================

2 초

512 MB

697

142

124

23.574%

문제
--

중국의 시민은 모두 신분증 번호를 가지고 있다. 신분증 번호는 18자리이다. 처음 17자리는 숫자이고, 마지막 1자리는 숫자이거나 'X'이다.

처음 17자리는 3개의 연속된 부분으로 나누어져 있다. 각각의 부분은 차례대로 지역 코드, 생일 코드, 순서 코드를 의미한다.

*   지역 코드는 6자리이다. 올바른 지역 코드는 정부에 의해 미리 정해져 있으며, 여기에 포함되지 않은 6자리 코드는 모두 올바른 지역 코드가 아니다.
*   생일 코드는 8자리이고, YYYYMMDD 형식이다. 처음 4자리는 연도, 다음 2자리는 월, 마지막 2자리는 일을 의미한다.
    *   월, 일이 1자리 수인 경우에는 앞에 0을 붙여 2자리로 만들어야 한다.
    *   올바른 생일 코드는 1900년 1월 1일부터 2011년 12월 31일 사이에 있는 날을 의미해야 한다.
*   순서 코드는 3자리 숫자이다. 3자리 숫자는 임의로 정해지며, "000"은 불가능하다. 나머지 수는 모두 올바른 순서 코드이다. 순서 코드가 홀수인 경우에는 남자를 의미하고, 짝수인 경우에는 여자를 의미한다.

신분증 번호의 마지막 숫자는 체크섬 코드이고, 수식을 통해서 계산해야 한다. 신분증 번호의 처음 17자리 숫자를 A1, A2, ..., A17이라고 했을 때, 아래 방정식을 이용해서 체크섬 코드를 구해야 한다.

x + A1×217 + A2×216 + A3×215 + ... + A16×22 + A17×21 ≡ 1 (mod 11)

위의 방정식을 만족하는 x는 항상 하나만 존재한다. 이 때, x가 10이면 체크섬 코드가 'X'이고, 그 외의 경우에는 x가 체크섬 코드이다.

신분증 번호 하나와 올바른 지역 코드의 목록이 주어졌을 때, 신분증 코드가 올바른지 아닌지, 올바른 경우에는 남자인지 여자인지 구하는 프로그램을 작성하시오.

입력
--

첫째 줄에 신분증 번호가 주어진다. 신분증 번호는 18자리이고, 처음 17자리는 0부터 9까지 숫자로만 이루어져 있다. 마지막 1자리는 0부터 9까지 숫자이거나 'X'이다.

둘째 줄에는 올바른 지역 코드의 개수 N(1 ≤ N ≤ 50)이 주어진다. 

셋째 줄부터 N개의 줄에는 올바른 지역 코드가 한 줄에 하나씩 주어진다. 지역 코드는 6자리이고, 0부터 9까지 숫자로만 이루어져 있다. 또, 0으로 시작하지 않는다. 입력으로 주어지는 지역 코드는 중복되지 않는다.

출력
--

입력으로 주어진 신분증 번호가 올바르지 않은 경우에는 "I"를 출력한다. 올바르면서 남자인 경우에는 "M"을, 여자인 경우에는 "F" 를 출력한다.

제한
--

예제 입력 1
-------

441323200312060636
1
441323

예제 출력 1
-------

M

예제 입력 2
-------

62012319240507058X
1
620123

예제 출력 2
-------

F

예제 입력 3
-------

321669197204300886
2
610111
659004

예제 출력 3
-------

I

예제 입력 4
-------

230231198306900162
1
230231

예제 출력 4
-------

I

예제 입력 5
-------

341400198407260005
1
341400

예제 출력 5
-------

I

예제 입력 6
-------

520381193206090891
2
532922
520381

예제 출력 6
-------

I

힌트
--

출처
--

*   문제를 번역한 사람: [baekjoon](/user/baekjoon)
*   문제의 오타를 찾은 사람: [inhau](/user/inhau)