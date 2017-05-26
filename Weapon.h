#pragma once
class Weapon
{
    Bomb bomb[MAXBOMB];     //��ź �迭 ����

    int (*iMap)[XMAP];       //�� ������ ������ ������ ����(�浹üũ �� �� ������ ���ؼ� �����´�)

    int iBombNum;       //������ �ִ� ��ź ����

    int iBombPow;       //��ü ��ź�� �Ŀ�

    HBITMAP bombBit;    //��ź ��Ʈ�� ����
    HBITMAP popBit;     //���� ��Ʈ�� ����

public:
    Weapon(void);
    ~Weapon(void);

    Bomb* getBomb();

    void increaseNum();
    int getIBombNum();

    void increasePow();
    int getIBombPow();

    void setMap(int (*iSetMap)[XMAP]);  //�� �迭 �ּ� ����
    void saveWeaponBitmap(HWND &hWnd);   //��Ʈ�� ����, �����ε� ������ ���� ������ ��

    void bombPut(int iX, int iY);     //��ź�� ���� �Լ�

    void bombPrint(HDC &hdc);   //��ź ���
    void bombAni();     //��ź �ִϸ��̼�

    void popPrint(HDC &hdc);    //���� ���
    void popAni(Bomb *other_1, Bomb *other_2, int iNum_1, int iNum_2);      //���� �ִϸ��̼�

    void blockClear(int iPlace);      //���� ����
    void popEnd(int iPlace);    //���İ� �������� ���� �۾�

    void bombTimer();      //��ź �ð� üũ

    void bombBlockCol(Bomb* bomb, int iPlace);      //��� ���� �� ��ź ����
    void bombCol(Bomb *other, int iNum, int iPlace);     //��ź�� ��ź���� �浹üũ 

    int randomItem();      //�����ϰ� �������� ���������

    void weaponClear();    //��� ���⸦ Ŭ����
};