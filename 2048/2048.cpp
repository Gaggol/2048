
#include <iostream>
#include <vector>
#include <chrono>
#include "Settings.h"
#include "Piece.h"
#include <Windows.h>
#include "Window.h"
#include "GameLogic.h"


#ifndef _WIN32
int main() {
	std::cout << "OS Not Supported.\nUse the Console version instead." << std::endl;
	return 0;
}
#endif

int wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int) {

#ifdef _DEBUG
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONIN$", "r", stdin);
	freopen_s(&f, "CONOUT$", "w", stdout);
	freopen_s(&f, "CONOUT$", "w", stderr);
#endif

	srand((unsigned int)GetTickCount64());
	
	GGL::GameLogic* GL = GGL::GameLogic::GL();

	GL->SetupGame();
	GL->Cleanup();
	GGL::Window::CleanFonts();
}