#include "StdAfx.h"
#include "Player.h"

Player::Player()
{
    iLife = MAXLIFE;

    bDead = false;
}
Player::~Player(void)
{
}

int Player::getITime()
{
    return iTime;
}
void Player::setITime(int iSetTime)
{
    iTime = iSetTime;
}

int Player::getILife()
{
    return iLife;
}
void Player::setILife(int iSetLife)
{
    iLife = iSetLife;
}

bool Player::getBDead()
{
    return bDead;
}
void Player::setBDead(bool bSetDead)
{
    bDead = bSetDead;
}

void Player::playerDead(Player &player)
{
    if( !bDead )
    {
        Bomb* bomb = player.getBomb();

        int iX = (getICharX()+WICHAR/2)/MAPSIZE;
        int iY = (getICharY()+HECHAR/2)/MAPSIZE;

        int tempX;
        int tempY;

        for(int i = 0;i < player.getIBombNum();++i)
        {
            if( bomb[i].getIUse() == 2 && bomb[i].getIPopAni() < 3 )
            {
                tempX = bomb[i].getIBombX();
                tempY = bomb[i].getIBombY();

                /* 캐릭터가 폭파에 맞았는지 충돌체크 */
                for(int j = 0;j <= bomb[i].getIBombPow();++j)
                {
                    /* 캐릭터가 폭파에 맞았는지 충돌체크 */
                    for(int j = 0;j <= bomb[i].getIBombPow();++j)
                    {
                        if( j <= bomb[i].getICol()[0] )
                        {
                            if( (iY == tempY-j) && (iX == tempX) )
                            {
                                bDead = true;

                                iTime = timeGetTime();

                                break;
                            }
                        }
                        
                        if( j <= bomb[i].getICol()[1] )
                        {
                            if( (iY == tempY+j) && (iX == tempX) )
                            {
                                bDead = true;

                                iTime = timeGetTime();

                                break;
                            }
                        }
                        
                        if( j <= bomb[i].getICol()[2] )
                        {
                            if( (iX == tempX-j) && (iY == tempY) ) 
                            {
                                bDead = true;

                                iTime = timeGetTime();

                                break;
                            }
                        }
                        
                        if( j <= bomb[i].getICol()[3] )
                        {
                            if( (iX == tempX+j) && (iY == tempY) ) 
                            {
                                bDead = true;

                                iTime = timeGetTime();

                                break;
                            }
                        }
                    }
                }
            }
        }
    }   
}

void Player::dead()
{
    setIBitY(4);
    setIBitX(0);
}

void Player::eatBombPow()
{
    Bomb *bomb = getBomb();
    
    if( getIBombPow()+1 <= MAXPOW )
    {
        increasePow();
    }
}
void Player::eatBombNum()
{
    if( getIBombNum()+1 < MAXBOMB )
    {
        increaseNum();
    }
}
void Player::eatSpeed()
{
    if( getISpeed()+2 < MAXSPEED )
    {
        increaseSpeed();
    }
}

void Player::playerClear()
{
    bDead = false;

    charClear();
}
void Player::allClear()
{
    iLife = MAXLIFE;

    playerClear();
    speedClear();
    weaponClear();
}