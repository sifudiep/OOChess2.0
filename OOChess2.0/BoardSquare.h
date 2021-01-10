#pragma once
#include "Owner.h"

struct BoardSquare {
	BoardSquare(char c_symbol = ' ', Owner c_owner = Owner::None) {
		symbol = c_symbol;
		owner = c_owner;
	}

	char symbol;
	Owner owner;
};
