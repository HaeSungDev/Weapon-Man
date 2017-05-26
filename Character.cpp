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
    DeleteObject(charBit);      //비트맵 메모리 해제
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
        charBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\Character1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);  //외부에서 비트맵을 불러와서 charBit에 저장
    }
    else if( iPlayer == 2)
    {
        charBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\Character2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);  //외부에서 비트맵을 불러와서 charBit에 저장
    }
    if( !charBit )
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

void Character::charPrint(HDC &hdc)
{
    HDC memDC = CreateCompatibleDC(hdc);      //메모리 dc 선언 및 생성
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, charBit);    //메모리 해제를 위해 비트맵을 저장할 임시변수 선언 및 초기화

    TransparentBlt(hdc, iCharX, iCharY, WICHAR, HECHAR, memDC, iBitX*WICHAR, iBitY*HECHAR, WICHAR, HECHAR, RGB(255,0,255));       //캐릭터의 RGB(255,0,255) 색을  투명비트맵화 출력

    SelectObject(memDC, oldBitmap);   //메모리dc의 비트맵을 원래대로 돌려놓음
    DeleteDC(memDC);    //메모리 dc 해제
}
void Character::charMove(WPARAM wParam)
{
    /* 비트맵 좌표를 바꿔 애니메이션처럼 보이게 함 */
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
        iCharY -= iSpeed;   //위로 이동

        break;

    case VK_DOWN:

        iBitY = 0;
        iCharY += iSpeed;   //아래로 이동

        break;

    case VK_LEFT:

        iBitY = 2;
        iCharX -= iSpeed;   //왼쪽으로 이동

        break;

    case VK_RIGHT:

        iBitY = 3;
        iCharX += iSpeed;   //오른쪽으로 이동

        break;
    }
}

bool Character::charCol(int iDirection, int iMapX, int iMapY, int iWidth, int iHeight)
{
    if( rectCol(iCharX, iCharY, WICHAR, HECHAR, iMapX, iMapY, iWidth, iHeight) )       //충돌했을때 체크
    {
        int tempX = (iCharX+WICHAR/2);
        int tempY = (iCharY+HECHAR/2);

        /* 이동방향에 따른 처리 */
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
    /* 사각형이 겹쳤는지 체크 */
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

void Character::speedClear()      //속도 초기화
{
    iSpeed = 2;
}