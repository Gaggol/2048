// 2048.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <chrono>
#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <sys/sysinfo.h>
#endif
class Piece {
public:
	bool Move(wchar_t input);
	bool ValidNeighbours();
	int X;
	int Y;
	int Size;
	Piece(int x, int y, int size);
};

Piece* board[4][4] {};
int boardSize = 4;
int validSpawnNumbers[2] = { 2, 4 };
int startingPieces = 2;

bool Piece::ValidNeighbours() {
	Piece* neighbour = nullptr;
	if(Y - 1 >= 0) {
		neighbour = board[Y - 1][X];
		if(neighbour->Size == Size) return true;
	}
	if(Y + 1 < boardSize) {
		neighbour = board[Y + 1][X];
		if(neighbour->Size == Size) return true;
	}
	if(X - 1 >= 0) {
		neighbour = board[Y][X - 1];
		if(neighbour->Size == Size) return true;
	}
	if(X + 1 < boardSize) {
		neighbour = board[Y][X + 1];
		if(neighbour->Size == Size) return true;
	}
	return false;
}

Piece::Piece(int x, int y, int size) {
	X = x;
	Y = y;
	Size = size;
}

bool Piece::Move(wchar_t input) {
	Piece* neighbour = nullptr;
	if(input == L'W') {
		if(Y - 1 < 0) return false;
		neighbour = board[Y - 1][X];
	}
	if(input == L'A') {
		if(X - 1 < 0) return false;
		neighbour = board[Y][X - 1];
	}
	if(input == L'S') {
		if(Y + 1 >= boardSize) return false;
		neighbour = board[Y + 1][X];
	}
	if(input == L'D') {
		if(X + 1 >= boardSize) return false;
		neighbour = board[Y][X + 1];
	}
	if(neighbour == nullptr) return false;

	if(neighbour->Size > 0 && neighbour->Size != Size) {
		return false;
	}
	if(neighbour->Size == Size) {
		neighbour->Size *= 2;
		if(neighbour->Size >= 2048) {
			std::wcout << "Big Score!" << std::endl;
		}
	}
	if(neighbour->Size == 0) {
		neighbour->Size = Size;
	}
	Size = 0;
	return true;
}

#ifdef _WIN32

int wmain(int argc, wchar_t* argv[]) {
	srand(GetTickCount());

#elif __linux__

int main(int argc, char* argv[]) {
	struct sysinfo x;
	srand(x.uptime);

#endif

	for(int y = 0; y < boardSize; y++) {
		for(int x = 0; x < boardSize; x++) {
			board[y][x] = new Piece(x, y, 0);
		}
	}

	int r1, r2, r3;

	while(startingPieces > 0) {
		r1 = rand() % boardSize;
		r2 = rand() % boardSize;
		r3 = rand() % 2;
		if(board[r1][r2]->Size == 0) {
			board[r1][r2]->Size = validSpawnNumbers[r3];
			startingPieces--;
		}
	}
	
	std::wstring inputBuffer;
	Piece* orgBoard[4][4] {};
	int score = 0;
	bool hasMoved = false;
	while(true) {
		score = 0;
		hasMoved = false;
		for(int y = 0; y < boardSize; y++) {
			for(int x = 0; x < boardSize; x++) {
				std::wcout << board[y][x]->Size << " ";
				score += board[y][x]->Size;
			}
			std::wcout << std::endl;
		}
		std::wcout << "Score: " << score << std::endl;

		std::wcin >> inputBuffer;
		system("CLS");
		wchar_t charPress = toupper(inputBuffer[0]);

		for(int y = 0; y < boardSize; y++) {
			for(int x = 0; x < boardSize; x++) {
				delete[] orgBoard[y][x];
				orgBoard[y][x] = new Piece(y, x, board[y][x]->Size);
			}
		}

		if(charPress == L'W' || charPress == L'A' || charPress == L'D' || charPress == 'S') {
			bool moved = false;
			do {
				moved = false;
				for(int y = 0; y < boardSize; y++) {
					for(int x = 0; x < boardSize; x++) {
						if(board[y][x]->Size > 0) {
							if(board[y][x]->Move(charPress)) {
								moved = true;
							}
						}
					}
				}
			} while(moved);
		}

		for(int y = 0; y < boardSize; y++) {
			for(int x = 0; x < boardSize; x++) {
				if(orgBoard[y][x]->Size != board[y][x]->Size) {
					hasMoved = true;
					break;
				}
			}
			if(hasMoved) break;
		}

		bool filledBoard = true;
		for(int y = 0; y < boardSize; y++) {
			for(int x = 0; x < boardSize; x++) {
				if(board[y][x]->Size == 0) {
					filledBoard = false;
					break;
				}
				if(board[y][x]->ValidNeighbours()) {
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
				r1 = rand() % boardSize;
				r2 = rand() % boardSize;
				r3 = rand() % 2;
				if(board[r1][r2]->Size == 0) {
					board[r1][r2]->Size = validSpawnNumbers[r3];
					break;
				}
			}
		}
	}

	for(int y = 0; y < boardSize; y++) {
		for(int x = 0; x < boardSize; x++) {
			delete[] board[y][x];
			delete[] orgBoard[y][x];
		}
	}

	std::wcout << "Enter to Exit";
}
