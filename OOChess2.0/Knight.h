#pragma once
#include "Piece.h"

class Knight : public Piece
{
	using Piece::Piece;
	
	void updatePossibleCoordinates(BoardSquare board[8][8], std::vector<Piece*> &allPieces) override;
};

