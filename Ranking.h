#pragma once
class Ranking
{
    /* 5������ ��Ÿ�� */
    bool bRank;     //��ŷ ���� ����

    TCHAR str[6][200];     //�ƽ�Ű�ڵ带 �����ڵ�� ��ȯ������ ����
    char str_a[6][200];      //��ũ�� �о��

    int iRank[6];        //���� ����� ������

public:
    Ranking(void);
    ~Ranking(void);

    void setBRank(bool bSetRank);
    bool getBRank();

    void rankRead(HWND &hWnd);     //��ũ�� �о��
    void swap();        //������������ ����

    void rankPrint(HDC &hdc);       //��ŷ�� ���
};