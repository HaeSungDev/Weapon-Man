#pragma once
class Map
{
    HBITMAP backBit;      //���ȭ�� ��Ʈ�� �ڵ�
    HBITMAP mapBit;     //�� ��Ʈ�� �ڵ�

    int (*iMap)[XMAP];   //�� �迭

public:

    Map(void);
    ~Map(void);

    void saveMap(int (*ISetMap)[XMAP]);     //�� ����
    void saveBitmap(HWND &hWnd);        //��Ʈ�� ����

    void printBack(HDC &hdc);       //���ȭ�� ���
    void printMap(HDC &hdc);        //�� ���
};