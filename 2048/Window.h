#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

namespace GGL
{
	class Window {
	public:
		static void CreateGUI();
		static void NormalTextFont(HDC);
		static void SmallTextFont(HDC);
		static RECT* GetInfoBarRect();
		static void CleanFonts();
		static void ChangeResolution(int, int);
	};
}

#endif