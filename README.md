# AssortRockTeam
어소트락 팀플 깃헙
---

## 명칭
### 현대 - 사무실 - 주인공
### 과거 - 멀티레벨 - 전우치

## 임무 목록
- 전투 
- 잠입 
- 호위

## 레벨 목록
- 사무실
- 목탑(타겟 - 황룡사 9층목탑) : 전투형
- 몽유도원도[임시] : 잠입형
- 000 : 호위형

## 사무실 구성요소
- 진행상황판
- 사무용품
- 레벨별 시그니처 오브젝트
- 상호작용 액터

---
<br><br>

# 임무별 구성요소

## 전투형
- 잡몹 : 일반병사 ~~/ 몬스터류~~
- 보스 : 장군 ~~/ 호랑이(모델 구할 수 있으면)~~

## 잠입형
- 일정 위치를 반복해서 이동하는 병사
- 병사 시야범위 체크용 데칼
- 시야 거리별 위험도
- 벽에 부적을 던지면 시간이 표시되고 그 시간동안 벽 뒤 움직임 보임

<br>

```
## 호위형

- 호위 오브젝트
- 일정 거리 이상 떨어지면 안내문구 > 오브젝트 이동에 따라
- 랜덤 1회 ~ 3회 산적 등장
```

---
<br><br>

# 기존 프로젝트 파일에 구현된 요소
- [전투형] 레벨 (레벨만)
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

<iframe width="1382" height="786" src="https://www.youtube.com/embed/OE8u0wtV1Ag" title="UE4 Sword Basic Animation set" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

- 봉 담당자

<iframe width="1382" height="786" src="https://www.youtube.com/embed/9kiyHn2liUI" title="UE4 Spear Animation" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

- 활 담당자 
> <br>
> [Mixamo 사용] <br><br>

<br>

`아마도 검 담당자가 임무 작업을 먼저 하게될듯`

기본 무기는 검과 봉을 사용
활은 원거리 무기라는 특성상 잠입 액션에서 사용


---
<br><br><br><br>

### 정말 시간이 남아돈다 싶으면 할거
```
- 배그처럼 벽뒤에서 고개만 숙여서 오른쪽 왼쪽 시야 넓히기
- 병사, 장군 패턴 추가
- 병사, 장군 AI 개선
- 전우치 주먹액션 추가
```