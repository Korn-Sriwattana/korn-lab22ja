#include <windows.h>
#include <stdio.h>
#include <iomanip>

double a, b;
char t[100], Text1[100], Text2[100];

HWND Ask, Plusbutton, Minusbutton, multipliedbutton, Dividebutton, Textbox1, Textbox2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {
        case WM_CREATE:
            ask = CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD, 20, 15, 190, 25, hwnd, NULL, NULL, NULL);
            Plusbutton = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | WS_BORDER, 65, 115, 25, 25, hwnd, (HMENU)1, NULL, NULL);
            Minusbutton = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | WS_BORDER, 95, 115, 25, 25, hwnd, (HMENU)2, NULL, NULL);
            multipliedbutton = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | WS_BORDER, 125, 115, 25, 25, hwnd, (HMENU)3, NULL, NULL);
            Dividebutton = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | WS_BORDER, 155, 115, 25, 25, hwnd, (HMENU)4, NULL, NULL);
            Textbox1 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 50, 50, 150, 25, hwnd, NULL, NULL, NULL);
            Textbox2 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 50, 80, 150, 25, hwnd, NULL, NULL, NULL);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1:
    	GetWindowText(Textbox1, Text1, 100);
    	GetWindowText(Textbox2, Text2, 100);
				a = atof(Text1);
				b = atof(Text2);
				sprintf(t, "%.6f", a + b);
				MessageBox(hwnd, t, "Result", MB_OK);
				break;
			case 2:
				GetWindowText(Textbox1, Text1, 100);
				GetWindowText(Textbox2, Text2, 100);
				a = atof(Text1);
				b = atof(Text2);
				sprintf(t, "%.6f", a - b);
				MessageBox(hwnd, t, "Result", MB_OK);
				break;
			case 3:
				GetWindowText(Textbox1, Text1, 100);
				GetWindowText(Textbox2, Text2, 100);
				a = atof(Text1);
				b = atof(Text2);
				sprintf(t, "%.6f", a * b);
				MessageBox(hwnd, t, "Result", MB_OK);
				break;
			case 4:
				GetWindowText(Textbox1, Text1, 100);
				GetWindowText(Textbox2, Text2, 100);
				a = atof(Text1);
				b = atof(Text2);
				if (b != 0) {
					sprintf(t, "%.6f", a / b);
					MessageBox(hwnd, t, "Result", MB_OK);
				} else {
					MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
				}
				break;

            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(2548, 101, 224)); //Change background colour
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(0, "WindowClass", "My Calculator", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU ,
                          CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
