#pragma once
struct Coordinate {
	Coordinate(int horizontal = 0, int vertical = 0) {
		x = horizontal;
		y = vertical;
	}

	int x, y;
};
