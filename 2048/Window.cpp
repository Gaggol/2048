#include "Settings.h"
#include "Window.h"
#include "GameLogic.h"
#include <chrono>

namespace GGL
{

	HFONT hFont;
	void Window::NormalTextFont(HDC hdc) {
		LOGFONTW lf = { 0 };

		lf.lfHeight = 40;
		lf.lfWeight = FW_BOLD;
		
		wcscpy_s(lf.lfFaceName, L"Arial");

		hFont = CreateFontIndirectW(&lf);

		SelectObject(hdc, hFont);
	}

	void Window::SmallTextFont(HDC hdc) {
		LOGFONTW lf = { 0 };
		lf.lfHeight = 20;
		lf.lfWeight = FW_BOLD;
		wcscpy_s(lf.lfFaceName, L"Arial");
		hFont = CreateFontIndirectW(&lf);
		SelectObject(hdc, hFont);
	}


	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if(GameLogic::instance().MSGLoop(hwnd, uMsg, wParam, lParam) == 0)
			return 0;
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}

	void Window::CreateGUI() {
		HINSTANCE hInstance = GetModuleHandle(NULL);

		WNDCLASS wc = { 0 };

		wc.lpfnWndProc = (WNDPROC)&WndProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = L"GGL - 2048";

		RegisterClassW(&wc);

		DWORD style = WS_CAPTION | WS_SYSMENU;

		RECT clientArea = { 0, 0, Resolution, Resolution };
		AdjustWindowRect(&clientArea, style, false);

		HWND gui;
		gui = CreateWindowExW(0, L"GGL - 2048", L"2048", style, CW_USEDEFAULT, CW_USEDEFAULT, clientArea.right - clientArea.left, clientArea.bottom - clientArea.top, NULL, NULL, hInstance, NULL);

		if(gui == NULL) {
			return;
		}

		ShowWindow(gui, SW_SHOW);

		MSG msg = {};

		while(WM_QUIT != msg.message) {
			if(PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {	
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
				continue;
			}
			GameLogic::instance().TryTick();
		}		
	}
}