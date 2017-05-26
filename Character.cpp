#include "StdAfx.h"
#include "Character.h"


Character::Character()
{
    charBit = NULL;

    iBitX = 1;
    iBitY = 0;

    iCharAni = 0;

    iSpeed = 2;
}
Character::~Character(void)
{
    DeleteObject(charBit);      //��Ʈ�� �޸� ����
}

void Character::setIPlayer(int iSetPlayer)
{
    iPlayer = iSetPlayer;

    if( iPlayer == 1 )
    {
        iCharX = 1*50;
        iCharY = 1*50;
    }
    else if( iPlayer == 2)
    {
        iCharX = 12*50-WICHAR;
        iCharY = 12*50-HECHAR;
    }
}

int Character::getICharX()
{
    return iCharX;
}
int Character::getICharY()
{
    return iCharY;
}

void Character::increaseSpeed()
{
    iSpeed += 1;
}
int Character::getISpeed()
{
    return iSpeed;
}

int Character::getIBitX()
{
    return iBitX;
}

void Character::setIBitX(int iSetBitX)
{
    iBitX = iSetBitX;
}
void Character::setIBitY(int iSetBitY)
{
    iBitY = iSetBitY;
}

void Character::saveBitmap(HWND &hWnd)
{
    if( iPlayer == 1)
    {
        charBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\Character1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);  //�ܺο��� ��Ʈ���� �ҷ��ͼ� charBit�� ����
    }
    else if( iPlayer == 2)
    {
        charBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\Character2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);  //�ܺο��� ��Ʈ���� �ҷ��ͼ� charBit�� ����
    }
    if( !charBit )
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

void Character::charPrint(HDC &hdc)
{
    HDC memDC = CreateCompatibleDC(hdc);      //�޸� dc ���� �� ����
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, charBit);    //�޸� ������ ���� ��Ʈ���� ������ �ӽú��� ���� �� �ʱ�ȭ

    TransparentBlt(hdc, iCharX, iCharY, WICHAR, HECHAR, memDC, iBitX*WICHAR, iBitY*HECHAR, WICHAR, HECHAR, RGB(255,0,255));       //ĳ������ RGB(255,0,255) ����  �����Ʈ��ȭ ���

    SelectObject(memDC, oldBitmap);   //�޸�dc�� ��Ʈ���� ������� ��������
    DeleteDC(memDC);    //�޸� dc ����
}
void Character::charMove(WPARAM wParam)
{
    /* ��Ʈ�� ��ǥ�� �ٲ� �ִϸ��̼�ó�� ���̰� �� */
    if( iCharAni < 10 )
    {
        iBitX = 0;
        ++iCharAni;
    }
    else if( iCharAni < 20 )
    {
        iBitX = 2;
        ++iCharAni;
    }
    else
    {
        iBitX = 0;
        iCharAni = 0;
    }

    switch(wParam)
    {
    case VK_UP:
        
        iBitY = 1;
        iCharY -= iSpeed;   //���� �̵�

        break;

    case VK_DOWN:

        iBitY = 0;
        iCharY += iSpeed;   //�Ʒ��� �̵�

        break;

    case VK_LEFT:

        iBitY = 2;
        iCharX -= iSpeed;   //�������� �̵�

        break;

    case VK_RIGHT:

        iBitY = 3;
        iCharX += iSpeed;   //���������� �̵�

        break;
    }
}

bool Character::charCol(int iDirection, int iMapX, int iMapY, int iWidth, int iHeight)
{
    if( rectCol(iCharX, iCharY, WICHAR, HECHAR, iMapX, iMapY, iWidth, iHeight) )       //�浹������ üũ
    {
        int tempX = (iCharX+WICHAR/2);
        int tempY = (iCharY+HECHAR/2);

        /* �̵����⿡ ���� ó�� */
        switch(iDirection)
        {
        case VK_UP:

            iCharY = iMapY+iHeight;

            break;

        case VK_DOWN:

            iCharY = iMapY-HECHAR;

            break;

        case VK_LEFT:

            iCharX = iMapX+iWidth;

            break;

        case VK_RIGHT:

            iCharX = iMapX-WICHAR;
            
            break;
        }

        return true;
    }
    else
    {
        return false;
    }
}
bool Character::rectCol(int iX_1, int iY_1, int iWidth_1, int iHeight_1, int iX_2, int iY_2, int iWidth_2, int iHeight_2)
{
    /* �簢���� ���ƴ��� üũ */
    if( (((iX_1 > iX_2) && (iX_1 < iX_2+iWidth_2)) || ((iX_1+iWidth_1 > iX_2) && (iX_1+iWidth_1 < iX_2+iWidth_2)) || ((iX_1 <= iX_2) && (iX_1+iWidth_1 >= iX_2+iWidth_2))) &&
        (((iY_1 > iY_2) && (iY_1 < iY_2+iHeight_2)) || ((iY_1+iHeight_1 > iY_2) && (iY_1+iHeight_1 < iY_2+iHeight_2)) || ((iY_1 <= iY_2) && (iY_1+iHeight_1 >= iY_2+iHeight_2))) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Character::charClear()
{
    iBitX = 1;
    iBitY = 0;

    iCharAni = 0;

    if( iPlayer == 1 )
    {
        iCharX = 1*50;
        iCharY = 1*50;
    }
    else if( iPlayer == 2)
    {
        iCharX = 12*50-WICHAR;
        iCharY = 12*50-HECHAR;
    }
}

void Character::speedClear()      //�ӵ� �ʱ�ȭ
{
    iSpeed = 2;
}