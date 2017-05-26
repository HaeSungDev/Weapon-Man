#include "StdAfx.h"
#include "Ranking.h"

Ranking::Ranking(void)
{
    bRank = false;
}
Ranking::~Ranking(void)
{
}

void Ranking::setBRank(bool bSetRank)
{
    bRank = bSetRank;
}
bool Ranking::getBRank()
{
    return bRank;
}

void Ranking::rankRead(HWND &hWnd)
{
    for(int i = 0;i < 6;++i)
    {
        iRank[i] = 999999;
        lstrcpy(str[i],L" ");
        strcpy(str_a[i]," ");
    }

    FILE *fp;

    fopen_s(&fp, ".\\Ranking\\Ranking.lhs", "rt");
    if(fp == NULL)
    {
        if(MessageBox(hWnd, L"외부에서 Load 되는 랭킹 파일이 없습니다.", L"ERROR", MB_OK | MB_ICONERROR) == IDOK)
        {
            DestroyWindow(hWnd);        //로드 실패시 프로그램 종료
        }
    }

    int i = 0;
    while( !feof(fp) )
    {
        fscanf_s(fp, "%d", &iRank[i]);
        fgets(str_a[i], 200, fp);

        swap();

        if( i < 5)
        {
            ++i;
        }
    }

    fclose(fp);
    
    for(int i = 0;i < 5;++i)
    {
        char *p;

        strcpy(str_a[i], strtok(str_a[i], "|"));
        
        MultiByteToWideChar(CP_ACP,0,str_a[i],200,str[i],200);
    }
}

void Ranking::swap()
{
    for(int i = 0;i < 6;++i)
    {
        for(int j = i+1;j < 6;++j)
        {
            if( iRank[i] > iRank[j] )
            {
                int temp = iRank[i];
                char tempStr[200];

                strcpy(tempStr, str_a[i]);

                iRank[i] = iRank[j];
                iRank[j] = temp;

                strcpy(str_a[i], str_a[j]);
                strcpy(str_a[j], tempStr);
            }
        }
    }
}

void Ranking::rankPrint(HDC &hdc)
{
    RECT rt[5] = { {25,214,370,252}, {25,254,370,292}, {25,294,370,332}, {25,334,370,372} ,{25,374,370,412} };

    HBITMAP rankBit = (HBITMAP)LoadImage(NULL, L".\\Bitmap\\Prize.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);    //랭크 비트맵
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, rankBit);

    HFONT myFont = CreateFont(20,0,0,0,FW_BOLD,0,0,0,HANGEUL_CHARSET,0,0,0,0,L"나눔고딕");
    HFONT oldFont = (HFONT)SelectObject(memDC, myFont);

    SetBkMode(memDC, TRANSPARENT);

    TCHAR temp[250];

    for(int i = 0;i < 5;++i)
    {
        wsprintf(temp, L"%d등 %d초 ", i+1,iRank[i]);
        lstrcat(temp, str[i]);

        DrawText(memDC, temp, -1, &rt[i], DT_CENTER | DT_WORDBREAK);
    }

    BitBlt(hdc, 144, 29, 400, 600, memDC, 0, 0, SRCCOPY);
    
    SelectObject(memDC, oldBitmap);
    SelectObject(memDC, oldFont);

    DeleteObject(myFont);
    DeleteObject(rankBit);
    DeleteDC(memDC);
}