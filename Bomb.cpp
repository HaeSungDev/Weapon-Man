#include "StdAfx.h"
#include "Bomb.h"


Bomb::Bomb(void)
{
    /* ¸â¹ö ÃÊ±âÈ­ */

    iBombX = 0;
    iBombY = 0;

    iBombPow = 1;

    iBombAni = 4;
    iPopAni = 4;

    iTime = 0;

    iUse = 0;
}
Bomb::~Bomb(void)
{
}

int* Bomb::getICol()
{
    return iCol;
}

void Bomb::setIBombX(int iSetBombX)
{
    iBombX = iSetBombX;
}
int Bomb::getIBombX()
{
    return iBombX;
}

void Bomb::setIBombY(int iSetBombY)
{
    iBombY = iSetBombY;
}
int Bomb::getIBombY()
{
    return iBombY;
}

void Bomb::setIBombPow(int iSetBombPow)
{
    iBombPow = iSetBombPow;
}
int Bomb::getIBombPow()
{
    return iBombPow;
}

void Bomb::setIBombAni(int iSetBombAni)
{
    iBombAni = iSetBombAni;
}
int Bomb::getIBombAni()
{
    return iBombAni;
}

void Bomb::setIPopAni(int iSetPopAni)
{
    iPopAni = iSetPopAni;
}
int Bomb::getIPopAni()
{
    return iPopAni;
}

void Bomb::setITime(int iSetTime)
{
    iTime = iSetTime;
}
int Bomb::getITime()
{
    return iTime;
}

void Bomb::setIUse(int iSetUse)
{
    iUse = iSetUse;
}
int Bomb::getIUse()
{
    return iUse;
}

void Bomb::bombClear()
{
    iBombX = 0;
    iBombY = 0;

    iBombPow = 1;

    iBombAni = 4;
    iPopAni = 4;

    iTime = 0;

    iUse = 0;
}
