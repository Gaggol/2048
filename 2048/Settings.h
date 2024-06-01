#ifndef SETTINGS_H
#define SETTINGS_H
#include <Windows.h>
#include <unordered_map>
#include <stdexcept>
#include <math.h>
namespace GGL
{
	class Piece;

	const int BoardSize = 4;
	const int ValidSpawnNumbers[2] = { 2, 4 };
	const int StartingPieces = 2;
	extern Piece* Board[BoardSize][BoardSize];

	const int FPS = 60;

	static int Resolution[2] = { 800, 800 };
	
	static int PixelsPerUnit[2] = { Resolution[0] / BoardSize, Resolution[1] / BoardSize };
	static int spacingOffset = 6;
	static int infoBarOffset = 40;

	//0x00BBGGRR
	const DWORD Color_Red = 0x000000FF;
	const DWORD Color_Green = 0x0000FF00;
	const DWORD Color_Blue = 0x00FF0000;
	const DWORD Color_White = 0x00FFFFFF;
	const DWORD Color_Black = 0x00000000;

	const DWORD Color_MenuBG = 0x00AAAAAA;
	const DWORD Color_MenuButton = 0x00CCCCCC;
	const DWORD Color_MenuButtonBTN = 0x00DDDDDD;
	const DWORD Color_MenuButtonBTN_HI = 0x00EEEEEE;

	const HBRUSH BrushColorMenuBG = CreateSolidBrush(Color_MenuBG);
	const HBRUSH BrushColorMenuButton = CreateSolidBrush(Color_MenuButton);
	const HBRUSH BrushColorMenuButtonBTN = CreateSolidBrush(Color_MenuButtonBTN);
	const HBRUSH BrushColorMenuButtonBTNHI = CreateSolidBrush(Color_MenuButtonBTN_HI);

	const DWORD ColorBG = 0x00F0F0F0;
	const HBRUSH ColorBGBrush = CreateSolidBrush(ColorBG);

	const DWORD ColorTextLo = 0x00656E77;
	const DWORD ColorTextHi = 0x00F2F6F9;
	
	const DWORD ColorTileDefault = 0x00646464;

	const enum Direction {
		DirectionNone = -1,
		DirectionLeft = 0,
		DirectionUp = 1,
		DirectionRight = 2,
		DirectionDown = 3
	};

	const enum ColorTile {
		ColorTileNone = 0,
		ColorTile2 = 2,
		ColorTile4 = 4,
		ColorTile8 = 8,
		ColorTile16 = 16,
		ColorTile32 = 32,
		ColorTile64 = 64,
		ColorTile128 = 128,
		ColorTile256 = 256,
		ColorTile512 = 512,
		ColorTile1024 = 1024,
		ColorTile2048 = 2048,
		ColorTileBig = 9999
	};

	class Settings {
	public:
		static ColorTile GetTileColor(int size);
		static HBRUSH GetBrush(ColorTile bgColor);
		static void DestroyBrushes();
		static void GenerateBrushes();
		static void MoveRECT(RECT*, int, int);
	private:
		static std::unordered_map<ColorTile, HBRUSH> BrushMap;
		static std::unordered_map<ColorTile, DWORD> ColorTileMap;
		/*
		std::unordered_map<ColorTile, DWORD> ColorTileMap = {
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
		*/
	};
}
#endif