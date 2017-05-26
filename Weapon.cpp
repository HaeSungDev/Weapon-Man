#include "StdAfx.h"
#include "Weapon.h"


Weapon::Weapon(void)
{
    srand((unsigned)time(NULL));

    iBombNum = 1;
    iBombPow = 1;

    bombBit = NULL;
    popBit = NULL;
}
Weapon::~Weapon(void)
{
    DeleteObject(bombBit);
    DeleteObject(popBit);
}

void Weapon::increaseNum()
{
    iBombNum += 1;
}
int Weapon::getIBombNum()
{
    return iBombNum;
}

void Weapon::increasePow()
{
    iBombPow += 1;
}
int Weapon::getIBombPow()
{
    return iBombPow;
}

Bomb* Weapon::getBomb()
{
    return bomb;    
}

void Weapon::setMap(int (*iSetMap)[XMAP])
{
    iMap = iSetMap;
}
void Weapon::saveWeaponBitmap(HWND &hWnd)
{
    bombBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\Bomb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    popBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\Pop.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    
    if( !bombBit || !popBit )
    {
        if( MessageBox(hWnd, L"이미지를 불러 올 수 없습니다", L"ERROR!", MB_OK || MB_ICONSTOP) == IDOK)
        {
            DestroyWindow(hWnd);   //저장 실패시 윈도우 종료
        }
        else
        {
            DestroyWindow(hWnd);
        }
    }
}

void Weapon::bombPut(int iX, int iY)
{
    for(int i = 0;i < iBombNum;++i)
    {
        if( bomb[i].getIUse() == 0 )    //폭탄이 안놓여있을 때 폭탄을 놓음
        {
            if( iMap[iY][iX] != 1 && iMap[iY][iX] != 2 && iMap[iY][iX] != 10 )
            {
                iMap[iY][iX] = 10;

                bomb[i].setIBombPow(iBombPow);  //폭탄 파워 동기화

                bomb[i].setIBombX(iX);      //폭탄의 x위치
                bomb[i].setIBombY(iY);      //폭탄의 y위치

                bomb[i].setIUse(1);     //폭탄 놓음

                break;
            }
        }
    }
}

void Weapon::bombPrint(HDC &hdc)
{
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, bombBit);

    for(int i = 0;i < iBombNum;++i)
    {
        if( bomb[i].getIUse() == 1 )     //폭탄이 놓여있을때
        {
            TransparentBlt(hdc, bomb[i].getIBombX()*MAPSIZE, bomb[i].getIBombY()*MAPSIZE, MAPSIZE, MAPSIZE, memDC, bomb[i].getIBombAni()*MAPSIZE, 0, MAPSIZE, MAPSIZE, RGB(255,0,255));
        }
    }

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}
void Weapon::bombAni()
{
    for(int i = 0;i < iBombNum;++i)
    {
        if( bomb[i].getIUse() == 1)
        {
            /* 비트맵에서 좌표를 바꿔가면서 폭탄모양을 변경해줌 */
            switch(bomb[i].getIBombAni())
            {
            case 0:

                bomb[i].setIBombAni(1);

                break;

            case 1:
                
                bomb[i].setIBombAni(2);

                break;

            case 2:

                bomb[i].setIBombAni(3);

                break;

            case 3:

                bomb[i].setIBombAni(4);

                break;

            case 4:

                bomb[i].setIBombAni(0);

                break;
            }
        }
    }
}

void Weapon::popPrint(HDC &hdc)
{
    HDC memDC = CreateCompatibleDC(hdc); 
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, popBit);

    int tempX;      //각각의 폭탄의 x좌표를 넣어줄 변수
    int tempY;      //각각의 폭탄의 y좌표를 넣어줄 변수

    for(int i = 0;i < iBombNum;++i)
    {
        if( bomb[i].getIUse() == 2)
        {
            tempX = bomb[i].getIBombX();
            tempY = bomb[i].getIBombY();

            for(int j = 0;j <= bomb[i].getIBombPow();++j)
            {
                if( j <= bomb[i].getICol()[0] )
                {
                    TransparentBlt(hdc, tempX*MAPSIZE, (tempY-j)*MAPSIZE, MAPSIZE, MAPSIZE, memDC, bomb[i].getIPopAni()*MAPSIZE, 0, MAPSIZE, MAPSIZE, RGB(255,0,255));
                }
                if( j <= bomb[i].getICol()[1] )
                {
                    TransparentBlt(hdc, tempX*MAPSIZE, (tempY+j)*MAPSIZE, MAPSIZE, MAPSIZE, memDC, bomb[i].getIPopAni()*MAPSIZE, 0, MAPSIZE, MAPSIZE, RGB(255,0,255));
                }
                if( j <= bomb[i].getICol()[2] )
                {
                    TransparentBlt(hdc, (tempX-j)*MAPSIZE, tempY*MAPSIZE, MAPSIZE, MAPSIZE, memDC, bomb[i].getIPopAni()*MAPSIZE, 0, MAPSIZE, MAPSIZE, RGB(255,0,255));
                }
                if( j <= bomb[i].getICol()[3] )
                {
                    TransparentBlt(hdc, (tempX+j)*MAPSIZE, tempY*MAPSIZE, MAPSIZE, MAPSIZE, memDC, bomb[i].getIPopAni()*MAPSIZE, 0, MAPSIZE, MAPSIZE, RGB(255,0,255));
                }
            }
        }
    }

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}
void Weapon::popAni(Bomb *other_1, Bomb *other_2,  int iNum_1, int iNum_2)
{
    for(int i = 0;i < iBombNum;++i)
    {
        if( bomb[i].getIUse() == 2)
        {
            /* 비트맵에서 좌표를 바꿔가면서 폭탄모양을 변경해줌 */
            switch(bomb[i].getIPopAni())
            {
            case 0:

                bomb[i].setIPopAni(1);

                break;

            case 1:
                
                bomb[i].setIPopAni(2);

                break;

            case 2:

                blockClear(i);      //벽돌 제거
                bomb[i].setIPopAni(3);

                break;

            case 3:

                popEnd(i);      //폭파 끝
                bomb[i].setIPopAni(4);

                break;

            case 4:
               
                bombCol(bomb, iBombNum, i);     //폭탄이 있는지 충돌체크
                bombCol(other_1, iNum_1, i);     //폭탄이 있는지 충돌체크
                bombCol(other_2, iNum_2, i);    //폭탄이 있는지 충돌체크
                bomb[i].setIPopAni(0);

                break;
            }
        }
    }
}

void Weapon::blockClear(int iPlace)
{
    int tempX = bomb[iPlace].getIBombX();
    int tempY = bomb[iPlace].getIBombY();

    /* 위쪽 블록이 깰수 있는 블럭일때 제거 */
    if( iMap[tempY-bomb[iPlace].getICol()[0]][tempX] == 2 )
    {
        iMap[tempY-bomb[iPlace].getICol()[0]][tempX] = randomItem();
    }
    
    /* 아래쪽 블록이 깰수 있는 블럭일때 제거 */
    if( iMap[tempY+bomb[iPlace].getICol()[1]][tempX] == 2 )
    {
        iMap[tempY+bomb[iPlace].getICol()[1]][tempX] = randomItem();
    }

    /* 왼쪽 블록이 깰수 있는 블럭일때 제거 */
    if( iMap[tempY][tempX-bomb[iPlace].getICol()[2]] == 2 )
    {
        iMap[tempY][tempX-bomb[iPlace].getICol()[2]] = randomItem();
    }

    /* 오른쪽 블록이 깰수 있는 블럭일때 제거 */
    if( iMap[tempY][tempX+bomb[iPlace].getICol()[3]] == 2 )
    {
        iMap[tempY][tempX+bomb[iPlace].getICol()[3]] = randomItem();
    }
}
void Weapon::popEnd(int iPlace)
{
    int tempX = bomb[iPlace].getIBombX();
    int tempY = bomb[iPlace].getIBombY();

    iMap[tempY][tempX] = 0;

    bomb[iPlace].setIUse(0);
    bomb[iPlace].setITime(0);
}

void Weapon::bombTimer()
{
    for(int i = 0;i < iBombNum; ++i)
    {
        if( bomb[i].getIUse() == 1 )        //폭탄이 놓여있을떄
        {
            bomb[i].setITime(bomb[i].getITime()+BOMBTIME);     //폭탄시간 증가 

            if(bomb[i].getITime() >= BOMBTIME*10)       //폭탄 시간이 됬을시
            {
                bombBlockCol(bomb, i);
                bomb[i].setIUse(2);     //폭탄 터짐
            }
        }
    }
}

void Weapon::bombBlockCol(Bomb *bomb, int iPlace)
{
    int tempX = bomb[iPlace].getIBombX();
    int tempY = bomb[iPlace].getIBombY();

    /* 충돌체크 안했을때 */
    for(int i = 0;i < 4;++i)
    {
        bomb[iPlace].getICol()[i] = bomb[iPlace].getIBombPow();
    }

    /* 위쪽 방향 벽돌 및 폭탄 충돌체크 */
    for(int i = 1;i <= bomb[iPlace].getIBombPow();++i)
    {   
        if( iMap[tempY-i][tempX] == 1 )
        {
            bomb[iPlace].getICol()[0] = i-1;
            break;
        }
        else if( iMap[tempY-i][tempX] == 2  || iMap[tempY-i][tempX] == 9 || iMap[tempY-i][tempX] == 10)
        {
            bomb[iPlace].getICol()[0] = i;
            break;
        }
        else if( (iMap[tempY-i][tempX] == 3) || (iMap[tempY-i][tempX] == 4) || (iMap[tempY-i][tempX] == 5) )    //아이템 제거
        {
            iMap[tempY-i][tempX] = 0;
        }
    }

    /* 아래쪽 방향 벽돌 및 폭탄 충돌체크 */
    for(int i = 1;i <= bomb[iPlace].getIBombPow();++i)
    {
        if( iMap[tempY+i][tempX] == 1 )
        {
            bomb[iPlace].getICol()[1] = i-1;
            break;
        }
        else if( iMap[tempY+i][tempX] == 2 || iMap[tempY+i][tempX] == 9 || iMap[tempY+i][tempX] == 10 )
        {
            bomb[iPlace].getICol()[1] = i;
            break;
        }
        else if( (iMap[tempY+i][tempX] = 3) || (iMap[tempY+i][tempX] == 4) || (iMap[tempY+i][tempX] == 5) )      //아이템제거
        {
            iMap[tempY+i][tempX] = 0;
        }
    }

    /* 왼쪽 방향 벽돌 및 폭탄 충돌체크 */
    for(int i = 1;i <= bomb[iPlace].getIBombPow();++i)
    {
        if( iMap[tempY][tempX-i] == 1 )
        {
            bomb[iPlace].getICol()[2] = i-1;
            break;
        }
        else if( iMap[tempY][tempX-i] == 2 || iMap[tempY][tempX-i] == 9 || iMap[tempY][tempX-i] == 10 )
        {
            bomb[iPlace].getICol()[2] = i;
            break;
        }

        if( (iMap[tempY][tempX-i] == 3) || (iMap[tempY][tempX-i] == 4) || (iMap[tempY][tempX-i] == 5) )     //아이템 제거
        {
            iMap[tempY][tempX-i] = 0;
        }
    }

    /* 오른쪽 방향 벽돌 및 폭탄 충돌체크 */
    for(int i = 1;i <= bomb[iPlace].getIBombPow();++i)
    {
        if( iMap[tempY][tempX+i] == 1 )
        {
            bomb[iPlace].getICol()[3] = i-1;
            break;
        }
        else if( iMap[tempY][tempX+i] == 2 || iMap[tempY][tempX+i] == 9 || iMap[tempY][tempX+i] == 10 )
        {
            bomb[iPlace].getICol()[3] = i;
            break;
        }
        else if( (iMap[tempY][tempX+i] == 3) || (iMap[tempY][tempX+i] == 4) || (iMap[tempY][tempX+i] == 5) )     //아이템제거
        {
            iMap[tempY][tempX+i] = 0;
        }
    }
}

void Weapon::bombCol(Bomb *other, int iNum, int iPlace)
{
    int iX = bomb[iPlace].getIBombX();
    int iY = bomb[iPlace].getIBombY();

    int tempX;
    int tempY;

    bombBlockCol(bomb, iPlace);

    /* 폭파가 폭탄에 닿았을떄 폭탄이 터짐 */
    for(int i = 0;i < iNum;++i)
    {
        if( other[i].getIUse() == 1 )
        {
            tempX = other[i].getIBombX();
            tempY = other[i].getIBombY();

            /* 폭탄이 폭파에 닿았는지 체크 */
            for(int j = 1;j <= bomb[iPlace].getIBombPow();++j)
            {
                if( j <= bomb[iPlace].getICol()[0] )
                {
                    if( (iY-j == tempY) && (iX == tempX) )
                    {
                        other[i].setIUse(2);
                        bombBlockCol(other, i);
                        
                        break;
                    }
                }
                
                if( j <= bomb[iPlace].getICol()[1] )
                {
                    if( (iY+j == tempY) && (iX == tempX) )
                    {
                        other[i].setIUse(2);
                        bombBlockCol(other, i);

                        break;
                    }
                }
                
                if( j <= bomb[iPlace].getICol()[2] )
                {
                    if( (iX-j == tempX) && (iY == tempY) ) 
                    {
                        other[i].setIUse(2);
                        bombBlockCol(other, i);

                        break;
                    }
                }
                
                if( j <= bomb[iPlace].getICol()[3] )
                {
                    if( (iX+j == tempX) && (iY == tempY) ) 
                    {
                        other[i].setIUse(2);
                        bombBlockCol(other, i);

                        break;
                    }
                }
            }
        }
    }
}

int Weapon::randomItem()
{
    int item = ((rand()%100+1)*(rand()%100+1))%100+1;

    if( item <= 70 )
    {
        return 0;
    }
    else if( item <= 80 )
    {
        return 3;
    }
    else if( item <= 90 )
    {
        return 4;
    }
    else
    {
        return 5;
    }
}

void Weapon::weaponClear()
{
    iBombNum = 1;
    iBombPow = 1;
}