#pragma once
#include <Windows.h>

#define UNICODE
#define _UNICODE

class Window
{
public:
    Window();
    ~Window(void);
    void CreateWin(); //Создать окно
private:
    void GethInstence();
};
