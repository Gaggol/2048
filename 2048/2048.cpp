
#include <iostream>
#include <vector>
#include <chrono>
#include "Settings.h"
#include "Piece.h"

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <sys/sysinfo.h>
#endif

using namespace GGL;

#ifdef _WIN32
int wmain(int argc, wchar_t* argv[]) {
	srand(GetTickCount());
#elif __linux__
int main(int argc, char* argv[]) {
	struct sysinfo x;
	sysinfo(&x);
	srand(x.uptime);
#endif
	for(int y = 0; y < BoardSize; y++) {
		for(int x = 0; x < BoardSize; x++) {
			Board[y][x] = new Piece(x, y, 0);
		}
	}

	int r1, r2, r3;
	int _startingPieces = StartingPieces;

	while(_startingPieces > 0) {
		r1 = rand() % BoardSize;
		r2 = rand() % BoardSize;
		r3 = rand() % 2;
		if(Board[r1][r2]->Size == 0) {
			Board[r1][r2]->Size = ValidSpawnNumbers[r3];
			_startingPieces--;
		}
	}

	std::wstring inputBuffer;
	Piece* orgBoard[BoardSize][BoardSize] = {};
	int score = 0;
	bool hasMoved = false;

	while(true) {
		score = 0;
		hasMoved = false;
		for(int y = 0; y < BoardSize; y++) {
			for(int x = 0; x < BoardSize; x++) {
				std::wcout << Board[y][x]->Size << " ";
				score += Board[y][x]->Size;
			}
			std::wcout << std::endl;
		}
		std::wcout << "Score: " << score << std::endl;

		std::wcin >> inputBuffer;
#ifdef _WIN32
		system("CLS");
#elif __linux__
		system("clear");
#endif
		wchar_t charPress = toupper(inputBuffer[0]);

		for(int y = 0; y < BoardSize; y++) {
			for(int x = 0; x < BoardSize; x++) {
				if(orgBoard[y][x] != nullptr) {
					delete[] orgBoard[y][x];
				}
				orgBoard[y][x] = new Piece(y, x, Board[y][x]->Size);
			}
		}

		if(charPress == L'W' || charPress == L'A' || charPress == L'D' || charPress == 'S') {
			bool moved = false;
			do {
				moved = false;
				for(int y = 0; y < BoardSize; y++) {
					for(int x = 0; x < BoardSize; x++) {
						if(Board[y][x]->Size > 0) {
							if(Board[y][x]->Move(charPress)) {
								moved = true;
							}
						}
					}
				}
			} while(moved);
		}

		for(int y = 0; y < BoardSize; y++) {
			for(int x = 0; x < BoardSize; x++) {
				if(orgBoard[y][x]->Size != Board[y][x]->Size) {
					hasMoved = true;
					break;
				}
			}
			if(hasMoved) break;
		}

		bool filledBoard = true;
		for(int y = 0; y < BoardSize; y++) {
			for(int x = 0; x < BoardSize; x++) {
				if(Board[y][x]->Size == 0) {
					filledBoard = false;
					break;
				}
				if(Board[y][x]->ValidNeighbours()) {
					filledBoard = false;
					break;
				}
			}
			if(!filledBoard) break;
		}

		if(filledBoard) {
			std::wcout << "You Lose" << std::endl;
			break;
		}
		if(hasMoved) {
			while(true) {
				r1 = rand() % BoardSize;
				r2 = rand() % BoardSize;
				r3 = rand() % 2;
				if(Board[r1][r2]->Size == 0) {
					Board[r1][r2]->Size = ValidSpawnNumbers[r3];
					break;
				}
			}
		}
	}

	for(int y = 0; y < BoardSize; y++) {
		for(int x = 0; x < BoardSize; x++) {
			delete Board[y][x];
			delete orgBoard[y][x];
		}
	}

	std::wcout << "Enter to Exit";
	std::wcin.ignore();
	std::wcin.get();
}
