#pragma once

#include "resource.h"
#include "stdafx.h"

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int					TabCtrl_AddTextItem(HWND, LPTSTR);
RECT				GetControlRect(int, long, long);
HWND				CreateControl(LPCTSTR, LPCTSTR, DWORD, HWND, int);