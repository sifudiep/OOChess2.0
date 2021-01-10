#include "Rook.h"

void Rook::updatePossibleCoordinates(BoardSquare board[8][8]) {
	possibleCoordinates.clear();

	for (int i = 1; coordinate.y + i < 8; i++) {
		bool squareIsOccupiedByOwner = addPossibleBoardSquare(board, coordinate.x, coordinate.y + i);
		if (squareIsOccupiedByOwner)
			break;
	}

	for (int i = 1; coordinate.y - i >= 0; i++) {
		bool squareIsOccupiedByOwner = addPossibleBoardSquare(board, coordinate.x, coordinate.y - i);
		if (squareIsOccupiedByOwner)
			break;
	}

	for (int i = 1; coordinate.x + i < 8; i++) {
		bool squareIsOccupiedByOwner = addPossibleBoardSquare(board, coordinate.x + i, coordinate.y);
		if (squareIsOccupiedByOwner)
			break;
	}

	for (int i = 1; coordinate.x - i >= 0; i++) {
		bool squareIsOccupiedByOwner = addPossibleBoardSquare(board, coordinate.x - i, coordinate.y);
		if (squareIsOccupiedByOwner)
			break;
	}
}
