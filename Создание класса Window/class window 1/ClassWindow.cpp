#include "ClassWindow.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
TCHAR CLASS_NAME[] = L"ClassWindow";

Window::Window()
{
}

Window::~Window(void)
{
}

void Window::CreateWin()
{
    HINSTANCE hInstence = (HINSTANCE)GetModuleHandle(NULL);

    WNDCLASS wc;

    wc.cbClsExtra = 0;                              //�������������� ��������� ������
    wc.cbWndExtra = 0;                              //�������������� ��������� ����
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);    //���� ����
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);       //������
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);         //������
    wc.hInstance = hInstence;                       //���������� ����������
    wc.lpfnWndProc = WndProc;                       //��� �-�� ��������� ���������
    wc.lpszClassName = CLASS_NAME;                  //��� ������ ����
    wc.lpszMenuName = NULL;                         //������ �� ������� ����
    wc.style = CS_VREDRAW | CS_HREDRAW;             //����� ����

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, L"�� ������� ���������������� ����� ����!", L"������ �����������", MB_ICONERROR | MB_OK);
    }

    HWND hwnd = CreateWindow(CLASS_NAME, L"Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstence, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"�� ������� ���������������� ����� ����!", L"������ �����������", MB_OK);
    }
    ShowWindow(hwnd, SW_SHOW);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}