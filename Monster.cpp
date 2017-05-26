#include "StdAfx.h"
#include "Monster.h"


Monster::Monster(void)
{
    /* ���ʹ� �� �߾ӿ� ��ġ*/ 
    iMonX = 290;
    iMonY = 280;

    iMonBitX = 0;

    iHP = 650;

    bDead = false;
    bMessage = false;

    redBrush = CreateSolidBrush(RGB(255,0,0));
}
Monster::~Monster(void)
{
    DeleteObject(redBrush);
    DeleteObject(monBit);
}

int Monster::getIHP()
{
    return iHP;
}

int Monster::getIMonX()
{
    return iMonX;
}
int Monster::getIMonY()
{
    return iMonY;
}

bool Monster::getBDead()
{
    return bDead;
}

void Monster::saveBitmap(HWND &hWnd)
{
    monBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\Monster.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    if( !monBit )
    {
        if( MessageBox(hWnd, L"�̹����� �ҷ� �� �� �����ϴ�", L"ERROR!", MB_OK || MB_ICONSTOP) == IDOK)
        {
            DestroyWindow(hWnd);   //���� ���н� ������ ����
        }
        else
        {
            DestroyWindow(hWnd);
        }
    }
}

void Monster::monsterPrint(HDC &hdc)
{
    if( !bDead )
    {
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, monBit);

        TransparentBlt(hdc, iMonX, iMonY, WMON, HMON, memDC, iMonBitX*WMON, 0, WMON, HMON, RGB(255,0,255));

        if( (iMonBitX == 1) && (timeGetTime()-iAniTime >= 200) )
        {
            iMonBitX = 0;
        }

        SelectObject(memDC, oldBitmap);
        DeleteDC(memDC);
    }
    else if( bMessage )
    {
        HFONT myFont = CreateFont(35,0,0,0,FW_BOLD,0,0,0,HANGEUL_CHARSET,0,0,0,0,L"�ü�");
        HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
        
        SetBkMode(hdc, TRANSPARENT);

        TextOut(hdc, 25, 300, L"���� �ο��� �̰� ��ŷ�� ����ϼ���", lstrlen(L"���� �ο��� �̰� ��ŷ�� ����ϼ���")); 

        SelectObject(hdc, oldFont);
        DeleteObject(myFont);

        if( timeGetTime()-iMsgTime >= 3000 )
        {
            bMessage = false;
        }
    }
}
void Monster::energyPrint(HDC &hdc)
{
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, redBrush);

    Rectangle(hdc, WINSIZE, WINSIZE-(iHP), WINSIZE+30, WINSIZE);

    SelectObject(hdc,oldBrush);
}
void Monster::monHitAni()
{
    if( iMonBitX == 1 )
    {
        iMonBitX = 0;
    }
}

void Monster::decreaseHP(int (*iMap)[XMAP], Player &player)
{
    if( !bDead )
    {
        Bomb *bomb = player.getBomb();

        int iX = (iMonX+WICHAR/2)/MAPSIZE;
        int iY = (iMonY+HECHAR/2)/MAPSIZE;

        int tempX;
        int tempY;

        for(int i = 0;i < player.getIBombNum();++i)
        {
            if( bomb[i].getIUse() == 2 && bomb[i].getIPopAni() == 3 )
            {
                tempX = bomb[i].getIBombX();
                tempY = bomb[i].getIBombY();

                /* ���Ͱ� ���Ŀ� �¾Ҵ��� �浹üũ */
                for(int j = 0;j <= bomb[i].getIBombPow();++j)
                {
                    /* ���Ͱ� ���Ŀ� �¾Ҵ��� �浹üũ */
                    for(int j = 0;j <= bomb[i].getIBombPow();++j)
                    {
                        if( j <= bomb[i].getICol()[0] )
                        {
                            if( (iY == tempY-j) && (iX == tempX) )
                            {
                                iHP -= 10;

                                iMonBitX = 1;
                                iAniTime = timeGetTime();

                                if( iHP <= 300 )
                                {
                                    increasePow();
                                }
                                if( iHP <= 0 )
                                {
                                    bMessage = true;
                                    iMsgTime = timeGetTime();

                                    bDead = true;

                                    iMap[iY][iX] = 0;
                                }
                                break;
                            }
                        }
                        
                        if( j <= bomb[i].getICol()[1] )
                        {
                            if( (iY == tempY+j) && (iX == tempX) )
                            {
                                iHP -= 10;

                                iMonBitX = 1;
                                iAniTime = timeGetTime();
                                
                                if( iHP <= 300 )
                                {
                                    increasePow();
                                }
                                if( iHP <= 0 )
                                {
                                    bMessage = true;
                                    iMsgTime = timeGetTime();

                                    bDead = true;

                                    iMap[iY][iX] = 0;
                                }
                                break;
                            }
                        }
                        
                        if( j <= bomb[i].getICol()[2] )
                        {
                            if( (iX == tempX-j) && (iY == tempY) ) 
                            {
                                iHP -= 10;

                                iMonBitX = 1;
                                iAniTime = timeGetTime();

                                if( iHP <= 300 )
                                {
                                    increasePow();
                                }
                                if( iHP <= 0 )
                                {
                                    bMessage = true;
                                    iMsgTime = timeGetTime();

                                    bDead = true;

                                    iMap[iY][iX] = 0;
                                }
                                break;
                            }
                        }
                        
                        if( j <= bomb[i].getICol()[3] )
                        {
                            if( (iX == tempX+j) && (iY == tempY) ) 
                            {
                                iHP -= 10;

                                iMonBitX = 1;
                                iAniTime = timeGetTime();

                                if( iHP <= 300 )
                                {
                                    increasePow();
                                }
                                if( iHP <= 0 )
                                {
                                    bMessage = true;
                                    iMsgTime = timeGetTime();

                                    bDead = true;

                                    iMap[iY][iX] = 0;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Monster::attack()
{
    if( !bDead )
    {
        if( iHP > 300 )
        {
            bombPut(XMON+1, YMON+1);
            bombPut(XMON-1, YMON-1);
            bombPut(XMON+1, YMON-1);
            bombPut(XMON-1, YMON+1);
            bombPut(XMON-1, YMON);
            bombPut(XMON+1, YMON);
        }
        else if( iHP > 150 )
        {
            bombPut(XMON+2, YMON+1);
            bombPut(XMON-2, YMON-1);
            bombPut(XMON+2, YMON-1);
            bombPut(XMON-2, YMON+1);
            bombPut(XMON-1, YMON);
            bombPut(XMON+1, YMON);
        }
        else if( iHP > 0 )
        {
            bombPut(XMON+3, YMON+1);
            bombPut(XMON-3, YMON-1);
            bombPut(XMON+3, YMON-1);
            bombPut(XMON-3, YMON+1);
            bombPut(XMON-1, YMON);
            bombPut(XMON+1, YMON);
        }
    }
}

void Monster::monsterClear(int (*iMap)[XMAP])
{
    int iX = (iMonX+WICHAR/2)/MAPSIZE;
    int iY = (iMonY+HECHAR/2)/MAPSIZE;

    iMap[iY][iX] = 9;

    iMonX = 290;
    iMonY = 280;

    iHP = 650;

    bDead = false;
}