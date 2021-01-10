#include "Bishop.h"

void Bishop::updatePossibleCoordinates(BoardSquare board[8][8]) {
	possibleCoordinates.clear();

	for (int i = 1; coordinate.y + i < 8 && coordinate.x + i < 8; i++) {
		bool squareIsOccupiedByOwner = addPossibleBoardSquare(board, coordinate.x + i, coordinate.y + i);
		if (squareIsOccupiedByOwner)
			break;
	}

	for (int i = 1; coordinate.y + i < 8 && coordinate.x - i >= 0; i++) {
		bool squareIsOccupiedByOwner = addPossibleBoardSquare(board, coordinate.x - i, coordinate.y + i);
		if (squareIsOccupiedByOwner)
			break;
	}

	for (int i = 1; coordinate.y - i >= 0 && coordinate.x + i < 8; i++) {
		bool squareIsOccupiedByOwner = addPossibleBoardSquare(board, coordinate.x + i, coordinate.y - i);
		if (squareIsOccupiedByOwner)
			break;
	}

	for (int i = 1; coordinate.y - i >= 0 && coordinate.x - i >= 0; i++) {
		bool squareIsOccupiedByOwner = addPossibleBoardSquare(board, coordinate.x - i, coordinate.y - i);
		if (squareIsOccupiedByOwner)
			break;
	}
}
