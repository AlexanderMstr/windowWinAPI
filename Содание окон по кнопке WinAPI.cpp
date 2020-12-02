//По нажатию на кнопку создает бессконечное кол-во других окон (нужно хэндлы склдывать куда-нибудь в массив)
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include<windows.h>
#include<algorithm>
#include<string>

static std::pair<bool, HWND> AddWindow(const std::wstring&& winClass, const std::wstring&& title, HWND hParentWnd, const WNDPROC callbackk)
{
    UnregisterClass(winClass.c_str(), GetModuleHandle(nullptr)); //класс окна
    WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
    HWND hWindow{};
    wc.cbClsExtra = 0; //дополнительное выделение памяти в классе окна
    wc.cbWndExtra = 0; //дополнительное выделение памяти в классе окна
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)); //цвет фона окна 
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW); //курсор 
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION); //иконка в заголовке
    wc.lpfnWndProc = callbackk;
    wc.lpszMenuName = winClass.c_str(); //указатель на меню
    wc.lpszClassName = winClass.c_str();
    wc.style = CS_VREDRAW | CS_HREDRAW; //стиль окна
    //функтор: 
    const auto create_window = [&hWindow, &winClass, &title, &hParentWnd]()->std::pair<bool, HWND> {
        if (hWindow = CreateWindow(winClass.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, 300, 300, nullptr, nullptr, nullptr, nullptr); !hWindow)
            return{ false,nullptr };

        ShowWindow(hWindow, SW_SHOWDEFAULT);
        UpdateWindow(hWindow);
        return { true,hWindow };
    };
    if (!RegisterClassEx(&wc)) {
        return create_window();
    }

    return create_window();

}
int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) //вызываемый объект сам очищает стэк (ТОЧКА ВХОДА)
{

    static MSG msg{}; //система сообщений
    static HWND hwnd{}, hButton{}, hButton1{}, hChildWnd{}, hChildEdit{}; //дискриптор окна(информация об окне)
    WNDCLASSEX wc{ sizeof(WNDCLASSEX) }; //хар-ки окна 
    //часть класса окна:
    wc.cbClsExtra = 0; //дополнительное выделение памяти в классе окна
    wc.cbWndExtra = 0; //дополнительное выделение памяти в классе окна
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)); //цвет фона окна 
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW); //курсор 
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION); //иконка в заголовке
    wc.hInstance = hInstance;
    wc.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT  //процедура обработка сообщений 
    {
        switch (uMsg)
        {
        case WM_CREATE:
        {
            RECT rc{};
            GetClientRect(hWnd, &rc);

            hButton = CreateWindow(
                L"BUTTON",
                L"Создать новое окно",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                0, 0, rc.right, 30,
                hWnd, reinterpret_cast<HMENU>(1337), nullptr, nullptr
            );

            HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Tahoma");
            SendMessage(hButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), true);

        }
        return 0;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case 1337:
            {
                
                const auto [flag, hChild] = AddWindow(L"MyAppChildClass", L"New window", hWnd, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT {


                    return DefWindowProc(hWnd, uMsg, wParam, lParam);
                    });
                hChildWnd = hChild;
            }
            break;
            }
        }
        return 0;
        case WM_SIZE:
        {
            SetWindowPos(hButton, nullptr, 0, 0, LOWORD(lParam), 30, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER); //ширина кнопка изменяется под размер окна
        }
        return 0;
        case WM_DESTROY:
        {
            PostQuitMessage(EXIT_SUCCESS);
        }
        return 0;
        }
        return DefWindowProc(hWnd, uMsg, wParam, lParam);//если сообщение не обрабатывается
    };

    wc.lpszClassName = L"MyAppClass"; //имя класса
    wc.lpszMenuName = nullptr; //указатель на меню
    wc.style = CS_VREDRAW | CS_HREDRAW; //стиль окна

    if (!RegisterClassEx(&wc)) //проверка, если ошибка
        return EXIT_FAILURE;

    if (hwnd = CreateWindow(wc.lpszClassName, L"Основное окно", WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN) - 600) / 2,
        (GetSystemMetrics(SM_CXSCREEN) - 600) / 2,
        600, 600, nullptr, nullptr, wc.hInstance, nullptr); hwnd == INVALID_HANDLE_VALUE)
        return EXIT_FAILURE;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, nullptr, 0, 0)) //цикл обработки сообщений
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); //обработка 
    }

    return static_cast<int>(msg.wParam);
}