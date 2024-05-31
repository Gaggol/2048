#ifndef SETTINGS_H
#define SETTINGS_H

namespace GGL
{
	class Piece;

	const int BoardSize = 4;
	const int ValidSpawnNumbers[2] = { 2,4 };
	const int StartingPieces = 2;
	extern Piece* Board[BoardSize][BoardSize];
}

#endif