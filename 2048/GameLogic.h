#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <Windows.h>
#include "Settings.h"

namespace GGL
{
	class GameLogic {
	public:
		static GameLogic* GL() { return &glInstance; }
		void SetupGame();
		void Cleanup();
		LRESULT MSGLoop(HWND, UINT, WPARAM, LPARAM);
		void Update();
		void TryTick();
		void InvalidatePiece(Piece*);
		bool IsIgnoringKeys();
	private:
		static GameLogic glInstance;
		Piece* orgBoard[BoardSize][BoardSize];
		int score;
		int oldScore;
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
		bool gameOver;
		bool uiCreated;
	};
}

#endif