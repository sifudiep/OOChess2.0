#pragma once
#include "Coordinate.h"
#include "Piece.h"
#include "Owner.h"

struct Move {
	Move(char c_symbol, Coordinate c_start, Coordinate c_end, Owner c_owner) {
		symbol = c_symbol;
		start = c_start;
		end = c_end;
		owner = c_owner;
	}

	char symbol;
	Coordinate start;
	Coordinate end;
	Owner owner;
};
