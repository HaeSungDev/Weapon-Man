#pragma once
class Weapon
{
    Bomb bomb[MAXBOMB];     //폭탄 배열 선언

    int (*iMap)[XMAP];       //맵 파일을 저장할 포인터 선언(충돌체크 및 값 조작을 위해서 가져온다)

    int iBombNum;       //가지고 있는 폭탄 개수

    int iBombPow;       //전체 폭탄의 파워

    HBITMAP bombBit;    //폭탄 비트맵 저장
    HBITMAP popBit;     //폭파 비트맵 저장

public:
    Weapon(void);
    ~Weapon(void);

    Bomb* getBomb();

    void increaseNum();
    int getIBombNum();

    void increasePow();
    int getIBombPow();

    void setMap(int (*iSetMap)[XMAP]);  //맵 배열 주소 저장
    void saveWeaponBitmap(HWND &hWnd);   //비트맵 저장, 오버로딩 구분을 위한 변수를 둠

    void bombPut(int iX, int iY);     //폭탄을 놓는 함수

    void bombPrint(HDC &hdc);   //폭탄 출력
    void bombAni();     //폭탄 애니메이션

    void popPrint(HDC &hdc);    //폭파 출력
    void popAni(Bomb *other_1, Bomb *other_2, int iNum_1, int iNum_2);      //폭파 애니메이션

    void blockClear(int iPlace);      //벽돌 제거
    void popEnd(int iPlace);    //폭파가 끝났을때 해줄 작업

    void bombTimer();      //폭탄 시간 체크

    void bombBlockCol(Bomb* bomb, int iPlace);      //블록 제거 및 폭탄 폭파
    void bombCol(Bomb *other, int iNum, int iPlace);     //폭탄과 폭탄끼리 충돌체크 

    int randomItem();      //랜덤하게 아이템을 등장시켜줌

    void weaponClear();    //모든 무기를 클리어
};