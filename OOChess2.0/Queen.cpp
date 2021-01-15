#include "Queen.h"


void Queen::updatePossibleCoordinates(BoardSquare board[8][8], std::vector<Piece*> &allPieces) {
	possibleCoordinates.clear();

	// Move like BISHOP
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


	// MOVE LIKE ROOK
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
