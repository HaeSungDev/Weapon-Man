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

void Weapon::bombPut(int iX, int iY)
{
    for(int i = 0;i < iBombNum;++i)
    {
        if( bomb[i].getIUse() == 0 )    //��ź�� �ȳ������� �� ��ź�� ����
        {
            if( iMap[iY][iX] != 1 && iMap[iY][iX] != 2 && iMap[iY][iX] != 10 )
            {
                iMap[iY][iX] = 10;

                bomb[i].setIBombPow(iBombPow);  //��ź �Ŀ� ����ȭ

                bomb[i].setIBombX(iX);      //��ź�� x��ġ
                bomb[i].setIBombY(iY);      //��ź�� y��ġ

                bomb[i].setIUse(1);     //��ź ����

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
        if( bomb[i].getIUse() == 1 )     //��ź�� ����������
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
            /* ��Ʈ�ʿ��� ��ǥ�� �ٲ㰡�鼭 ��ź����� �������� */
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

    int tempX;      //������ ��ź�� x��ǥ�� �־��� ����
    int tempY;      //������ ��ź�� y��ǥ�� �־��� ����

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
            /* ��Ʈ�ʿ��� ��ǥ�� �ٲ㰡�鼭 ��ź����� �������� */
            switch(bomb[i].getIPopAni())
            {
            case 0:

                bomb[i].setIPopAni(1);

                break;

            case 1:
                
                bomb[i].setIPopAni(2);

                break;

            case 2:

                blockClear(i);      //���� ����
                bomb[i].setIPopAni(3);

                break;

            case 3:

                popEnd(i);      //���� ��
                bomb[i].setIPopAni(4);

                break;

            case 4:
               
                bombCol(bomb, iBombNum, i);     //��ź�� �ִ��� �浹üũ
                bombCol(other_1, iNum_1, i);     //��ź�� �ִ��� �浹üũ
                bombCol(other_2, iNum_2, i);    //��ź�� �ִ��� �浹üũ
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

    /* ���� ����� ���� �ִ� ���϶� ���� */
    if( iMap[tempY-bomb[iPlace].getICol()[0]][tempX] == 2 )
    {
        iMap[tempY-bomb[iPlace].getICol()[0]][tempX] = randomItem();
    }
    
    /* �Ʒ��� ����� ���� �ִ� ���϶� ���� */
    if( iMap[tempY+bomb[iPlace].getICol()[1]][tempX] == 2 )
    {
        iMap[tempY+bomb[iPlace].getICol()[1]][tempX] = randomItem();
    }

    /* ���� ����� ���� �ִ� ���϶� ���� */
    if( iMap[tempY][tempX-bomb[iPlace].getICol()[2]] == 2 )
    {
        iMap[tempY][tempX-bomb[iPlace].getICol()[2]] = randomItem();
    }

    /* ������ ����� ���� �ִ� ���϶� ���� */
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
        if( bomb[i].getIUse() == 1 )        //��ź�� ����������
        {
            bomb[i].setITime(bomb[i].getITime()+BOMBTIME);     //��ź�ð� ���� 

            if(bomb[i].getITime() >= BOMBTIME*10)       //��ź �ð��� ������
            {
                bombBlockCol(bomb, i);
                bomb[i].setIUse(2);     //��ź ����
            }
        }
    }
}

void Weapon::bombBlockCol(Bomb *bomb, int iPlace)
{
    int tempX = bomb[iPlace].getIBombX();
    int tempY = bomb[iPlace].getIBombY();

    /* �浹üũ �������� */
    for(int i = 0;i < 4;++i)
    {
        bomb[iPlace].getICol()[i] = bomb[iPlace].getIBombPow();
    }

    /* ���� ���� ���� �� ��ź �浹üũ */
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
        else if( (iMap[tempY-i][tempX] == 3) || (iMap[tempY-i][tempX] == 4) || (iMap[tempY-i][tempX] == 5) )    //������ ����
        {
            iMap[tempY-i][tempX] = 0;
        }
    }

    /* �Ʒ��� ���� ���� �� ��ź �浹üũ */
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
        else if( (iMap[tempY+i][tempX] = 3) || (iMap[tempY+i][tempX] == 4) || (iMap[tempY+i][tempX] == 5) )      //����������
        {
            iMap[tempY+i][tempX] = 0;
        }
    }

    /* ���� ���� ���� �� ��ź �浹üũ */
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

        if( (iMap[tempY][tempX-i] == 3) || (iMap[tempY][tempX-i] == 4) || (iMap[tempY][tempX-i] == 5) )     //������ ����
        {
            iMap[tempY][tempX-i] = 0;
        }
    }

    /* ������ ���� ���� �� ��ź �浹üũ */
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
        else if( (iMap[tempY][tempX+i] == 3) || (iMap[tempY][tempX+i] == 4) || (iMap[tempY][tempX+i] == 5) )     //����������
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

    /* ���İ� ��ź�� ������� ��ź�� ���� */
    for(int i = 0;i < iNum;++i)
    {
        if( other[i].getIUse() == 1 )
        {
            tempX = other[i].getIBombX();
            tempY = other[i].getIBombY();

            /* ��ź�� ���Ŀ� ��Ҵ��� üũ */
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