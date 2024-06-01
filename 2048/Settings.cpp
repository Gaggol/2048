#include "Settings.h"
#include "Piece.h"

namespace GGL
{
	void Settings::MoveRECT(RECT* rect, int offsetWidth, int offsetHeight) {
		rect->left += offsetWidth;
		rect->right += offsetWidth;
		rect->top += offsetHeight;
		rect->bottom += offsetHeight;
	}

	HBRUSH Settings::GetBrush(ColorTile bgColor) {
		return BrushMap.at(bgColor);
	}

	ColorTile Settings::GetTileColor(int size) {
		if(size <= 2048) {
			return (ColorTile)size;
		}
		return ColorTileBig;
	}

	std::unordered_map<ColorTile, HBRUSH> Settings::BrushMap = {};

	void Settings::DestroyBrushes() {

	}

	void Settings::GenerateBrushes() {
		for(const auto& pair : ColorTileMap) {
			BrushMap.insert(std::make_pair(pair.first, CreateSolidBrush(pair.second)));
		}
	}

	std::unordered_map<ColorTile, DWORD> Settings::ColorTileMap = {
			{ ColorTileNone,	0x00000000 },
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
			{ ColorTileBig,		0x00646464 },
	};

	Piece* Board[BoardSize][BoardSize];
}