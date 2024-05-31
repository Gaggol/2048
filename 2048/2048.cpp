
#include <iostream>
#include <vector>
#include <chrono>
#include "Settings.h"
#include "Piece.h"
#include <Windows.h>
#include "Window.h"
#include "GameLogic.h"

using namespace GGL;

#ifndef _WIN32
int main() {
	std::cout << "OS Not Supported.\nUse the Console version instead." << std::endl;
	return 0;
}
#endif

int wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PWSTR l, int i) {
	srand((unsigned int)GetTickCount64());
	GameLogic::instance().SetupGame();
	GameLogic::instance().Cleanup();
}
