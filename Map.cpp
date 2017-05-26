#include "StdAfx.h"
#include "Map.h"

Map::Map(void)
{
}
Map::~Map(void)
{
    DeleteObject(backBit);
    DeleteObject(mapBit);
}

void Map::saveMap(int (*ISetMap)[XMAP])
{
    iMap = ISetMap;
}
void Map::saveBitmap(HWND &hWnd)
{
    backBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\BackGround.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);      //���ȭ�� ��Ʈ�� �ε� �� ����
    mapBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\Block.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);      //�� ��Ʈ�� �ε� �� ����

    if( !backBit || !mapBit )
    {
        if(MessageBox(hWnd, L"�ܺο��� Load �Ǵ� �̹��� ������ �����ϴ�.", L"ERROR", MB_OK | MB_ICONERROR) == IDOK)
        {
            DestroyWindow(hWnd);        //�ε� ���н� ���α׷� ����
        }
    }
}

void Map::printBack(HDC &hdc)
{
    HDC memDC = CreateCompatibleDC(hdc);      //�޸� dc ���� �� ����
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, backBit);    //�޸� ������ ���� ��Ʈ���� ������ �ӽú��� ���� �� �ʱ�ȭ

    BitBlt(hdc, 0, 0, WINSIZE, WINSIZE, memDC, 0, 0, SRCCOPY);      //������

    SelectObject(memDC, oldBitmap);   //�޸�dc�� ��Ʈ���� ������� ��������

    DeleteDC(memDC);    //�޸� dc ����
}
void Map::printMap(HDC &hdc)
{
    HDC memDC = CreateCompatibleDC(hdc);    //hdc�� ȣȯ�Ǵ� �޸�dc ����
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, mapBit);      //�޸� ������ ���� �ӽú���    
    
    for(int i = 0;i < YMAP;++i)
    {
        for(int j = 0;j < XMAP;++j)
        {
            switch(iMap[i][j])
            {
            case 1:

                BitBlt(hdc, j*MAPSIZE, i*MAPSIZE, MAPSIZE, MAPSIZE, memDC, 0*MAPSIZE, 0, SRCCOPY);      //�ν� �� ���� �������

                break;

            case 2:

                BitBlt(hdc, j*MAPSIZE, i*MAPSIZE, MAPSIZE, MAPSIZE, memDC, 1*MAPSIZE, 0, SRCCOPY);      //�ν� �� �ִ� �������

                break;
                
            case 3:

                TransparentBlt(hdc, j*MAPSIZE, i*MAPSIZE, MAPSIZE, MAPSIZE, memDC, 2*MAPSIZE, 0, MAPSIZE, MAPSIZE, RGB(255,0,255));

                break;

            case 4:

                TransparentBlt(hdc, j*MAPSIZE, i*MAPSIZE, MAPSIZE, MAPSIZE, memDC, 3*MAPSIZE, 0, MAPSIZE, MAPSIZE, RGB(255,0,255));

                break;

            case 5:

                TransparentBlt(hdc, j*MAPSIZE, i*MAPSIZE, MAPSIZE, MAPSIZE, memDC, 4*MAPSIZE, 0, MAPSIZE, MAPSIZE, RGB(255,0,255));

                break;
            }
        }
    }

    SelectObject(memDC, oldBitmap);     //�޸�dc�� ��Ʈ���� ������� ������
    DeleteDC(memDC);    //�޸�dc ����
}