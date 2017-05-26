#pragma once
class Bomb
{
    int iBombX;  //폭탄의 x위치
    int iBombY;  //폭탄의 y위치

    int iBombPow;    //캐릭터가 가진 폭탄의 파워
    
    int iBombAni;   //폭탄 애니메이션 변수
    int iPopAni;    //폭탄 폭파 애니메이션 변수
    
    int iTime;   //폭탄의 시간

    int iUse; //0 : 폭탄 없음 1 : 폭탄 설치 됨 2 : 폭탄 터짐

    int iCol[4];        //폭탄의 방향마다 충돌체크해주는 변수

public:
    Bomb(void);
    ~Bomb(void);

    /* 각 멤버의 접근자와 수정자 */
    int* getICol();

    void setIBombX(int iSetBombX);
    int getIBombX();

    void setIBombY(int iSetBombY);
    int getIBombY();

    void setIBombPow(int iSetBombPow);
    int getIBombPow();

    void setIBombAni(int iSetBombAni);
    int getIBombAni();

    void setIPopAni(int iSetPopAni);
    int getIPopAni();

    void setITime(int iSetTime);
    int getITime();

    void setIUse(int iSetUse);
    int getIUse();

    void bombClear();   //폭탄 요소 클리어
};

