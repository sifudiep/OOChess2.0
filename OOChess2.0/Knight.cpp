#include "Knight.h"

void Knight::updatePossibleCoordinates(BoardSquare board[8][8], std::vector<Piece*> &allPieces) {
	possibleCoordinates.clear();

	if (coordinate.y + 2 < 8) {
		if (coordinate.x + 1 < 8) {
			addPossibleBoardSquare(board, coordinate.x + 1, coordinate.y + 2);
		}

		if (coordinate.x - 1 >= 0) {
			addPossibleBoardSquare(board, coordinate.x - 1, coordinate.y + 2);
		}
	}

	if (coordinate.y - 2 >= 0) {
		if (coordinate.x + 1 < 8) {
			addPossibleBoardSquare(board, coordinate.x + 1, coordinate.y - 2);
		}

		if (coordinate.x - 1 >= 0) {
			addPossibleBoardSquare(board, coordinate.x - 1, coordinate.y - 2);
		}
	}

	if (coordinate.x + 2 < 8) {
		if (coordinate.y + 1 < 8) {
			addPossibleBoardSquare(board, coordinate.x + 2, coordinate.y + 1);

		}

		if (coordinate.y - 1 >= 0) {
			addPossibleBoardSquare(board, coordinate.x + 2, coordinate.y - 1);

		}
	}

	if (coordinate.x - 2 >= 0) {
		if (coordinate.y + 1 < 8) {
			addPossibleBoardSquare(board, coordinate.x - 2, coordinate.y + 1);
		}

		if (coordinate.y - 1 >= 0) {
			addPossibleBoardSquare(board, coordinate.x - 2, coordinate.y - 1);
		}
	}
}
