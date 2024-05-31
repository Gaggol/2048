#ifndef PIECE_H
#define PIECE_H

namespace GGL
{
	class Piece {
	public:
		int X;
		int Y;
		int Size;
		Piece(int x, int y, int size) {
			X = x;
			Y = y;
			Size = size;
		};
		bool Move(wchar_t input);
		bool ValidNeighbours();
	};
}

#endif