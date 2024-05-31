#ifndef PIECE_H
#define PIECE_H

namespace GGL
{
	class Piece {
	public:
		int X;
		int Y;
		int Size;
		bool hasIncreasedSize = false;
		bool newSpawn = false;
		ColorTile bgColor = ColorTileNone;
		DWORD txtColor = 0;
		Piece(int x, int y, int size);
		RECT Rect;
		bool Move(Direction dir);
		bool ValidNeighbours();
		void SetSize(int size);
	};
}

#endif