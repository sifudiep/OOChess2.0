#include "Piece.h"

Piece::Piece(Coordinate c_coordinate, Owner c_owner, char c_symbol) {
	coordinate = c_coordinate;
	owner = c_owner;
	symbol = c_symbol;
	firstMove = true;
}

bool Piece::addPossibleBoardSquare(BoardSquare board[8][8], int x, int y) {
	if (board[y][x].owner != owner) {
		possibleCoordinates.emplace_back(Coordinate(x, y));

		if (board[y][x].owner != Owner::None && board[y][x].owner != owner)
			return true;

		return false;
	}
	return true;
}