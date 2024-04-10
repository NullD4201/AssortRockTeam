# AssortRockTeam
어소트락 팀플 깃헙
---

|기간|내용|
|:--|:--|
|2024.03.21~2024.03.27|+ 김원종 : 창 에셋 데이터 활용해서 공격 콤보 적용하고 데미지 콜리전 작성 <br> + 민재홍 : 검 에셋 활용해서 공격 콤보 적용, 데미지 콜리전 작성 <br> + 배지훈 : 믹사모 내 활쏘는 애니메이션 다운로드 후 블렌더 활용하여 베이스 수정 및 적용|
|~2024.04.10|- AI 마무리 <br>- 잡입 맵 AI 배치, 부적 배치 <br>- Player의 AI Target 시 움직임, AI 시야 기능|
|~2024.04.16|- 전투맵 구현<br>- AI 보스 구현 <br>- Player 스태미너, HP 등 UI 구현 <br>- Player 데미지 설정 및 회피 기능 설정|
|~2024.04.18|버그수정 작업|
|||

## 콘셉트
```
역사학자인 주인공이 논문을 작성하던 중 발견한 족자에서 전우치를 만나 
현대에 훼손되거나 약탈당한 유물들을 과거를 바꾸면서 복원한다.
```

## 명칭
### 현대 - 사무실 - 주인공
### 과거 - 멀티레벨 - 전우치

## 임무 목록
- 전투 
- 잠입 

## 레벨 목록
- 사무실
- 목탑(타겟 - 황룡사 9층목탑) : 전투형
- 몽유도원도[임시] : 잠입형

## 사무실 구성요소
- 진행상황판
- 사무용품
- 레벨별 시그니처 오브젝트
- 상호작용 액터

---
<br><br>

# 임무별 구성요소

## 전투형
- 잡몹 : 일반병사

## 잠입형
- 일정 위치를 반복해서 이동하는 병사
- 병사 시야범위 체크용 데칼
- 시야 거리별 위험도


---
<br><br>

# 기존 프로젝트 파일에 구현된 요소
- [**전투형**] 레벨 (레벨만)
- 사무실
- 박물관
- 진행상황판
- 사무용품
- 상호작용 액터

---
<br><br>

# 무기류
## 전우치가 사용하는 무기는 검(칼), 봉, 활
- 검 담당자 

[![사용할 에셋](https://cdn1.epicgames.com/ue/product/Thumbnail/SwordBasicAnimation_thumb-284x284-7974ad6a6889f2926ebf42931b32735c.png?resize=1&w=300)](https://youtu.be/OE8u0wtV1Ag)

- 봉 담당자

[![사용할 에셋](https://cdn1.epicgames.com/ue/product/Thumbnail/SpearGlaiveAnimation_thumb-284x284-a51e829dae26d7ee09d483cf60223433.png?resize=1&w=300)](https://youtu.be/9kiyHn2liUI)

- 활 담당자 [Mixamo 사용]

`아마도 검 담당자가 임무 작업을 먼저 하게될듯`

기본 무기는 검과 봉을 사용
활은 원거리 무기라는 특성상 잠입 액션에서 사용


---
<br><br><br><br>

### 별도 다운로드 필요 에셋
> 폴더 경로를 그대로 설정할 것

<br>

./Content/Characters/ | ./Content/ThirdPerson/ | ./Content/StarterContent/<br>
> UE5 Default StarterContent 

- [./Content/BasicInteraction/](https://www.unrealengine.com/marketplace/ko/product/basic-interaction-widgets-notes)

- [./Content/SpearAnimation/](https://www.unrealengine.com/marketplace/ko/product/spear-glaive-animation)

- [./Content/SwordBasicAnimation/](https://www.unrealengine.com/marketplace/ko/product/sword-basic-animation)

- [./Content/InfinityBladeWeapons/](https://www.unrealengine.com/marketplace/ko/product/infinity-blade-weapons)

- [./Content/HouseOfChangwon/](https://www.unrealengine.com/marketplace/ko/product/house-of-changwon)

- [./Content/KoreanTraditionalMartialArts/](https://www.unrealengine.com/marketplace/ko/product/korean-traditional-martial-arts)