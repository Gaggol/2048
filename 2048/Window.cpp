#include "Settings.h"
#include "Window.h"
#include "GameLogic.h"
#include <chrono>
#include <iostream>

namespace GGL
{

	RECT InfoBarRect = { spacingOffset, 0, (Resolution[0] - spacingOffset), infoBarOffset};
	RECT* Window::GetInfoBarRect() {
		return &InfoBarRect;
	}

	LOGFONTW lf { 0 };
	HFONT smallFont = nullptr;
	HFONT normalFont = nullptr;

	void Window::ChangeResolution(int x, int y) {
		
	}

	void Window::NormalTextFont(HDC hdc) {
		if(normalFont == nullptr) {
			lf = { 0 };
			normalFont = { 0 };

			lf.lfHeight = 40;
			lf.lfWeight = FW_BOLD;

			wcscpy_s(lf.lfFaceName, L"Arial");

			normalFont = CreateFontIndirectW(&lf);
		}
		SelectObject(hdc, normalFont);
	}

	void Window::SmallTextFont(HDC hdc) {
		if(smallFont == nullptr) {
			lf = { 0 };
			smallFont = { 0 };

			lf.lfHeight = 20;
			lf.lfWeight = FW_BOLD;

			wcscpy_s(lf.lfFaceName, L"Arial");
			smallFont = CreateFontIndirectW(&lf);
		}
		SelectObject(hdc, smallFont);
	}

	void Window::CleanFonts() {
		//delete smallFont;
		//delete normalFont;
	}


	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if(GGL::GameLogic::GL()->MSGLoop(hwnd, uMsg, wParam, lParam) == 0)
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

		// LEFT TOP RIGHT BOTTOM

		RECT clientArea = { 0, 0,
			Resolution[0] + spacingOffset,
			Resolution[1] + spacingOffset + infoBarOffset
		};
		AdjustWindowRect(&clientArea, style, false);
		
		int screenWidth = (GetSystemMetrics(SM_CXSCREEN) - clientArea.right)/2;
		int screenHeight = (GetSystemMetrics(SM_CYSCREEN) - clientArea.bottom)/2;

		HWND gui;
		gui = CreateWindowExW(0, L"GGL - 2048", L"2048", style, screenWidth, screenHeight, clientArea.right - clientArea.left, clientArea.bottom - clientArea.top, NULL, NULL, hInstance, NULL);

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
			GGL::GameLogic::GL()->TryTick();
		}
	}
}