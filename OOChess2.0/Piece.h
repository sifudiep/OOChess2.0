#pragma once

#include <vector>

#include "Coordinate.h"
#include "Owner.h"
#include "BoardSquare.h"


class Piece {
public:
	Piece(Coordinate c_coordinate, Owner c_owner, char c_symbol);
	bool addPossibleBoardSquare(BoardSquare board[8][8], int x, int y);
	virtual void updatePossibleCoordinates(BoardSquare board[8][8], std::vector<Piece*> &allPieces) = 0;

	Coordinate coordinate;
	std::vector<Coordinate> possibleCoordinates;
	Coordinate formerCoordinate;
	Owner owner;
	char symbol;
	bool firstMove;
	bool justMadeFirstMove;
	
};


