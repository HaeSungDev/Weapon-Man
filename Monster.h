#pragma once
class Monster : public Weapon
{
    int iMonBitX;   //비트맵에서 몬스터의 x좌표

    int iAniTime;   //애니메이션 시간체크

    int iMsgTime;   //메세지 구동시간 체크

    int iMonX;      //몬스터의 x좌표
    int iMonY;      //몬스터의 y좌표

    int iHP;        //몬스터의 체력

    bool bDead;     //몬스터가 죽었으면 true 아니면 false
    bool bMessage;  //메세지 구동

    HBITMAP monBit;     //몬스터 비트맵

    HBRUSH redBrush;    //붉은색 

public:
    Monster(void);
    ~Monster(void);

    int getIHP();

    int getIMonX();
    int getIMonY();

    bool getBDead();

    void saveBitmap(HWND &hWnd);        //비트맵을 저장한다

    void monsterPrint(HDC &hdc);        //몬스터를 출력함
    void energyPrint(HDC &hdc);     //체력바를 출력
    void monHitAni();      //몬스터가 맞는 애니메이션

    void decreaseHP(int (*iMap)[XMAP], Player &player);     //폭탄을 맞았을때 몬스터 HP감소
    
    void attack();      //몬스터의 공격패턴

    void monsterClear(int (*iMap)[XMAP]);    //몬스터의 초기화
};