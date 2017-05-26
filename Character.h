#pragma once
class Character
{
    HBITMAP charBit;    //캐릭터 비트맵 저장

    int iCharX;     //캐릭터의 x좌표
    int iCharY;     //캐릭터의 y좌표

    int iBitX;      //비트맵에서의 캐릭터 좌표
    int iBitY;      //비트맵에서의 캐릭터 좌표

    int iCharAni;   //캐릭터 애니메이션이용 변수

    int iSpeed;     //캐릭터 이동속도

    int iPlayer;    //플레이어 번호

public:

    Character();
    ~Character(void);

    void setIPlayer(int iSetPlayer);

    int getICharX();
    int getICharY();

    int getIBitX();

    void setIBitX(int iSetBitX);
    void setIBitY(int iSetBitY);

    void increaseSpeed();
    int getISpeed();

    void saveBitmap(HWND &hWnd);      //비트맵 저장을 위한 함수

    void charPrint(HDC &hdc);       //캐릭터를 출력해줌
    void charMove(WPARAM wParam);    //캐릭터 이동

    bool charCol(int iDirection, int iMapX, int iMapY, int iWidth, int iHeight);     //캐릭터 충돌체크
    bool rectCol(int iX_1, int iY_1, int iWidth_1, int iHeight_1, int iX_2, int iY_2, int iWidth_2, int iHeight_2);     //사각형이 겹쳤는지 체크

    void charClear();       //캐릭터가 죽었을때 초기화
    void speedClear();      //속도 초기화
};

