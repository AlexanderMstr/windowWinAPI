#pragma once
#include <Windows.h>

#define UNICODE
#define _UNICODE

class Window
{
public:
    Window();
    ~Window(void);
    void CreateWin(); //������� ����
private:
    void GethInstence();
};
