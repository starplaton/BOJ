# 14710번 - 고장난 시계


=================

0.5 초

512 MB

1490

768

663

52.745%

문제
--

논산훈련소에 간 불쌍한 상언이는 첫날 훈련소에서 다쳐 먼 거리를 이동할 때 버스를 타고 다녔다. 어느 날 버스를 탄 상언이는 훈련소 버스 앞에 붙어있는 아날로그 시계를 보게 되었는데, 시계가 이상해 보인다는 사실을 관찰했다. 일반적인 시계라면 가리킬 수 없는 시간을 가리키고 있던 것이다. 이 시계를 본 상언이는 어떤 시계의 시침과 분침이 가리키는 방향을 보면 그 시계가 고장 났는지 정상인지 판단할 수 있을 거라 생각했지만, 귀찮아서 생각을 그만두기로 했다. 상언이를 대신해서 시계가 정상인지 이상한지 알려주자.

정상적인 시계는 12시 정각에 시침과 분침이 둘 다 정확히 12시 방향을 가리키며, 시침은 12시간에 한 바퀴, 분침은 1시간에 한 바퀴를 시계 방향으로 등속도로 움직인다.

입력
--

첫 번째 줄에 시침의 각도 θ1, 분침의 각도 θ2 (0 ≤ θ1, θ2 ≤ 359)가 정수로 주어진다. 시침, 분침의 각도는 12시 방향을 기준으로 시계방향으로 잰다. 예를 들어 3시 방향은 90, 9시 방향은 270 이다.

출력
--

첫 번째 줄에 시계의 각도가 정상인 경우 O를, 그렇지 않을 경우 X를 출력한다.

제한
--

예제 입력 1
-------

180 0

예제 출력 1
-------

O

예제 입력 2
-------

0 180

예제 출력 2
-------

X

힌트
--

첫 번째 예시는 시침이 6시 방향을, 분침이 12시 방향을 가리키고 있는 상태로 6시 정각의 시계 모양이다.

두 번째 예시는 시침이 12시 방향을, 분침이 6시 방향을 가리키고 있는 상태로 정상적인 시계에선 나올 수 없는 모양이다.

출처
--

[University](/category/5) > [서울대학교](/category/354) > [2017 서울대학교 프로그래밍 경시대회](/category/682) > [Division 2](/category/detail/1755) B번

*   문제를 만든 사람: [pse1202](/user/pse1202)