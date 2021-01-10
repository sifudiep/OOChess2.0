#include "King.h"

void King::updatePossibleCoordinates(BoardSquare board[8][8]) {
	possibleCoordinates.clear();

	if (coordinate.x + 1 < 8) {
		addPossibleBoardSquare(board, coordinate.x + 1, coordinate.y);
	}

	if (coordinate.x - 1 >= 0) {
		addPossibleBoardSquare(board, coordinate.x - 1, coordinate.y);
	}

	if (coordinate.y + 1 < 8) {
		addPossibleBoardSquare(board, coordinate.x, coordinate.y + 1);
	}

	if (coordinate.y - 1 >= 0) {
		addPossibleBoardSquare(board, coordinate.x, coordinate.y - 1);
	}

	if (coordinate.y + 1 < 8 && coordinate.x + 1 < 8) {
		addPossibleBoardSquare(board, coordinate.x + 1, coordinate.y + 1);
	}

	if (coordinate.y + 1 < 8 && coordinate.x - 1 >= 0) {
		addPossibleBoardSquare(board, coordinate.x - 1, coordinate.y + 1);
	}

	if (coordinate.y - 1 >= 0 && coordinate.x + 1 < 8) {
		addPossibleBoardSquare(board, coordinate.x + 1, coordinate.y - 1);
	}

	if (coordinate.y - 1 >= 0 && coordinate.x - 1 >= 0) {
		addPossibleBoardSquare(board, coordinate.x - 1, coordinate.y - 1);
	}
}