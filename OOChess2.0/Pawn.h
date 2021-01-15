#pragma once
#include "Piece.h"

class Pawn: public Piece
{
	using Piece::Piece;
	void updatePossibleCoordinates(BoardSquare board[8][8], std::vector<Piece*> &allPieces) override;
	int findPieceIndex(std::vector<Piece*> allPieces, int x, int y);
	
};

