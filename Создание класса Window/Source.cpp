//Создание окна через класс (другой способ)
#include<Windows.h>
#include<memory>
LRESULT CALLBACK _WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
TCHAR CLASS_NAME[] = L"Window";

class Window
{
public:
    Window() = default;

    void Create(LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, RECT pos)
    {
        HINSTANCE hInstence = (HINSTANCE)GetModuleHandle(NULL);
        WNDCLASS wc = {};

        wc.lpfnWndProc = _WindowProc;
        wc.hInstance = hInstence;
        wc.lpszClassName = CLASS_NAME;

        RegisterClass(&wc);

        m_hWnd = ::CreateWindowW(CLASS_NAME, L"Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstence, this);


        if (m_hWnd == NULL)
        {
            MessageBox(NULL, L"Не удалось зарегистрировать класс окна!", L"Ошибка регистрации", MB_OK);
        }

    }

    void showWindow()
    {
        ::ShowWindow(m_hWnd, SW_SHOW);
    }

private:
    LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
        }
    }

    friend LRESULT CALLBACK _WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        Window* p;
        if (uMsg != WM_CREATE)
            p = reinterpret_cast<Window*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
        else
        {
            ::SetWindowLongPtr(hwnd, GWLP_USERDATA, lParam);
            p = reinterpret_cast<Window*>(lParam);
        }

        if (p)
            return p->WndProc(uMsg, wParam, lParam);

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    HWND m_hWnd = NULL;
};

int WINAPI WinMain(HINSTANCE hInstence, HINSTANCE, LPSTR pCmdLine, int nCmdLine)
{
    Window w;
    w.Create("Window", "Window", CS_VREDRAW, { 10, 10, 10, 100 });
    w.showWindow();
    // Run the message loop.
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

}