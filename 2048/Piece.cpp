#include "Settings.h"
#include "Piece.h"
namespace GGL
{
	bool Piece::ValidNeighbours() {
		Piece* neighbour = nullptr;
		if(Y - 1 >= 0) {
			neighbour = Board[Y - 1][X];
			if(neighbour->Size == Size) return true;
		}
		if(Y + 1 < BoardSize) {
			neighbour = Board[Y + 1][X];
			if(neighbour->Size == Size) return true;
		}
		if(X - 1 >= 0) {
			neighbour = Board[Y][X - 1];
			if(neighbour->Size == Size) return true;
		}
		if(X + 1 < BoardSize) {
			neighbour = Board[Y][X + 1];
			if(neighbour->Size == Size) return true;
		}
		return false;
	}

	bool Piece::Move(wchar_t input) {
		Piece* neighbour = nullptr;
		if(input == L'W') {
			if(Y - 1 < 0) return false;
			neighbour = Board[Y - 1][X];
		}
		if(input == L'A') {
			if(X - 1 < 0) return false;
			neighbour = Board[Y][X - 1];
		}
		if(input == L'S') {
			if(Y + 1 >= BoardSize) return false;
			neighbour = Board[Y + 1][X];
		}
		if(input == L'D') {
			if(X + 1 >= BoardSize) return false;
			neighbour = Board[Y][X + 1];
		}
		if(neighbour == nullptr) return false;

		if(neighbour->Size > 0 && neighbour->Size != Size) {
			return false;
		}
		if(neighbour->Size == Size) {
			neighbour->Size *= 2;
		}
		if(neighbour->Size == 0) {
			neighbour->Size = Size;
		}
		Size = 0;
		return true;
	}
}