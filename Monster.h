#pragma once
class Monster : public Weapon
{
    int iMonBitX;   //��Ʈ�ʿ��� ������ x��ǥ

    int iAniTime;   //�ִϸ��̼� �ð�üũ

    int iMsgTime;   //�޼��� �����ð� üũ

    int iMonX;      //������ x��ǥ
    int iMonY;      //������ y��ǥ

    int iHP;        //������ ü��

    bool bDead;     //���Ͱ� �׾����� true �ƴϸ� false
    bool bMessage;  //�޼��� ����

    HBITMAP monBit;     //���� ��Ʈ��

    HBRUSH redBrush;    //������ 

public:
    Monster(void);
    ~Monster(void);

    int getIHP();

    int getIMonX();
    int getIMonY();

    bool getBDead();

    void saveBitmap(HWND &hWnd);        //��Ʈ���� �����Ѵ�

    void monsterPrint(HDC &hdc);        //���͸� �����
    void energyPrint(HDC &hdc);     //ü�¹ٸ� ���
    void monHitAni();      //���Ͱ� �´� �ִϸ��̼�

    void decreaseHP(int (*iMap)[XMAP], Player &player);     //��ź�� �¾����� ���� HP����
    
    void attack();      //������ ��������

    void monsterClear(int (*iMap)[XMAP]);    //������ �ʱ�ȭ
};