#include "Settings.h"
#include "Piece.h"
#include "GameLogic.h"
namespace GGL
{
	Piece::Piece(int x, int y, int size) {
		X = x;
		Y = y;
		Size = size;
		Rect = { x * PixelsPerUnit, y * PixelsPerUnit, (x+1) * PixelsPerUnit, (y+1) * PixelsPerUnit };
		SetSize(size);
	};

	void Piece::SetSize(int size) {
		Size = size;
		txtColor = ColorTextHi;
		switch(size) {
			case 2:
				txtColor = ColorTextLo;
				break;
			case 4:
				txtColor = ColorTextLo;
				break;
		}
		bgColor = Settings::GetTileColor(size);
	}

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

	bool Piece::Move(Direction dir) {
		Piece* neighbour = nullptr;
		switch(dir) {
			case GGL::DirectionLeft:
				if(X - 1 < 0) return false;
				neighbour = Board[Y][X - 1];
				break;
			case GGL::DirectionUp:
				if(Y - 1 < 0) return false;
				neighbour = Board[Y - 1][X];
				break;
			case GGL::DirectionRight:
				if(X + 1 >= BoardSize) return false;
				neighbour = Board[Y][X + 1];
				break;
			case GGL::DirectionDown:
				if(Y + 1 >= BoardSize) return false;
				neighbour = Board[Y + 1][X];
				break;
			default:
				break;
		}
		if(neighbour == nullptr) return false;

		if(neighbour->Size > 0) {
			if(neighbour->Size != Size) {
				return false;
			}
			if(neighbour->hasIncreasedSize) {
				return false;
			}
			if(neighbour->Size == Size) {
				neighbour->SetSize(Size * 2);
				neighbour->hasIncreasedSize = true;
			}
		}
		else if(neighbour->Size == 0) {
			neighbour->SetSize(Size);
		}
		
		if(hasIncreasedSize) hasIncreasedSize = false;
		SetSize(0);

		GameLogic::instance().InvalidatePiece(neighbour);
		GameLogic::instance().InvalidatePiece(this);

		return true;
	}
}