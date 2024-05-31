
#include "GameLogic.h"
#include "Piece.h"
#include "Window.h"
#include <iostream>
#include "Input.h"
#include <chrono>

namespace GGL
{
	Piece* orgBoard[BoardSize][BoardSize] = {};
	Input input;

	void GameLogic::SetupGame() {
		score = 0;
		hasMoved = false;
		isTryingToMove = false;
		for(int y = 0; y < BoardSize; y++) {
			for(int x = 0; x < BoardSize; x++) {
				Board[y][x] = new Piece(x, y, 0);
			}
		}
		StartGame();
	}

	void GameLogic::StartGame() {
		int _startingPieces = StartingPieces;

		while(_startingPieces > 0) {
			if(SpawnPiece(false)) {
				_startingPieces--;
			}
		}
#ifdef _DEBUG
		Debug();
#endif
		Window::CreateGUI();
	}

	Direction GameLogic::_direction() {
		if(input.GetKeyDown(VK_W)) return DirectionUp;
		if(input.GetKeyDown(VK_A)) return DirectionLeft;
		if(input.GetKeyDown(VK_D)) return DirectionRight;
		if(input.GetKeyDown(VK_S)) return DirectionDown;
		return DirectionNone;
	}
	
	void GameLogic::Debug() {
		//system("CLS");
		for(int y = 0; y < BoardSize; y++) {
			for(int x = 0; x < BoardSize; x++) {
				std::wcout << Board[y][x]->Size << " ";
				score += Board[y][x]->Size;
			}
			std::wcout << std::endl;
		}
		std::wcout << "Score: " << score << std::endl;
	}

	void GameLogic::TryToMove(Direction dir) {
		for(int y = 0; y < BoardSize; y++) {
			for(int x = 0; x < BoardSize; x++) {
				if(orgBoard[y][x] != nullptr) {
					delete[] orgBoard[y][x];
				}
				orgBoard[y][x] = new Piece(y, x, Board[y][x]->Size);
			}
		}
		bool moved = false;
		do {
			moved = false;
			for(int y = 0; y < BoardSize; y++) {
				for(int x = 0; x < BoardSize; x++) {
					Piece* piece = Board[y][x];
					if(piece->Size > 0) {
						if(piece->Move(dir)) {
							moved = true;
						}
					}
				}
			}
		} while(moved);

		for(int y = 0; y < BoardSize; y++) {
			for(int x = 0; x < BoardSize; x++) {
				Piece* orgPiece = orgBoard[y][x];
				Piece* piece = Board[y][x];
				piece->hasIncreasedSize = false;
				if(orgPiece->Size != piece->Size) {
					hasMoved = true;
				}
			}
			if(hasMoved) break;
		}

		if(hasMoved) {
			while(true) {
				if(SpawnPiece()) {
					break;
				}
			}
		}
	}

	bool GameLogic::IsBoardFilled() {
		bool filledBoard = true;
		for(int y = 0; y < BoardSize; y++) {
			for(int x = 0; x < BoardSize; x++) {
				Piece* piece = Board[y][x];
				if(piece->Size == 0) {
					filledBoard = false;
					break;
				}
				if(piece->ValidNeighbours()) {
					filledBoard = false;
					break;
				}
			}
			if(!filledBoard) break;
		}
		return filledBoard;
	}

	void GameLogic::InvalidatePiece(Piece* piece) {
		InvalidateRect(hwnd, NULL, false);
	}

	void GameLogic::Update() {
		hasMoved = false;
		isTryingToMove = false;


		Direction dir = _direction();

		if(dir != DirectionNone) {
			input.FlushKeys();
			TryToMove(dir);
#ifdef _DEBUG
			//Debug();
#endif
		}

		if(hasMoved) {
			InvalidateRect(hwnd, NULL, true);
			UpdateWindow(hwnd);
		}
		IsBoardFilled();
		ignoreKeys = false;
	}

	void GameLogic::Cleanup() {
		for(int y = 0; y < BoardSize; y++) {
			for(int x = 0; x < BoardSize; x++) {
				delete Board[y][x];
				delete orgBoard[y][x];
			}
		}
	}

	Piece* lastPiece;

	bool GameLogic::SpawnPiece() {
		return SpawnPiece(true);
	}

	bool GameLogic::SpawnPiece(bool newSpawn) {
		int r1, r2, r3;
		r1 = rand() % BoardSize;
		r2 = rand() % BoardSize;
		r3 = rand() % 10;
		if(Board[r1][r2]->Size == 0) {
			if(r3 < 10) {
				Board[r1][r2]->SetSize(ValidSpawnNumbers[0]);
			} else {
				Board[r1][r2]->SetSize(ValidSpawnNumbers[1]);
			}
			if(newSpawn) {
				if(lastPiece != nullptr) {
					lastPiece->newSpawn = false;
				}
				lastPiece = Board[r1][r2];
				lastPiece->newSpawn = true;
			}
			return true;
		}
		return false;
	}

	bool GameLogic::IsIgnoringKeys() {
		return ignoreKeys;
	}

	LRESULT GameLogic::MSGLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch(uMsg) {

			case WM_KEYDOWN:
				if(ignoreKeys) return 0;
				ignoreKeys = true;
				input.SetKeyDown((int)wParam);

				GameLogic::instance().Update();
				GameLogic::instance().ResetTickTimer();
				InvalidateRect(hwnd, NULL, true);
				UpdateWindow(hwnd);
				return 0;

			case WM_CREATE:
				Settings::GenerateBrushes();
				this->hwnd = hwnd;
				return 0;

			case WM_DESTROY:
				Settings::DestroyBrushes();
				PostQuitMessage(0);
				return 0;

			case WM_PAINT:
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				FillRect(hdc, &ps.rcPaint, ColorBGBrush);
				for(int y = 0; y < BoardSize; y++) {
					for(int x = 0; x < BoardSize; x++) {
						Piece* p = Board[y][x];
						FillRect(hdc, &p->Rect, Settings::GetBrush(p->bgColor));
						if(p->Size > 0) {
							Window::NormalTextFont(hdc);
							SetTextColor(hdc, p->txtColor);
							SetBkMode(hdc, TRANSPARENT);
							wchar_t buffer[16];
							wsprintfW(buffer, L"%d", p->Size);
							DrawTextW(hdc, buffer, -1, &p->Rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
							if(p->newSpawn) {
								Window::SmallTextFont(hdc);
								SetTextColor(hdc, Color_Red);
								DrawTextW(hdc, L"NEW", -1, &p->Rect, DT_CENTER | DT_SINGLELINE | DT_BOTTOM);
							}
						}
					}
				}
				EndPaint(hwnd, &ps);
				return 0;
		}
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);

	}

	uint64_t tickTimeStamp = 0;
	uint64_t nextTick = ((double)1 / (double)FPS) * 1000;
	uint64_t MStimeStamp = 0;
	uint64_t TimeSinceEpochMilliSec() {
		using namespace std::chrono;
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}

	void GameLogic::ResetTickTimer() {
		MStimeStamp = TimeSinceEpochMilliSec();
		tickTimeStamp = MStimeStamp + nextTick;
	}

	void GameLogic::TryTick() {
		MStimeStamp = TimeSinceEpochMilliSec();
		if(tickTimeStamp < MStimeStamp) {
			Update();
			ResetTickTimer();
		}
		Sleep(50);
	}
}