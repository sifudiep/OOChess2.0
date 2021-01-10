#include "Pawn.h"

void Pawn::updatePossibleCoordinates(BoardSquare board[8][8]) {
	possibleCoordinates.clear();

	if (owner == Owner::Blue) {
		if (coordinate.y + 1 < 8 && board[coordinate.y + 1][coordinate.x].owner == Owner::None) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x, coordinate.y + 1));
		}

		if (firstMove && board[coordinate.y + 2][coordinate.x].owner == Owner::None) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x, coordinate.y + 2));
		}

		if (board[coordinate.y + 1][coordinate.x + 1].owner == Owner::Red) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x + 1, coordinate.y + 1));
		}

		if (board[coordinate.y + 1][coordinate.x - 1].owner == Owner::Red) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x - 1, coordinate.y + 1));
		}

	}
	else if (owner == Owner::Red) {
		if (coordinate.y - 1 >= 0 && board[coordinate.y - 1][coordinate.x].owner == Owner::None) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x, coordinate.y - 1));
		}

		if (firstMove && board[coordinate.y - 2][coordinate.x].owner == Owner::None) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x, coordinate.y - 2));
		}

		if (board[coordinate.y - 1][coordinate.x + 1].owner == Owner::Blue) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x + 1, coordinate.y - 1));
		}

		if (board[coordinate.y - 1][coordinate.x - 1].owner == Owner::Blue) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x - 1, coordinate.y - 1));
		}
	}
}
