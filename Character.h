#pragma once
class Character
{
    HBITMAP charBit;    //ĳ���� ��Ʈ�� ����

    int iCharX;     //ĳ������ x��ǥ
    int iCharY;     //ĳ������ y��ǥ

    int iBitX;      //��Ʈ�ʿ����� ĳ���� ��ǥ
    int iBitY;      //��Ʈ�ʿ����� ĳ���� ��ǥ

    int iCharAni;   //ĳ���� �ִϸ��̼��̿� ����

    int iSpeed;     //ĳ���� �̵��ӵ�

    int iPlayer;    //�÷��̾� ��ȣ

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

    void saveBitmap(HWND &hWnd);      //��Ʈ�� ������ ���� �Լ�

    void charPrint(HDC &hdc);       //ĳ���͸� �������
    void charMove(WPARAM wParam);    //ĳ���� �̵�

    bool charCol(int iDirection, int iMapX, int iMapY, int iWidth, int iHeight);     //ĳ���� �浹üũ
    bool rectCol(int iX_1, int iY_1, int iWidth_1, int iHeight_1, int iX_2, int iY_2, int iWidth_2, int iHeight_2);     //�簢���� ���ƴ��� üũ

    void charClear();       //ĳ���Ͱ� �׾����� �ʱ�ȭ
    void speedClear();      //�ӵ� �ʱ�ȭ
};

