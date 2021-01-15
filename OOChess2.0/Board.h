#pragma once
#include <vector>

#include "Move.h"
#include "Piece.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>

//TODO Enpassant

class Board
{
public:
	Board();
	void gameInput();
	
private:
	BoardSquare board[8][8];
	HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
	Owner turn;
	std::vector<Piece*> allPieces;


	bool movePiece(char symbol, Coordinate start, Coordinate destination, bool simulate);
	bool kingBecomesChecked(char symbol, Coordinate start, Coordinate destination);
	bool deleteSquare(Coordinate destination);
	void moveBack(char symbol, Coordinate coordinate);
	bool castle(Owner owner, bool kingSide);
	void showSquareInfo(char symbol, int x, int y);
	void clearEmptyPieces();
	void tryCaptureEnpassant(char symbol, Coordinate start, Coordinate destination);


	void checkEnPassantPawns(Owner owner);
	int findPieceIndex(char symbol, int x, int y);
	int kingIsUnderCheck(Owner owner);
	int getKingIndex(Owner owner);
	void updateAllPossibleCoordinates();
	void syncAllPiecesToBoard();
	void clearBoard();
	void drawBoard();
	void resetBoardPieces();
};

