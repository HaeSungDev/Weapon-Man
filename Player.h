#pragma once
class Player : public Character, public Weapon
{
    int iTime;      //ĳ���Ͱ� �׾��ִ� �ð�

    int iLife;      //ĳ���� ��� ����

    bool bDead;     //ĳ���Ͱ� ����ִ��� ����

public:
    
    Player();
    ~Player(void);

    int getITime();     
    void setITime(int iSetTime);

    int getILife();
    void setILife(int iSetLife);

    bool getBDead();
    void setBDead(bool bSetDead);

    void playerDead(Player &player);    //���� ���Ŀ� ���� �浹üũ

    void dead();     //��� �ִϸ��̼�

    void eatBombPow();      //ȭ�� �������� ����
    void eatBombNum();      //��ź ���� ���� �������� ����
    void eatSpeed();        //�ӵ� ���� �������� ����

    void playerClear();      //ĳ���͸� �ٽ� �츮�� Ŭ����
    void allClear();       //��� ������� Ŭ����













};

