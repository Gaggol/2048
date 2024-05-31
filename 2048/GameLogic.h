#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <Windows.h>
#include "Settings.h"

namespace GGL
{
	class GameLogic {
	public:
		void SetupGame();
		void Cleanup();
		LRESULT MSGLoop(HWND, UINT, WPARAM, LPARAM);
		void Update();
		static GameLogic instance() { static GameLogic GL; return GL; }
		void TryTick();
		void InvalidatePiece(Piece*);
		bool IsIgnoringKeys();
	private:
		Piece* orgBoard[BoardSize][BoardSize];
		int score;
		bool hasMoved;
		bool isTryingToMove;
		void StartGame();
		bool SpawnPiece();
		bool SpawnPiece(bool);
		void Debug();
		Direction _direction();
		void TryToMove(Direction);
		bool IsBoardFilled();
		void ResetTickTimer();
		HWND hwnd;
		bool ignoreKeys;
	};
}

#endif