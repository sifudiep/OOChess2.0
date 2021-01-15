#include "Pawn.h"

#include <iostream>


int Pawn::findPieceIndex(std::vector<Piece*> allPieces, int x, int y) {
	for (size_t i = 0; i < allPieces.size(); i++) {
		if (allPieces[i]->coordinate.x == x && allPieces[i]->coordinate.y == y) {
			if (allPieces[i]->symbol == 'P') {
				return i;
			}
			
			return -1;
		}
	}

	return -1;
}

void Pawn::updatePossibleCoordinates(BoardSquare board[8][8], std::vector<Piece*> &allPieces) {
	possibleCoordinates.clear();

	if (owner == Owner::Blue) {
		if (coordinate.y + 1 < 8 && board[coordinate.y + 1][coordinate.x].owner == Owner::None) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x, coordinate.y + 1));

			if (firstMove && board[coordinate.y + 2][coordinate.x].owner == Owner::None) {
				possibleCoordinates.emplace_back(Coordinate(coordinate.x, coordinate.y + 2));
			}
		}

		if (board[coordinate.y + 1][coordinate.x + 1].owner == Owner::Red) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x + 1, coordinate.y + 1));
		}

		if (board[coordinate.y + 1][coordinate.x - 1].owner == Owner::Red) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x - 1, coordinate.y + 1));
		}

		if (board[coordinate.y][coordinate.x + 1].owner == Owner::Red) {
			int enPassantIndex = findPieceIndex(allPieces, coordinate.x + 1, coordinate.y);
			
			if (enPassantIndex != -1) {
				if (allPieces[enPassantIndex]->coordinate.y == 4) {
					if (allPieces[enPassantIndex]->justMadeFirstMove && allPieces[enPassantIndex]->symbol == 'P') {
						possibleCoordinates.emplace_back(Coordinate(coordinate.x + 1, coordinate.y + 1));
					}
				}
			}
		}

		if (board[coordinate.y][coordinate.x - 1].owner == Owner::Red) {
			int enPassantIndex = findPieceIndex(allPieces, coordinate.x - 1, coordinate.y);

			if (enPassantIndex != -1) {
				if (allPieces[enPassantIndex]->coordinate.y == 4) {
					if (allPieces[enPassantIndex]->justMadeFirstMove && allPieces[enPassantIndex]->symbol == 'P') {
						possibleCoordinates.emplace_back(Coordinate(coordinate.x - 1, coordinate.y + 1));
					}
				}
			}
		}
	}
	else if (owner == Owner::Red) {
		if (coordinate.y - 1 >= 0 && board[coordinate.y - 1][coordinate.x].owner == Owner::None) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x, coordinate.y - 1));

			if (firstMove && board[coordinate.y - 2][coordinate.x].owner == Owner::None) {
				possibleCoordinates.emplace_back(Coordinate(coordinate.x, coordinate.y - 2));
			}
		}

		if (board[coordinate.y - 1][coordinate.x + 1].owner == Owner::Blue) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x + 1, coordinate.y - 1));
		}

		if (board[coordinate.y - 1][coordinate.x - 1].owner == Owner::Blue) {
			possibleCoordinates.emplace_back(Coordinate(coordinate.x - 1, coordinate.y - 1));
		}

		if (board[coordinate.y][coordinate.x + 1].owner == Owner::Blue) {
			int enPassantIndex = findPieceIndex(allPieces, coordinate.x + 1, coordinate.y);

			if (enPassantIndex != -1) {
				if (allPieces[enPassantIndex]->coordinate.y == 4) {
					if (allPieces[enPassantIndex]->justMadeFirstMove && allPieces[enPassantIndex]->symbol == 'P') {
						possibleCoordinates.emplace_back(Coordinate(coordinate.x + 1, coordinate.y + 1));
					}
				}
			}
		}

		if (board[coordinate.y][coordinate.x - 1].owner == Owner::Blue) {
			int enPassantIndex = findPieceIndex(allPieces, coordinate.x - 1, coordinate.y);

			if (enPassantIndex != -1) {
				if (allPieces[enPassantIndex]->coordinate.y == 4) {
					if (allPieces[enPassantIndex]->justMadeFirstMove && allPieces[enPassantIndex]->symbol == 'P') {
						possibleCoordinates.emplace_back(Coordinate(coordinate.x - 1, coordinate.y + 1));
					}
				}
			}
		}
	}
}
