# 17081번 - RPG Extreme


======================

5 초

1024 MB

3317

815

540

21.574%

문제
--

![](https://upload.acmicpc.net/ad60f113-37b3-4ea5-918a-8fc8165f93c4/-/preview/)

요즘 택희는 RPG 게임을 하고 있다. 던전을 헤쳐나가며 몬스터를 물리치고, 아이템을 모으고, 레벨 업을 하여 보스 몬스터를 물리치는 전형적인 RPG 게임이다.

이 게임은 _N_×_M_ 2차원 그리드 위에서 진행되며, 그리드의 각 칸에는 아래와 같은 것들이 있을 수 있다.

*   빈 칸(.) : 자유롭게 입장할 수 있는 칸이다. 주인공(@)은 처음에 빈 칸에서 시작한다.
*   벽(#) : 막힌 칸이다. 이 칸으로는 움직일 수 없다.
*   아이템 상자(B)
    *   아이템 상자에는 장비 중 한 가지가 들어 있다.
    *   장비는 무기(W), 갑옷(A), 장신구(O) 3가지로 구분되며, 알파벳 대문자는 해당 타입의 이름이다.
    *   아이템 상자를 열어서 아이템을 얻었을 경우, 무기 / 방어구는 얻은 장비로 교체되고, 장신구의 경우엔 착용할 수 있는 칸이 남았을 경우, 그리고 동일한 효과의 장신구를 착용하지 않고 있을 경우에만 얻은 장신구를 착용한다. 장신구에 대한 설명은 아래의 주인공에 대한 설명에서 자세히 다룬다.
    *   아이템 상자가 열리고 나면, 해당 칸은 빈 칸이 된다. 주인공은 아이템 상자를 연 이후, 아이템 상자가 있던 칸으로 이동하게 된다.
*   가시 함정(^)
    *   가시 함정은 밟았을 때 5의 데미지를 입으며, 이 데미지로 인해 사망할 수도 있다.
    *   함정은 밟더라도 사라지지 않는다.
    *   만약 함정 위에서 입력받은 커맨드 방향으로 움직일 수 없어 제자리에 멈추는 경우, 해당 함정을 또 밟은 것이 된다.
*   몬스터(&)
    *   몬스터는 알파벳 대소문자 문자열로 된 이름, 정수로 표시되는 공격력, 방어력, 체력, 쓰러뜨렸을 때 얻을 수 있는 경험치 값을 갖고 있다.
    *   몬스터가 있는 칸에 입장할 경우, 몬스터와의 전투가 벌어진다. 항상 주인공 캐릭터가 선공을 하며, 한 번씩 번갈아가며 공격하여 각자 _max_(1, 내 공격력 - 상대의 방어력) 만큼의 데미지를 서로에게 한 번씩 입힌다. 한 쪽의 체력이 0 이하가 될 경우 전투는 즉시 종료된다.
    *   몬스터가 사망할 경우, 그 자리는 빈 칸이 된다. 주인공은 승리했을 경우 이 칸으로 이동한다.
    *   전투가 시작되고, 캐릭터 혹은 몬스터가 죽을 때 까지의 모든 과정은 한 턴 내에 이루어진다.
*   보스 몬스터(M)
    *   몬스터와 동일하다. 게임의 목표는 보스 몬스터를 처치하는 것이다.

주인공은 처음에 빈 칸 하나에서 시작한다. 주인공 캐릭터에 대한 정보는 아래와 같다.

*   체력, 공격력, 방어력 : 정수로 표시된다. 초기 값은 체력 20, 공격력 2, 방어력 2이다.
*   경험치 : 처음엔 레벨 1이며, 레벨 _N_에서 _N_+1이 되기 위한 필요 경험치는 5×_N_이다.
    *   레벨이 오를 경우, 최대 HP가 5, 공격력과 방어력이 2씩 상승한 뒤 HP가 모두 회복된다.
    *   경험치를 얻어 레벨이 오르게 되면, 남는 경험치는 버려진다. 예를 들어, 다음 레벨까지 필요한 경험치가 3인 상태에서 5의 경험치를 얻는다면, 레벨이 오른 다음, 남은 2의 경험치는 버려지고 0의 경험치를 갖고 있는 상태가 된다.
*   무기 : 한 개만 착용할 수 있다. 각 무기는 공격력 값을 가지며, 이 값이 주인공의 공격력에 더해진다.
    *   무기로 인한 공격력은 다른 모든 공격력 상승 효과보다 먼저 적용된다. 즉, 모든 다른 공격력 상승 효과는 무기의 공격력까지 같이 상승시킨다.
*   방어구 : 한 개만 착용할 수 있다. 각 방어구는 방어력 값을 가지며, 이 값이 주인공의 방어력에 더해진다.
*   장신구 : 최대 4개까지 착용할 수 있으나, 동일한 효과의 장신구는 최대 하나까지만 착용 가능하다. 각 장신구에는 여러 효과가 있으며, 목록은 아래와 같다.
    *   HP Regeneration(HR) : 전투에서 승리할 때마다 체력을 3 회복한다. 체력은 최대 체력 수치까지만 회복된다.
    *   Reincarnation(RE) : 주인공이 사망했을 때 소멸하며, 주인공을 최대 체력으로 부활시켜 준 뒤, 주인공을 첫 시작 위치로 돌려보낸다. 레벨이나 장비 등의 다른 정보는 변함이 없다. 전투 중이던 몬스터가 있다면 해당 몬스터의 체력도 최대치로 회복된다. 소멸한 뒤에 다시 이 장신구를 얻는다면 또 착용한다.
    *   Courage(CO) : 모든 전투에서, 첫 번째 공격에서 주인공의 공격력(무기 합산)이 두 배로 적용된다. 즉, 모든 첫 공격에서 몬스터에게 _max_(1, 공격력×2 – 몬스터의 방어력)만큼의 데미지를 입힌다.
    *   Experience(EX) : 얻는 경험치가 1.2배가 된다. 소수점 아래는 버린다.
    *   Dexterity(DX) : 가시 함정에 입는 데미지가 1로 고정되며, Courage 장신구와 함께 착용할 경우, Courage의 공격력 효과가 두 배로 적용되는 대신 세 배로 적용된다.
    *   Hunter(HU) : 보스 몬스터와 전투에 돌입하는 순간 체력을 최대치까지 회복하고, 보스 몬스터의 첫 공격에 0의 데미지를 입는다.
    *   Cursed(CU) : 아무 능력이 없으며, 그냥 장신구 한 자리를 차지한다.

주인공의 한 턴은 다음과 같은 순서대로 이루어진다.

*   주인공이 상하좌우로 한 칸 이동한다.
*   그 칸이 빈칸이라면 아무 일도 없이 지나가고, 아이템 상자, 가시 함정, 몬스터, 보스몬스터가 있을 경우 위에서 기술한 대로 각 칸에 대한 행동을 한다.

주인공은 상하좌우로 한 칸씩 이동할 수 있으며, 주인공의 이동은 _L_, _R_, _U_, _D_로 이루어진 문자열 하나로 미리 모두 주어진다. _L_은 왼쪽, _R_은 오른쪽, _U_는 위, _D_는 아래를 의미한다. 움직일 수 없는 명령(벽으로 들어가거나, 그리드 밖으로 나가는 등)이 주어질 수도 있는데, 이 경우 제자리에서 이동하지 않는다.

게임은 보스 몬스터를 처치하거나, 주인공이 (전투 또는 가시 함정에 의해) HP가 0 이하가 되어 죽거나, 입력된 문자열에 해당하는 모든 커맨드를 마쳤을 때 끝난다. 보스 몬스터를 처치해서 게임이 끝날 경우, 보스 몬스터의 경험치를 획득하고, 필요하다면 레벨 업이나 장신구 효과 등도 모두 진행한 뒤 게임이 끝나게 된다. 만약 입력이 끝나지 않았으나 게임이 끝났을 경우, 남은 입력은 모두 무시한다. 게임이 끝난 이후에는 아래와 같은 순서대로 게임의 결과를 출력해야 한다. <, > 안에 표시된 단어는 <, > 내부의 내용을 적절히 대체하고, <, >를 제거하여 출력한다.

*   그리드의 상태 : _N_개의 줄에 _M_개의 문자로 출력한다.
    *   주인공 : @ 
        *   주인공이 있는 칸은 그 칸에 무엇이 있든(함정 등) @으로 출력한다.
        *   만약 사망하였을 경우, 주인공은 그리드에서 사라진다. 즉, 패배한 게임에서는 @의 출력이 없다.
    *   빈 칸 : .
    *   벽 : #
    *   보스가 아닌 몬스터 : & (살아있을 경우)
    *   보스 몬스터 : M (살아있을 경우)
    *   가시 함정 : ^
    *   아이템 상자 : B (열리지 않았을 경우)
*   진행된 턴 수 _T_에 대해, 아래의 문자열
    *   Passed Turns : _T_
    *   게임은 0턴에서 시작한다. 즉, 첫 이동을 마친 뒤 게임이 끝난다면 1턴이 지난 것이다.
*   종료 시점의 주인공의 정보에 대해, 아래의 문자열
    *   LV : <_N_\>
        *   _N_은 주인공의 현재 레벨이다.
    *   HP : <_REM_\>/<_CUR_\>
        *   _REM_은 현재 남은 체력, _CUR_는 최대 체력이다.
        *   만약 남은 체력이 0 미만일 경우, _REM_은 0이다.
    *   ATT : <_N_\>+<_W_\>
        *   _N_은 무기가 적용되지 않은 주인공의 공격력 값이다.
        *   _W_는 착용 중인 무기의 공격력이다. 무기가 없다면 이 값은 0이다.
    *   DEF : <_N_\>+<_A_\>
        *   _N_은 방어구가 적용되지 않은 주인공의 방어력 값이다.
        *   _A_는 착용 중인 방어구의 방어력이다. 방어구가 없다면 이 값은 0이다.
    *   EXP : <_CUR_\>/<_MAX_\>
        *   _CUR_은 현재 경험치량, _MAX_는 다음 레벨이 되는 데에 필요한 총 경험치량이다.
*   게임의 결과
    *   보스 몬스터를 처치했을 경우 : YOU WIN!
    *   죽었을 경우 : YOU HAVE BEEN KILLED BY <_S_\>..
        *   전투의 결과로 사망했을 경우 _S_는 몬스터의 이름, 가시 함정에 의해 사망했을 경우 _S_는 “SPIKE TRAP” 이 된다.
    *   입력이 끝났을 경우 : Press any key to continue.

출력 예제를 참고하면 더 쉽게 알 수 있다. 각 아이템 상자의 내용물이나, 몬스터의 정보 등은 입력으로 모두 주어지며, 입력 형식은 설명을 참조한다.

여기까지 읽었다면 무엇을 해야 할 지 파악했을 것이다. 최선을 다해보도록 하자!

입력
--

첫 줄에 그리드의 크기 _N_과 _M_이 주어진다. (1 ≤ _N_, _M_ ≤ 100, 2 ≤ _N_×_M_)

다음 줄부터 _N_개의 줄에 걸쳐 _M_개의 문자로 그리드의 상태가 주어진다. 주어지는 문자는 모두 본문에 설명된 것 중 하나이다.

보스 몬스터에 해당하는 ‘M’과, 주인공에 해당하는 ‘@’은 정확히 한 개씩 있다.

그 다음 줄에는 _L_, _R_, _U_, _D_로 이루어진 문자열 S가 주어진다. (1 ≤ |_S_| ≤ 5,000) 주인공은 문자열 _S_의 첫 글자부터 순서대로 실행한다.

이 그리드에 있는 몬스터의 수(보스 몬스터 포함)를 _K_라 하자. 이제 _K_줄에 걸쳐 각 몬스터의 정보가 아래와 같이 주어진다.

*   _R C S W A H E_ (1 ≤ _R_ ≤ _N_, 1 ≤ _C_ ≤ _M_, 1 ≤ |_S_| ≤ 10, 1 ≤ _W_, _A_, _H_, _E_ ≤ 20)
    *   위에서부터 _R_번째 줄, 왼쪽에서부터 _C_번째 열에 있는 몬스터에 대한 정보이다. 이 칸에는 몬스터가 있음이 보장된다.
    *   _S_는 몬스터의 이름으로, 알파벳 대소문자로만 이루어진 1글자 이상, 10글자 이하의 문자열이다.
        *   보스 몬스터를 포함해 모든 몬스터의 이름은 서로 다르다.
    *   _W_는 몬스터의 공격력 값이다.
    *   _A_는 몬스터의 방어력 값이다.
    *   _H_는 몬스터의 최대 체력이다.
    *   _E_는 몬스터를 쓰러뜨렸을 때 얻을 수 있는 경험치이다.
*   모든 몬스터에 대한 정보는 정확히 한 번씩 주어진다.

이후, 그리드에 있는 아이템 상자의 수를 _L_이라 할 때, _L_줄에 걸쳐 각 상자의 정보가 아래와 같이 주어진다.

*   _R C T_ <_S_\> (1 <= _R_ <= _N_, 1 <= _C_ <= _M_, _T_ ∈ { 'W', ‘A’, ‘O’ })
*   위에서부터 _R_번째 줄, 왼쪽에서부터 _C_번째 열에 있는 아이템 상자에 대한 정보이다. 이 칸에는 아이템 상자가 있음이 보장된다.
*   _T_ = 'W', 'A'일 경우
    *   <_S_\> = _N_ (1 ≤ _N_ ≤ 10)
    *   _T_ = 'W'일 경우 공격력이 _N_인 무기를, _T_ \= 'A'일 경우 방어력이 _N_인 방어구를 의미한다.
*   _T_ = 'O'일 경우
    *   <_S_\> ∈ { "HR", "RE", "CO", "EX", "DX", "HU", "CU" }
    *   각 효과를 가진 장신구임을 의미한다. 자세한 내용은 본문을 참조한다.
*   모든 아이템 상자에 대한 정보가 정확히 한 번씩 주어진다.

출력
--

_N_개의 줄에 _M_개의 문자로 게임이 끝난 시점의 그리드의 최종 상태를 출력한다.

_N_+1번째 줄에 진행된 턴 수를 Passed Turns : _T_ 의 형태로 출력한다.

_N_+2번째 줄부터 _N_+6번째 줄까지, 주인공의 상태를 출력 예제의 형식대로 출력한다. 각 값의 의미는 본문을 참조한다.

_N_+7번째 줄에, 게임의 결과를 본문에 설명한 형식대로 출력한다.

아래 예제 중 첫 세 개는 가능한 세 가지 게임 결과에 대한 출력 형식을 모두 담고 있으므로 참고하면 좋을 것이다.

제한
--

예제 입력 1
-------

7 8
.&....&.
..B.&..&
B...&...
.B@.B#..
.&....M.
.B...B..
..B^^&..
RRRUULLULUDDDLDRDRDRRRURRULUULLU
3 5 One 4 2 10 3
2 5 Two 10 2 8 3
1 2 Three 20 2 14 7
5 2 Four 16 2 16 5
7 6 Five 16 5 16 12
5 7 Boss 2 9 20 2
1 7 EO 20 1 1 4
2 8 ET 10 5 4 10
4 5 W 4
2 3 O CO
3 1 A 10
4 2 A 2
6 2 O DX
7 3 O HU
6 6 W 3

예제 출력 1
-------

......&.
.......&
B.......
.....#..
......@.
........
...^^...
Passed Turns : 27
LV : 3
HP : 29/30
ATT : 6+3
DEF : 6+2
EXP : 14/15
YOU WIN!

예제 입력 2
-------

6 6
BBBB^&
....&.
&...BB
B.B#.&
B&.@#B
...#MB
UURRDDURDLRRLLLDUULUUUURRRLRRDLDRRDDDLRRD
5 2 One 2 2 19 4
3 1 Two 2 2 12 2
2 5 Three 4 5 16 9
4 6 Four 20 13 20 8
6 5 Boss 10 20 11 20
1 6 Etc 20 20 20 20
1 1 O EX
1 2 O CU
1 3 O CO
1 4 O CU
3 5 O DX
3 6 O RE
4 1 A 10
5 1 W 10
4 3 W 5
5 6 W 1
6 6 A 1

예제 출력 2
-------

....^&
......
......
..B#..
....#.
...#M.
Passed Turns : 38
LV : 3
HP : 0/30
ATT : 6+1
DEF : 6+1
EXP : 9/15
YOU HAVE BEEN KILLED BY Boss..

예제 입력 3
-------

6 6
@.BB.M
..##B.
BB....
##.###
&&.&&&
&#..#&
RRRRRDDRRDDLLDURRRRRDULLLUURRRU
1 6 Boss 20 20 20 20
5 2 One 5 2 2 5
5 1 Two 5 4 6 6
6 1 Three 5 4 10 6
5 4 Four 8 4 8 7
5 5 Five 8 4 8 10
5 6 Six 3 3 10 20
6 6 Seven 8 8 1 4
1 3 O RE
1 4 O HR
3 1 W 2
3 2 A 2
2 5 A 10

예제 출력 3
-------

.....M
..##B@
......
##.###
......
.#..#.
Passed Turns : 31
LV : 5
HP : 40/40
ATT : 10+2
DEF : 10+2
EXP : 4/25
Press any key to continue.

예제 입력 4
-------

5 5
B^^#M
^^^#.
&^@##
^^^^#
^^^^^
UULLDDDDRRRRULUULUUULDDDDLUUURRRDDRR
1 5 Boss 10 5 2 3
3 1 Easy 1 1 1 10
1 1 O DX

예제 출력 4
-------

.^^#M
^^^#.
.^.##
^^^^#
^^^^^
Passed Turns : 34
LV : 2
HP : 0/25
ATT : 4+0
DEF : 4+0
EXP : 0/10
YOU HAVE BEEN KILLED BY SPIKE TRAP..

예제 입력 5
-------

5 5
B^^#M
^^^#.
&^@##
^^^^#
^^^^^
UULLDDDDRRRRULUULUUULDDDDLUUURRRDDRR
1 5 Boss 10 5 2 3
3 1 Easy 1 1 1 10
1 1 O RE

예제 출력 5
-------

.^^#M
^^^#.
&^.##
^^^^#
^^^^^
Passed Turns : 9
LV : 1
HP : 0/20
ATT : 2+0
DEF : 2+0
EXP : 0/5
YOU HAVE BEEN KILLED BY SPIKE TRAP..

예제 입력 6
-------

8 8
..B.&..&
.B&B#B#B
.#...B..
M#.&.&..
.@B.#&..
.&#.&B..
###BBB.&
&B.##...
LRLDLUDLDLDRDUURULUDRLDRLDLURD
1 5 HNUHXA 3 3 6 4
1 8 LxfsUy 2 2 10 2
2 3 BgtXGo 5 3 12 4
4 1 miUjvv 3 2 6 3
4 4 bjeHPC 2 2 4 1
4 6 qOMYnk 5 2 4 4
5 6 jpYpUQ 5 2 7 4
6 2 GfGskF 6 3 7 4
6 5 dzxXYp 3 3 5 1
7 8 GUmyAf 6 2 13 1
8 1 wECzzs 3 2 3 3
1 3 O DX
2 2 O RE
2 4 O CO
2 6 W 2
2 8 W 7
3 6 O CU
5 3 A 6
6 6 O DX
7 4 O DX
7 5 A 5
7 6 O RE
8 2 O RE

예제 출력 6
-------

..B.&..&
.B&B#B#B
.#...B..
M#.&.&..
..B.#&..
.&#.&B..
###BBB.&
&B.##...
Passed Turns : 12
LV : 1
HP : 0/20
ATT : 2+0
DEF : 2+0
EXP : 0/5
YOU HAVE BEEN KILLED BY GfGskF..

예제 입력 7
-------

8 8
##&&.&.&
B.&&B#.#
#..#....
#..&@&&#
&..&.#&.
&#&....&
#&..&..&
&.M.#.##
URLDRRURRUDRRDLRLUUDRRDRRLRULU
1 3 nMgvJf 4 2 11 6
1 4 XxqSmr 2 2 9 9
1 6 sWXDGn 6 1 7 9
1 8 RDkfra 6 1 6 6
2 3 cnIShV 5 3 10 9
2 4 tlAMAV 5 1 7 8
4 4 ThyjkB 6 3 9 10
4 6 oewIOe 3 3 10 7
4 7 mnBiQu 5 2 10 8
5 1 geDyeA 3 3 11 8
5 4 eChkWg 3 1 2 7
5 7 JYsSkN 5 2 13 8
6 1 tpsySF 3 3 2 6
6 3 CUMSDn 4 1 10 7
6 8 IjiBXl 4 3 5 8
7 2 ogdOhi 6 2 1 9
7 5 DzAkbI 6 2 7 6
7 8 KZEaHY 5 1 9 6
8 1 DtVSBD 3 2 12 7
8 3 dkMqDO 4 2 7 6
2 1 O HU
2 5 O EX

예제 출력 7
-------

##&&.&.&
B.&&B#@#
#..#....
#..&...#
&..&.#&.
&#&....&
#&..&..&
&.M.#.##
Passed Turns : 30
LV : 2
HP : 21/25
ATT : 4+0
DEF : 4+0
EXP : 8/10
Press any key to continue.

예제 입력 8
-------

4 5
&&&B#
...&.
&#&B.
@BBM&
RDDDULUDLRRRRUULRDDL
1 1 CBdyeX 4 3 5 10
1 2 jGZOLx 3 1 6 7
1 3 FOeeDv 5 1 2 10
2 4 PbTbcv 3 2 3 8
3 1 MFoVDB 6 1 4 6
3 3 lxTGpq 6 3 5 7
4 4 GYddRJ 6 3 3 10
4 5 KJlYKE 3 3 3 8
1 4 A 4
3 4 W 2
4 2 W 5
4 3 O HR

예제 출력 8
-------

&&&B#
...&.
.#&B.
...@&
Passed Turns : 12
LV : 3
HP : 30/30
ATT : 6+5
DEF : 6+0
EXP : 0/15
YOU WIN!

예제 입력 9
-------

5 4
.@#.
.B.B
BB.&
B&..
&M.&
ULRRDRURDLRLDRLLRDURRRDUL
3 4 KcUWry 7 5 8 4
4 2 yoKqoR 4 5 8 7
5 1 bZkdGd 5 4 11 8
5 2 gKrJBh 8 2 9 6
5 4 xqFzGM 3 2 9 4
2 2 W 1
2 4 A 8
3 1 O HU
3 2 O RE
4 1 O HU

예제 출력 9
-------

..#.
....
BB..
B.@.
&M..
Passed Turns : 25
LV : 2
HP : 23/25
ATT : 4+1
DEF : 4+8
EXP : 4/10
Press any key to continue.

예제 입력 10
--------

5 6
BB&^M.
&####.
^&.B..
...#&#
.@..&.
RRRUULLLLUUURRRRRDDDLL
5 5 One 4 1 5 3
4 5 Two 4 1 6 3
3 2 Three 13 1 5 6
2 1 Four 11 2 7 4
1 3 Five 13 2 10 3
1 5 Boss 14 3 13 10
3 4 A 4
1 1 O RE
1 2 O CU

예제 출력 10
--------

...^@.
.####.
^.....
...#.#
......
Passed Turns : 16
LV : 3
HP : 3/30
ATT : 6+0
DEF : 6+4
EXP : 13/15
YOU WIN!

힌트
--

출처
--

[University](/category/5) > [연세대학교](/category/334) > [2019 연세대학교 컴퓨터과학과 프로그래밍 경진대회](/category/detail/2024) J번

*   문제를 만든 사람: [ae04071](/user/ae04071), [portableangel](/user/portableangel)