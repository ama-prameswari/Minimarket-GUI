#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <cstdio>

#define ID_FILE_EXIT 1
#define GENERATE_BUTTON 2

int itemPrice[100];
int itemAmount[100];
char* itemName[100];
int num = 0;

HWND hName, hPrice, hAmount, hOut1, hOut2, hOut3, hOut4;

void CreateMainMenu(HWND hwnd)
{
    HMENU hMenu = CreateMenu();
    HMENU hFMItem = CreateMenu();

    AppendMenu(hFMItem, MF_STRING, NULL, "New");
    AppendMenu(hFMItem, MF_STRING, NULL, "Open");
    AppendMenu(hFMItem, MF_STRING, ID_FILE_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFMItem, "File");
    AppendMenu(hMenu, MF_STRING, NULL, "Edit");
    AppendMenu(hMenu, MF_STRING, NULL, "Tools");
    AppendMenu(hMenu, MF_STRING, NULL, "Help");
    SetMenu(hwnd, hMenu);
}

void AddControls(HWND hwnd)
{
    CreateWindowW(L"Static", L"LIST MENU", WS_VISIBLE | WS_CHILD, 80, 50, 110, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"1. Bread", WS_VISIBLE | WS_CHILD, 80, 80, 110, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"2. Brownies", WS_VISIBLE | WS_CHILD, 80, 110, 110, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"3. Cheese Cake", WS_VISIBLE | WS_CHILD, 80, 140, 110, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"4. Donuts", WS_VISIBLE | WS_CHILD, 80, 170, 110, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"5. Sponge Cake", WS_VISIBLE | WS_CHILD, 80, 200, 110, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"6. Toast Bread", WS_VISIBLE | WS_CHILD, 80, 230, 110, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"7. Coffee Latte", WS_VISIBLE | WS_CHILD, 80, 260, 110, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"8. Milk Tea", WS_VISIBLE | WS_CHILD, 80, 290, 110, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"9. Soda", WS_VISIBLE | WS_CHILD, 80, 320, 110, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"10. Yogurt", WS_VISIBLE | WS_CHILD, 80, 350, 110, 38, hwnd, NULL, NULL, NULL);


    CreateWindowW(L"Static", L"Item: ", WS_VISIBLE | WS_CHILD, 200, 50, 98, 38, hwnd, NULL, NULL, NULL);
    hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 300, 50, 98, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Price: ", WS_VISIBLE | WS_CHILD, 200, 90, 98, 38, hwnd, NULL, NULL, NULL);
    hPrice = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 300, 90, 98, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Quantity: ", WS_VISIBLE | WS_CHILD, 200, 130, 98, 38, hwnd, NULL, NULL, NULL);
    hAmount = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 300, 130, 98, 38, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Calculate", WS_VISIBLE | WS_CHILD, 450, 130, 98, 38, hwnd, (HMENU)GENERATE_BUTTON, NULL, NULL);

    // hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 100, 290, 300, 200, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Item", WS_VISIBLE | WS_CHILD, 205, 220, 150, 40, hwnd, NULL, NULL, NULL);
    hOut1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 205, 260, 150, 250, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Price", WS_VISIBLE | WS_CHILD, 355, 220, 150, 40, hwnd, NULL, NULL, NULL);
    hOut2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 355, 260, 150, 250, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Quantity", WS_VISIBLE | WS_CHILD, 505, 220, 150, 40, hwnd, NULL, NULL, NULL);
    hOut3 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 505, 260, 150, 250, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Sub-Total", WS_VISIBLE | WS_CHILD, 655, 220, 150, 40, hwnd, NULL, NULL, NULL);
    hOut4 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 655, 260, 150, 250, hwnd, NULL, NULL, NULL);
}

int powInt(int x, int y)
{
    for(int i = 0; i < y; i++)
    {
        x *= 10;
    }
    return x;
}

int parseInt(char* chars)
{
    int sum = 0;
    int len = strlen(chars);
    for(int x = 0; x < len; x++)
    {
        int n = chars[len - (x + 1)] - '0';
        sum = sum + powInt(n, x);
    }
    return sum;
}
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("MINI MARKET"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           744,                 /* The programs width */
           675,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            CreateMainMenu(hwnd);
            AddControls(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;

        case WM_COMMAND:
            {
                switch(LOWORD(wParam))
                {
                case GENERATE_BUTTON:
                {

                        int lenPrice = GetWindowTextLength(hPrice)+1;
                        static char teksPrice[250];
                        GetWindowText(hPrice, teksPrice, lenPrice);

                        int lenAmount = GetWindowTextLength(hAmount)+1;
                        static char teksAmount[500];
                        GetWindowText(hAmount, teksAmount, lenAmount);

                        //char* charPrice = teksPrice;
                        //char* charAmount = teksAmount;

                        int intPrice = parseInt(teksPrice);
                        int intAmount = parseInt(teksAmount);
                        //int intName = parseInt(teksName);

                        //static char space[50];

                        //int itemNum = intAmount;
                        //int itemPrice = intPrice;
                        //int subtotal = itemNum * itemPrice;

                        itemPrice[num] = intPrice;
                        itemAmount[num] = intAmount;
                        //int subtotal = intPrice * intAmount;

                        static char teks1[1000];
                        static char teks2[1000];
                        static char teks3[1000];
                        static char teks4[1000];
                        static char space[20];
                        //static char char_total[50];
                        static char eol[20];

                        char num_total[100];

                        strcpy(teks1, "");
                        strcpy(teks2, "");
                        strcpy(teks3, "");
                        strcpy(teks4, "");
                        strcpy(space, " ");
                        strcpy(eol, "\r\n");
                        //strcpy(char_total, "TOTAL=");

                        int subtotal = 0, total = 0;
                        for(int x = 0; x <= num; x++)
                        {
                            char name[500];
                            std::sprintf(name, "%d", x+1);
                            strcat(teks1, name);
                            strcat(teks1, eol);

                            //char num_name[lenName];
                            //std::sprintf(num_name, "%d", itemName[x]);
                            //strcat(teks1, num_name);
                            //strcat(teks1, eol);

                            char num_price[lenPrice];
                            std::sprintf(num_price, "%d", itemPrice[x]);
                            strcat(teks2, num_price);
                            strcat(teks2, eol);
                            //strcat(teks, space);

                            char num_amount[lenAmount];
                            std::sprintf(num_amount, "%d", itemAmount[x]);
                            strcat(teks3, num_amount);
                            strcat(teks3, eol);
                            //strcat(teks, space);

                            total += itemPrice[x] * itemAmount[x];
                            subtotal = itemPrice[x] * itemAmount[x];
                            char num_subtotal[100];
                            std::sprintf(num_subtotal, "%d", subtotal);
                            std::sprintf(num_total, "%d", total);
                            //strcat(teks, char_total);
                            strcat(teks4, num_subtotal);
                            strcat(teks4, eol);

                        }

                        //char price_char[50], amount_char[50], subtotal_char[50];
                        //std::sprintf(price_char, "%d", itemPrice);
                        //std::sprintf(amount_char, "%d", itemNum);
                        //std::sprintf(subtotal_char, "%d", subtotal);

                        //SetWindowText(hOut1, teksName);
                        //SetWindowText(hOut2, price_char);
                        //SetWindowText(hOut3, amount_char);
                        //SetWindowText(hOut4, subtotal_char);

                        SetWindowText(hOut1, teks1);
                        SetWindowText(hOut2, teks2);
                        SetWindowText(hOut3, teks3);
                        SetWindowText(hOut4, teks4);
                        //SetWindowText(hTotal, num_total);
                        num++;
                break;
                }
                break;
                }
            }
            break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
