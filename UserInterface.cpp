#include "StdAfx.h"
#include "UserInterface.h"

UserInterface::UserInterface(void)
{
    ZeroMemory(bMenu, sizeof(bMenu));
   
    menu[0].bottom = 489;
    menu[0].left = 280;
    menu[0].right = 424;
    menu[0].top = 450;

    menu[1].bottom = 528;
    menu[1].left = 280;
    menu[1].right = 424;
    menu[1].top = 489;

    menu[2].bottom = 567;
    menu[2].left = 280;
    menu[2].right = 424;
    menu[2].top = 528;
}
UserInterface::~UserInterface(void)
{
    DeleteObject(uiBit);
    DeleteObject(menuBit);
}

void UserInterface::saveBitmap(HWND &hWnd)
{
    uiBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\UI.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    menuBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\menu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if( !uiBit || !menuBit )
    {
        if( MessageBox(hWnd, L"이미지를 불러 올 수 없습니다.", L"ERROR!", MB_OK || MB_ICONSTOP) == IDOK )
        {
            DestroyWindow(hWnd);
        }
        else
        {
            DestroyWindow(hWnd);
        }
    }
}

void UserInterface::interfacePrint(HDC &hdc)
{
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, uiBit);
    
    BitBlt(hdc, 0, 0, WINSIZE+30, WINSIZE, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, menuBit);

    if( bMenu[0] )
    {
        TransparentBlt(hdc, menu[0].left-30, menu[0].top-10, WIMENU+60, HEMENU+20, memDC, 0, 0*HEMENU, WIMENU, HEMENU, RGB(255,0,255));
    }
    else
    {
        TransparentBlt(hdc, menu[0].left, menu[0].top, WIMENU, HEMENU, memDC, 0, 0*HEMENU, WIMENU, HEMENU, RGB(255,0,255));
    }
    if( bMenu[1] )
    {
        TransparentBlt(hdc, menu[1].left-30, menu[1].top-10, WIMENU+60, HEMENU+20, memDC, 0, 1*HEMENU, WIMENU, HEMENU, RGB(255,0,255));
    }
    else
    {
        TransparentBlt(hdc, menu[1].left, menu[1].top, WIMENU, HEMENU, memDC, 0, 1*HEMENU, WIMENU, HEMENU, RGB(255,0,255));
    }
    if( bMenu[2] )
    {
        TransparentBlt(hdc, menu[2].left-30,menu[2].top-10, WIMENU+60, HEMENU+20, memDC, 0, 2*HEMENU, WIMENU, HEMENU, RGB(255,0,255));
    }
    else
    {
        TransparentBlt(hdc, menu[2].left, menu[2].top, WIMENU, HEMENU, memDC, 0, 2*HEMENU, WIMENU, HEMENU, RGB(255,0,255));
    }

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}

void UserInterface::checkMouse(int iX, int iY)
{
    if( (iX >= menu[0].left && iX <= menu[0].right) &&
        (iY >= menu[0].top && iY <= menu[0].bottom) )
    {
        bMenu[0] = true;
    }
    else
    {
        bMenu[0] = false;
    }
    
    if( (iX >= menu[1].left && iX <= menu[1].right) &&
             (iY >= menu[1].top && iY <= menu[1].bottom) )
    {
        bMenu[1] = true;
    }
    else
    {
        bMenu[1] = false;
    }
    
    if( (iX >= menu[2].left && iX <= menu[2].right) &&
             (iY >= menu[2].top && iY <= menu[2].bottom) )
    {
        bMenu[2] = true;
    }
    else
    {
        bMenu[2] = false;
    }
}
int UserInterface::checkClick(HWND &hWnd)
{
    if( bMenu[0] )
    {
        return 1;
    }
    else if( bMenu[1] )
    {
        return 2;
    }
    else if( bMenu[2] )
    {
        return 0;
    }
}