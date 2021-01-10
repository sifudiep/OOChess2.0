#pragma once
#include "Piece.h"

class Bishop : public Piece
{
	using Piece::Piece;

	void updatePossibleCoordinates(BoardSquare board[8][8]) override;
};

