// Hathor.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "Hathor.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' ""version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Constants:
#define MAX_LOADSTRING		100
#define GUI_BORDER			10
#define WS_CONTROL			WS_VISIBLE | WS_CHILD

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Controls:
HWND tabControl;
HWND downloadsList;
#define IDC_TAB				100
#define IDC_DOWNLOADS		101

void DebugPrint(LPTSTR str)
{
#ifdef _DEBUG
	MessageBox(0, str, "Debug", 0);
#endif
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	SONGDATA * sd = (SONGDATA*)malloc(sizeof(SONGDATA));
	sd->duration = 200;
	FindAndChooseVidForSong("Get Lucky", "Daft Punk", sd);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_HATHOR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Initialize common controls.
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_STANDARD_CLASSES | ICC_LISTVIEW_CLASSES;
	if (!InitCommonControlsEx(&iccx))
		MessageBox(0, "Failed to initialize controls.", "Error", MB_ICONERROR);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HATHOR));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HATHOR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	// wcex.lpszMenuName = MAKEINTRESOURCE(IDC_HATHOR);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:

		// Setup tab control.
		tabControl = CreateControl(WC_TABCONTROL, NULL, 0, hWnd, IDC_TAB);
		TabCtrl_AddTextItem(tabControl, "By Song");
		TabCtrl_AddTextItem(tabControl, "YouTube");
		TabCtrl_AddTextItem(tabControl, "Spotify");
		SendMessage(tabControl, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), NULL);

		// Setup downloads list.
		downloadsList = CreateControl(WC_LISTVIEW, NULL, 0, hWnd, IDC_DOWNLOADS);
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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

// Helper function: Adds a tab to a tab control.
int TabCtrl_AddTextItem(HWND tab, LPTSTR text)
{
	TCITEM tci;
	tci.mask = TCIF_TEXT;
	tci.pszText = text;
	tci.cchTextMax = lstrlen(text);
	tci.lParam = NULL;

	return TabCtrl_InsertItem(tab, TabCtrl_GetItemCount(tab), &tci);
}

// Decide what rectangle to use for a control based on window size.
// Left and top are x and y, right and botttom are width and height.
RECT GetControlRect(int control, long width, long height)
{
	RECT result;

	switch (control)
	{
	case IDC_TAB:
		result.left = result.top = GUI_BORDER;
		result.right = (width / 2) - (long)(GUI_BORDER * 1.5);
		result.bottom = height - GUI_BORDER * 2;
		break;
	case IDC_DOWNLOADS:
		result.left = (width / 2) + (long)(GUI_BORDER * 0.5);
		result.top = GUI_BORDER;
		result.right = (width / 2) - (long)(GUI_BORDER * 1.5);
		result.bottom = height - GUI_BORDER * 2;
		break;
	}

	return result;
}

// Helper function: make a control (in case you couldn't figure that out)
HWND CreateControl(LPCTSTR className, LPCTSTR title, DWORD controlStyle, HWND parent, int id)
{
	RECT cli, ctr;
	GetClientRect(parent, &cli);
	ctr = GetControlRect(id, cli.right, cli.bottom);

	return CreateWindowEx(0, className, title, WS_CONTROL | controlStyle,
		ctr.left, ctr.top, ctr.right, ctr.bottom,
		parent, (HMENU)id, GetModuleHandle(NULL), NULL);
}