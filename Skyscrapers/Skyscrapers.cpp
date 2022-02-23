// Skyscrapers.cpp : Определяет точку входа для приложения.
//


#include "framework.h"
#include "Skyscrapers.h"
#include "Func.h"
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#define MAX_LOADSTRING 100


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SKYSCRAPERS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SKYSCRAPERS));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SKYSCRAPERS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SKYSCRAPERS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

int gameMode = 1;
bool play = false;
int time_s = 0;
int time_m = 0;
int time_h = 0;
char timech[9];
TCHAR playernameT[20];
char playername[20];
char record[500];

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit[99];
    static HWND hBtn;
    static HWND hBtn1;
    static HWND hBtn2;
    static HWND hEdt1;
    static HWND hStat;
    static HWND hStat1;
    static HWND hTimer;
    static HWND hListBox;
    char filename[60];
    char massive[101][55] = {};
    char name[55] = "";
    char tru[3] = "";
    int level = 0;

    HFONT hFont = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial" );
    
    switch (message)
    {
    case WM_CREATE: {
        if (encryption) {
            LoadRecordsEncoded();
        }
        else {
            LoadRecords();
        }

        save_load_buttons_show(hBtn1, hBtn2, hWnd, hFont, hListBox);
        hListBox = CreateWindowExA(NULL, "LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL, 1000, 250, 150, 50, hWnd, (HMENU)4, NULL, NULL);

        char massive[101][60] = {};
        SendMessage(hListBox, WM_SETREDRAW, FALSE, 0L);
        for (int i = 0; i < 99; i++) {
            char name[60] = "";
            char tru[3] = "";
            if (debug) {
                sprintf_s(name, "..\\game%dsolve.txt", i);
            }
            else {
                sprintf_s(name, "..\\game%d.txt", i);
            }

            FILE* fin = fopen(name, "rt");
            if (fin != NULL) {
                sprintf_s(tru, "%d", i);
                strcpy(massive[i - 1], name);
                SendMessageA(hListBox, LB_ADDSTRING, 0, (LPARAM)tru);
                fclose(fin);
            }
        }
        SendMessage(hListBox, WM_SETREDRAW, TRUE, 0L);
        InvalidateRect(hListBox, NULL, TRUE);

        SetTimer(hWnd, 1, 1000, 0);
        }
        break;
    case WM_TIMER: {
        if (play) {
            time_s += 1;
            if (time_s == 60) {
                time_m += 1;
                time_s = 0;
            }
            if (time_m == 60) {
                time_h += 1;
                time_m = 0;
                time_s = 0;
            }
        }
        if (time_s < 10) {
            if (time_m < 10) {
                if (time_h < 10) {
                    sprintf(timech, "0%d:0%d:0%d", time_h, time_m, time_s);
                }
                else {
                    sprintf(timech, "%d:0%d:0%d", time_h, time_m, time_s);
                }
            }
            else {
                if (time_h < 10) {
                    sprintf(timech, "0%d:%d:0%d", time_h, time_m, time_s);
                }
                else {
                    sprintf(timech, "%d:%d:0%d", time_h, time_m, time_s);
                }
            }
        }
        else {
            if (time_m < 10) {
                if (time_h < 10) {
                    sprintf(timech, "0%d:0%d:%d", time_h, time_m, time_s);
                }
                else {
                    sprintf(timech, "%d:0%d:%d", time_h, time_m, time_s);
                }
            }
            else {
                if (time_h < 10) {
                    sprintf(timech, "0%d:%d:%d", time_h, time_m, time_s);
                }
                else {
                    sprintf(timech, "%d:%d:%d", time_h, time_m, time_s);
                }
            }
        }
        DestroyWindow(hTimer);
        hTimer = CreateWindowA("STATIC", timech, WS_CHILD | WS_VISIBLE, 1050, 50, 59, 20, hWnd, (HMENU)3, NULL, NULL);
        SendMessage(hTimer, WM_SETFONT, (LPARAM)WPARAM(hFont), TRUE);
        }
        break;
    case WM_KEYDOWN:
        if (wParam == 0x53) {
            catch_data(hWnd);
            strcpy(filename, filename_search(hListBox, hWnd));
            saveLevel(filename);
        }
        if (wParam == 0x4C) {
            strcpy(filename, filename_search(hListBox, hWnd));
            loadLevel(filename);

            DestroyWindow(hBtn);
            for (int i = 0; i < 100; i++) {
                DestroyWindow(hEdit[i]);
            }
            int x = 56;
            int y = 60;
            int a = 0;
            char dig[2];
            for (int i = 1; i <= N - 2; i++) {
                x = 56;
                for (int j = 1; j <= N - 2; j++) {
                    a = i * 10 + j;
                    if (mas_search(i, j) == 0) {
                        sprintf_s(dig, "%s", "");
                    }
                    else {
                        sprintf_s(dig, "%d", mas_search(i, j));
                    }
                    hEdit[a] = CreateWindowA("eDit", dig, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_NUMBER | SW_SHOWNORMAL | EN_SETFOCUS, x, y, 15, 21, hWnd, (HMENU)a, hInst, NULL);
                    SendMessage(hEdit[a], WM_SETFONT, WPARAM(hFont), TRUE);
                    x += 30;
                }
                y += 30;
            }
            hBtn = CreateWindow(L"BUTTON", L"Check", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (x - 10) / 2, y + 30, 50, 35, hWnd, (HMENU)0, NULL, NULL);
            SendMessage(hBtn, WM_SETFONT, WPARAM(hFont), TRUE);
            play = true;
            time_s = 0;
            time_m = 0;
            time_h = 0;

            GetWindowText(hEdt1, playernameT, sizeof(playernameT));

            wcstombs(playername, playernameT, 20);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        if (wParam == VK_ESCAPE) {
            if (gameMode) {
                hStat = CreateWindowA("STATIC", DrawRecords(), WS_VISIBLE, 0, 0, 1000, 400, hWnd, NULL, hInst, NULL);
                SendMessage(hStat, WM_SETFONT, (LPARAM)WPARAM(hFont), TRUE);
                gameMode = 0;
                SetFocus(hWnd);
            }
            else {
                DestroyWindow(hStat);
                gameMode = 1;
            }
        }       
        
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            SelectObject(hdc, hFont);
                if (play) {
                    printmain(hdc);
                    DestroyWindow(hEdt1);
                }
                else {
                    save_load_buttons_show(hBtn1, hBtn2, hWnd, hFont, hListBox);

                    TextOut(hdc, 200, 200, L"Please type your name and load level: ", 39);
                    hEdt1 = CreateWindowW(_T("edit"), _T("Noname"), WS_CHILD | WS_VISIBLE | WS_BORDER, 460, 200, 160, 21, hWnd, (HMENU)5, hInst, NULL);
                    SendMessage(hEdt1, WM_SETFONT, WPARAM(hFont), TRUE);
                    
                }
            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        if (wmId == 0) {
            catch_data(hWnd);
            if (checkIfTrue(hWnd)) {
                MessageBoxA(hWnd, "Верно!", "Проверка результата", MB_OK);
                addRecord(playername, time_h, time_m, time_s);
                if (encryption) {
                    SaveRecordsEncoded();
                }
                else {
                    SaveRecords();
                }
                
            }
            
        }
        else if (wmId == 1) {
            strcpy(filename, filename_search(hListBox, hWnd));
            loadLevel(filename);
            
            DestroyWindow(hBtn);
            for (int i = 0; i < 100; i++) {
                DestroyWindow(hEdit[i]);
            }
            int x = 56;
            int y = 60;
            int a = 0;
            char dig[2];
            for (int i = 1; i <= N - 2; i++) {
                x = 56;
                for (int j = 1; j <= N - 2; j++) {
                    a = i * 10 + j;
                    if (mas_search(i, j) == 0) {
                        sprintf_s(dig, "%s", "");
                    }
                    else {
                        sprintf_s(dig, "%d", mas_search(i, j));
                    }
                    hEdit[a] = CreateWindowA("eDit", dig, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_NUMBER | SW_SHOWNORMAL | EN_SETFOCUS, x, y, 15, 21, hWnd, (HMENU)a, hInst, NULL);
                    SendMessage(hEdit[a], WM_SETFONT, WPARAM(hFont), TRUE);
                    x += 30;
                }
                y += 30;
            }
            hBtn = CreateWindow(L"BUTTON", L"Check", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (x - 10) / 2, y + 30, 50, 35, hWnd, (HMENU)0, NULL, NULL);
            SendMessage(hBtn, WM_SETFONT, WPARAM(hFont), TRUE);
            play = true;
            time_s = 0;
            time_m = 0;
            time_h = 0;

            GetWindowText(hEdt1, playernameT, sizeof(playernameT));

            wcstombs(playername, playernameT, 20);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (wmId == 2) {
            catch_data(hWnd);
            strcpy(filename, filename_search(hListBox, hWnd));
            saveLevel(filename);
        }
        else if (wmId == IDM_ABOUT) {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        }
        else if (wmId == IDM_EXIT) {
            DestroyWindow(hWnd);
        }
        else {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
        
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
