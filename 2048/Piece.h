#ifndef PIECE_H
#define PIECE_H

namespace GGL
{
	class Piece {
	public:
		int X;
		int Y;
		int Size;
		DWORD bgColor = 0;
		DWORD txtColor = 0;
		Piece(int x, int y, int size) {
			X = x;
			Y = y;
			Size = size;
		};
		bool Move(wchar_t input);
		bool ValidNeighbours();
		void SetSize(int size);
	};
}

#endif