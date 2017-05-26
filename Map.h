#pragma once
class Map
{
    HBITMAP backBit;      //배경화면 비트맵 핸들
    HBITMAP mapBit;     //맵 비트맵 핸들

    int (*iMap)[XMAP];   //맵 배열

public:

    Map(void);
    ~Map(void);

    void saveMap(int (*ISetMap)[XMAP]);     //맵 저장
    void saveBitmap(HWND &hWnd);        //비트맵 저장

    void printBack(HDC &hdc);       //배경화면 출력
    void printMap(HDC &hdc);        //맵 출력
};