#pragma once
class Ranking
{
    /* 5위까지 나타냄 */
    bool bRank;     //랭킹 실행 여부

    TCHAR str[6][200];     //아스키코드를 유니코드로 변환시켜줄 변수
    char str_a[6][200];      //랭크를 읽어옴

    int iRank[6];        //앞의 기록을 가져옴

public:
    Ranking(void);
    ~Ranking(void);

    void setBRank(bool bSetRank);
    bool getBRank();

    void rankRead(HWND &hWnd);     //랭크를 읽어옴
    void swap();        //오름차순으로 정렬

    void rankPrint(HDC &hdc);       //랭킹을 출력
};