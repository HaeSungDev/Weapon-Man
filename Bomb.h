#pragma once
class Bomb
{
    int iBombX;  //��ź�� x��ġ
    int iBombY;  //��ź�� y��ġ

    int iBombPow;    //ĳ���Ͱ� ���� ��ź�� �Ŀ�
    
    int iBombAni;   //��ź �ִϸ��̼� ����
    int iPopAni;    //��ź ���� �ִϸ��̼� ����
    
    int iTime;   //��ź�� �ð�

    int iUse; //0 : ��ź ���� 1 : ��ź ��ġ �� 2 : ��ź ����

    int iCol[4];        //��ź�� ���⸶�� �浹üũ���ִ� ����

public:
    Bomb(void);
    ~Bomb(void);

    /* �� ����� �����ڿ� ������ */
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

    void bombClear();   //��ź ��� Ŭ����
};

