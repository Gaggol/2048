#include "Settings.h"
#include "Piece.h"

namespace GGL
{
	DWORD Settings::GetColor(ColorTile bgColor) {
		try {
			return ColorTileMap.at(bgColor);
		} catch(const std::out_of_range& a) {
			return ColorTileDefault;
		}
	}

	std::unordered_map<ColorTile, DWORD> Settings::ColorTileMap = {
			{ ColorTile2,		0x00DAE4EE },
			{ ColorTile4,		0x00C8E0ED },
			{ ColorTile8,		0x0079B1F2 },
			{ ColorTile16,		0x006395F5 },
			{ ColorTile32,		0x005F7CF6 },
			{ ColorTile64,		0x003B5EF6 },
			{ ColorTile128,		0x0072CFED },
			{ ColorTile256,		0x0061CCED },
			{ ColorTile512,		0x0050C8ED },
			{ ColorTile1024,	0x003FC5ED },
			{ ColorTile2048,	0x002EC2ED },
	};

	Piece* Board[BoardSize][BoardSize];
}