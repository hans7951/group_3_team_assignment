# group_3_team_assignment
locate_elevator 함수 : 유리판과 바닥의 물 웅덩이를 생성함
locate_cube 함수 :직육면체의 기둥을 생성함
판 함수 :건물내에서 층을 만들음
기본틀 함수 :건물의 외각을 형성함
locate_heart 함수 : 각 층에서 하트 모양이 만들어지는 역할을 함
locate_clover 함수 :각 층에서 클로버 모양이 만들어지는 역할을 함
locate_space 함수 : 각 층에서 스페이스 모양이 만들어지는 역할을 함
locate_diamond 함수 : 각 층에서 다이아몬드 모양이 만들어지는 역할을 함
stage_1 함수 : x,y,z값을 입력받아 건물의 위치를 설정해 생성하고 건물내에서 구멍을 만들음

woolColor 함수 : color변수의 값이 1 증가할 때마다 양털의 색깔이 빨주노초파남보 순으로 바뀌도록 만듦
                순서가 보라색이면 color값을 0로 만들어 사이클이 다시 돌아가도록 만듦
                
# STAGE_2
stage_2 함수 : 주어진 값을 Drop_stage_2 함수에 보내줌. 
Drop_stage_2 함수 : 바닥 중심의 위치와 그 높이를 받고 그것을 이용하여 각 (x, z)마다 최고점을 구한 뒤 그 위치를 Install_stage_2 함수에 보내줌.
Install_stage_2 함수 : 어떤 위치부터 그 바닥까지 자리에 블록을 놓아 기둥을 세움.

# stage_3
locate_rail, locate_oval, locate_circle 함수를 이용하여 동굴을 만들어낸다. 먼저 안에 원기둥모양으로 비어있는 직육면체를 생성하고 locate_oval안에서 난수를 생성하여 광물의 종류를 정하고 원기둥의 둘레에 난수에 따라 sin함수와 cos함수로 무작위로 배치한다. 그리고 locate_rail함수로 저장된 위치에 가로 세로 방향을 반복하며 배치한다. 마지막으로 locate_circle로 용암과 물을 채운다.

# stage_5
기본틀 함수와 locate_number함수를 이용하여 영화 메트릭스와 같은 분위기를 내는 맵을 만든다. locate_number함수는 0모양과 1모양이 저장 되어있고 인자인 number에 따라 모양을 결정하며 direction에 따라 어떤 평면에 어느방향으로 배치할 것인지 정한다. xy평면에 배치할것이면 add_1과 add_3은 x와 y에 더해지고 zy평면에 배치할것이면 add_1과 add_3은 z와 y에 더해지고 xz평면에 배치할것이면 add_1과 add_3은 x와 z에 더해지며 블록이 배치된다. stage_5에서는 locate_number에 난수를 생성하여 전달하고 이 난수를 통해 0과 1 둘중 하나를 고르며 난수를 생성하여 xy와 zy평면에서 숫자들이 몇 개씩(가로 방향으로) 붙어있을지 정한다. xz평면에서는 중앙에는 저장된 위치에 배치되고 그 의외에 곳은 난수를 통해 주어진 범위내에 무작위로 생성된다. 마지막으로 바닥에 물이 배치된다.

# youtube 영상
https://youtu.be/IGVjWBt5QZA
