#pragma once
#include <vector>

#include "Move.h"
#include "Piece.h"
#include <windows.h>


class Board
{
public:
	Board();
	void gameInput();
	
private:
	std::vector<Piece*> allPieces;
	BoardSquare board[8][8];
	HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
	Owner turn;

	bool movePiece(char symbol, Coordinate start, Coordinate destination, bool simulate);
	bool kingBecomesChecked(char symbol, Coordinate start, Coordinate destination);
	void captureSquare(Coordinate destination);
	void moveBack(char symbol, Coordinate coordinate);

	int getKingIndex(Owner owner);
	void updateAllPossibleCoordinates();
	void syncAllPiecesToBoard();
	void clearBoard();
	void drawBoard();
	void resetBoardPieces();
};

