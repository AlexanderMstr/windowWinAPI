//������ ������������ ����� ��������� ����� ������ ����
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include<windows.h>
#include<algorithm>

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) //���������� ������ ��� ������� ���� (����� �����)
{

    static MSG msg{}; //������� ���������
    static HWND hwnd{}, hButton{}, hButton1{}, hButton2{}, hButton3{}, hButton4{}, hChildWnd{}, hChildEdit{}; //���������� ����(���������� �� ����)
    WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; //���-�� ���� 
    //����� ������ ����:
    wc.cbClsExtra = 0; //�������������� ��������� ������ � ������ ����
    wc.cbWndExtra = 0; //�������������� ��������� ������ � ������ ����
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)); //���� ���� ���� 
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW); //������ 
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION); //������ � ���������
    wc.hInstance = hInstance;
    wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT  //��������� ��������� ��������� 
    {
        switch (uMsg)
        {
        case WM_CREATE:
        {
            RECT rc{};
            GetClientRect(hWnd, &rc);

            hButton = CreateWindow(
                L"BUTTON",
                L"�������� ����",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
               0, 0, rc.right, 50,
                hWnd, reinterpret_cast<HMENU>(1337), nullptr, nullptr
            );
            hButton1 = CreateWindow(
                L"BUTTON",
                L"������ ������ ����",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 31, rc.right, 30,
                hWnd, reinterpret_cast<HMENU>(1338), nullptr, nullptr
            );
            hButton2 = CreateWindow(
                L"BUTTON",
                L"�� ���� �����",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 62, rc.right, 30,
                hWnd, reinterpret_cast<HMENU>(1339), nullptr, nullptr
            );
            hButton4 = CreateWindow(
                L"BUTTON",
                L"�����",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 92, rc.right, 30,
                hWnd, reinterpret_cast<HMENU>(1341), nullptr, nullptr
            );
            hButton3 = CreateWindow(
                L"BUTTON",
                L"�����",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 122, rc.right, 30,
                hWnd, reinterpret_cast<HMENU>(1340), nullptr, nullptr
            );
            HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Tahoma");
            SendMessage(hButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), true);
            SendMessage(hButton1, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), true);
            SendMessage(hButton2, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), true);
            SendMessage(hButton4, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), true);
        }
        return 0;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case 1337:
            {
                HWND hCalcWnd = FindWindow(nullptr, L"�����������");
                SetWindowPos(hCalcWnd, HWND_TOPMOST, 100, 100, 0, 0, SWP_NOOWNERZORDER | SWP_NOZORDER);
            }
            break;
            case 1338:
            {
                HWND hCalcWnd = FindWindow(nullptr, L"�����������");
                SetWindowPos(hCalcWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);
            }
            break;
            case 1339:
            {
                HWND hCalcWnd = FindWindow(nullptr, L"�����������");
                SetWindowPos(hCalcWnd, HWND_TOPMOST, 0, 0, 1920, 1080, SWP_NOOWNERZORDER | SWP_NOZORDER);
            }
            break;
            case 1341:
            {
                HWND hCalcWnd = FindWindow(nullptr, L"�����������");
                SetWindowPos(hCalcWnd, HWND_NOTOPMOST, 0, 0,0, 0, SWP_NOSIZE);
            }
            break;
            case 1340:
            {
                PostQuitMessage(EXIT_SUCCESS);
            }
            break;
            }
        }
        return 0;
        case WM_SIZE:
        {
            SetWindowPos(hButton, nullptr, 0, 0, LOWORD(lParam), 30, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER); //������ ������ ���������� ��� ������ ����
            SetWindowPos(hButton1, nullptr, 0, 0, LOWORD(lParam), 30, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
            SetWindowPos(hButton2, nullptr, 0, 0, LOWORD(lParam), 30, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
            SetWindowPos(hButton4, nullptr, 0, 0, LOWORD(lParam), 30, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
            SetWindowPos(hButton3, nullptr, 0, 0, LOWORD(lParam), 30, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
        }
        return 0;
        case WM_DESTROY:
        {
            PostQuitMessage(EXIT_SUCCESS);
        }
        return 0;
        }
        return DefWindowProc(hWnd, uMsg, wParam, lParam);//���� ��������� �� ��������������
    };

    wc.lpszClassName = L"MyAppClass"; //��� ������
    wc.lpszMenuName = nullptr; //��������� �� ����
    wc.style = CS_VREDRAW | CS_HREDRAW; //����� ����

    if (!RegisterClassEx(&wc)) //��������, ���� ������
        return EXIT_FAILURE;

 
    if (hwnd = CreateWindow(wc.lpszClassName, L"������� ����", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
        return EXIT_FAILURE;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, nullptr, 0, 0)) //���� ��������� ���������
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); //��������� 
    }

    return static_cast<int>(msg.wParam);
}