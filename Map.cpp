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
    backBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\BackGround.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);      //배경화면 비트맵 로드 후 저장
    mapBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\Block.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);      //맵 비트맵 로드 후 저장

    if( !backBit || !mapBit )
    {
        if(MessageBox(hWnd, L"외부에서 Load 되는 이미지 파일이 없습니다.", L"ERROR", MB_OK | MB_ICONERROR) == IDOK)
        {
            DestroyWindow(hWnd);        //로드 실패시 프로그램 종료
        }
    }
}

void Map::printBack(HDC &hdc)
{
    HDC memDC = CreateCompatibleDC(hdc);      //메모리 dc 선언 및 생성
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, backBit);    //메모리 해제를 위해 비트맵을 저장할 임시변수 선언 및 초기화

    BitBlt(hdc, 0, 0, WINSIZE, WINSIZE, memDC, 0, 0, SRCCOPY);      //배경출력

    SelectObject(memDC, oldBitmap);   //메모리dc의 비트맵을 원래대로 돌려놓음

    DeleteDC(memDC);    //메모리 dc 해제
}
void Map::printMap(HDC &hdc)
{
    HDC memDC = CreateCompatibleDC(hdc);    //hdc에 호환되는 메모리dc 생성
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, mapBit);      //메모리 해제를 위한 임시변수    
    
    for(int i = 0;i < YMAP;++i)
    {
        for(int j = 0;j < XMAP;++j)
        {
            switch(iMap[i][j])
            {
            case 1:

                BitBlt(hdc, j*MAPSIZE, i*MAPSIZE, MAPSIZE, MAPSIZE, memDC, 0*MAPSIZE, 0, SRCCOPY);      //부실 수 없는 벽돌출력

                break;

            case 2:

                BitBlt(hdc, j*MAPSIZE, i*MAPSIZE, MAPSIZE, MAPSIZE, memDC, 1*MAPSIZE, 0, SRCCOPY);      //부실 수 있는 벽돌출력

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

    SelectObject(memDC, oldBitmap);     //메모리dc의 비트맵을 원래대로 돌려줌
    DeleteDC(memDC);    //메모리dc 제거
}