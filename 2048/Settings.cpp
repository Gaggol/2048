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

	HBRUSH Settings::GetBrush(int size) {
		return BrushMap.at(size);
	}

	std::unordered_map<int, HBRUSH> Settings::BrushMap = {};

	void Settings::DestroyBrushes() {

	}

	void Settings::GenerateBrushes() {
		for(const auto& pair : ColorTileMap) {
			BrushMap.insert(std::make_pair(pair.first, CreateSolidBrush(pair.second)));
		}
	}

	std::unordered_map<int, DWORD> Settings::ColorTileMap = {
			{ 0,		0x00000000 },
			{ 1,		0x00646464 },
			{ 2,		0x00DAE4EE },
			{ 4,		0x00C8E0ED },
			{ 8,		0x0079B1F2 },
			{ 16,		0x006395F5 },
			{ 32,		0x005F7CF6 },
			{ 64,		0x003B5EF6 },
			{ 128,		0x0072CFED },
			{ 256,		0x0061CCED },
			{ 512,		0x0050C8ED },
			{ 1024,		0x003FC5ED },
			{ 2048,		0x002EC2ED },
	};

	Piece* Board[BoardSize][BoardSize];
}