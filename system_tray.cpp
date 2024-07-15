#include <windows.h>
#include <shellapi.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3

NOTIFYICONDATA nid;
HINSTANCE hInst;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddTrayIcon(HWND hwnd);
void AddMenus(HWND hWnd);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;
    WNDCLASSW wc = { 0 };

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc))
        return -1;

    HWND hwnd = CreateWindowW(L"myWindowClass", L"System Tray Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, hInstance, NULL);
    AddTrayIcon(hwnd);
    AddMenus(hwnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void AddTrayIcon(HWND hwnd) {
    ZeroMemory(&nid, sizeof(nid));

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1001;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_APP + 1;
    nid.hIcon = (HICON)LoadImage(NULL, "D:\\Vs_Code\\C++\\systemtrayicon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);

    if (nid.hIcon == NULL) {
        MessageBox(hwnd, "Failed to load icon!", "Error", MB_OK | MB_ICONERROR);
    }

    strcpy(nid.szTip, "systemtrayicon");
    Shell_NotifyIcon(NIM_ADD, &nid);
}

// Window procedure function
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case FILE_MENU_NEW:
            MessageBox(hwnd, "New menu item clicked!", "Menu", MB_OK | MB_ICONINFORMATION);
            break;
        case FILE_MENU_EXIT:
            DestroyWindow(hwnd);
            break;
        }
        break;

    case WM_APP + 1:
        switch (lParam) {
        case WM_LBUTTONDOWN:
            ShowWindow(hwnd, SW_SHOWNORMAL);  
            SetForegroundWindow(hwnd);        
            break;
        case WM_RBUTTONUP:
            POINT pt;
            GetCursorPos(&pt);
            HMENU hMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING,FILE_MENU_EXIT, "Quit");
            AppendMenu(hMenu, MF_STRING, FILE_MENU_NEW, "Help");
            SetForegroundWindow(hwnd); 
            TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
            CloseMenu(hMenu);
            break;
        }
        break;

    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0);
        break;

    // Hide the window    
    case WM_CLOSE:
        ShowWindow(hwnd, SW_HIDE);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void AddMenus(HWND hWnd) {
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, NULL, "SubMenu Item");

    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    AppendMenu(hMenu, MF_STRING, NULL, "Help");

    SetMenu(hWnd, hMenu);
}
