#pragma once
class Player : public Character, public Weapon
{
    int iTime;      //캐릭터가 죽어있는 시간

    int iLife;      //캐릭터 목숨 개수

    bool bDead;     //캐릭터가 살아있는지 여부

public:
    
    Player();
    ~Player(void);

    int getITime();     
    void setITime(int iSetTime);

    int getILife();
    void setILife(int iSetLife);

    bool getBDead();
    void setBDead(bool bSetDead);

    void playerDead(Player &player);    //상대방 폭파에 대한 충돌체크

    void dead();     //사망 애니메이션

    void eatBombPow();      //화력 아이템을 먹음
    void eatBombNum();      //폭탄 개수 증가 아이템을 먹음
    void eatSpeed();        //속도 증가 아이템을 먹음

    void playerClear();      //캐릭터를 다시 살리고 클리어
    void allClear();       //목숨 원래대로 클리어













};

