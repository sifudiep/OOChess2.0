#include "Board.h"
#include <iostream>
#include <string>

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

Board::Board() {
	turn = Owner::Blue;
	resetBoardPieces();
	clearBoard();
	updateAllPossibleCoordinates();
	drawBoard();
}

void Board::gameInput() {
	std::string turnText = (turn == Owner::Blue) ? "BLUE" : "RED";
	int textColor = turn == Owner::Blue ? 9 : 12;

	start:

	std::string input;

	std::cout << "It's ";
	SetConsoleTextAttribute(h_console, textColor);
	std::cout << turnText;
	SetConsoleTextAttribute(h_console, 7);
	std::cout << "'s turn to make a move!: ";

	std::cin >> input;

	char symbol = input[0];
	Coordinate start(std::tolower(input[1]) - 97, (int)input[2] - 49);
	Coordinate destination(std::tolower(input[3]) - 97, (int)input[4] - 49);

	if (input.size() == 5) {
		if (std::isalpha(input[0]) && std::isalpha(input[1]) && std::isalpha(input[3]) ) {
			if (start.y >= 0 && start.y < 8 && destination.y >= 0 && destination.y < 8) {
				if (!kingBecomesChecked(symbol, start, destination)) {
					if (movePiece(symbol, start, destination, false)) {
						turn = turn == Owner::Blue ? Owner::Red : Owner::Blue;
					} else {
						std::cout << std::endl << "The piece cannot move to that square" << std::endl;
						goto start;
					}
					
				} else {
					std::cout << std::endl << "Move is not legal, King is going to be in check..." << std::endl;
					goto start;
				}
			} else {
				std::cout << std::endl << "Somethings wrong with the numbers in the input..." << std::endl;
				goto start;
			}
		} else {
			std::cout << std::endl << "Something's wrong with the letters in the input..." << std::endl;
			std::cout << input[0] << input[1] << input[3];
			goto start;
		}
	} else {
		std::cout << std::endl << "Input must be 5 symbols long" << std::endl;
		goto start;
	}

}

void Board::captureSquare(Coordinate destination) {
	for (size_t i = 0; i < allPieces.size(); i++) {
		if (allPieces[i]->coordinate.x == destination.x && allPieces[i]->coordinate.y == destination.y) {
			allPieces.erase(allPieces.begin() + i);
			break;
		}
	}
}
bool Board::kingBecomesChecked(char symbol, Coordinate start, Coordinate destination) {	
	if (movePiece(symbol, start, destination, true)) {
		for (size_t i = 0; i < allPieces.size(); i++ ) {
			for (size_t j = 0; j < allPieces[i]->possibleCoordinates.size(); j++) {
				Owner opponent = turn == Owner::Blue ? Owner::Red : Owner::Blue;

				if (allPieces[i]->owner == opponent) {
					if (allPieces[i]->possibleCoordinates[j].x == allPieces[getKingIndex(turn)]->coordinate.x &&
						allPieces[i]->possibleCoordinates[j].y == allPieces[getKingIndex(turn)]->coordinate.y) {
						moveBack(symbol, destination);
						return true;
					}
				}
			}
		}
	}

	moveBack(symbol, destination);
	return false;
}

void Board::moveBack(char symbol, Coordinate coordinate) {
	for (size_t i = 0; i < allPieces.size(); i++) {
		if (allPieces[i]->symbol == symbol && allPieces[i]->coordinate.x == coordinate.x && allPieces[i]->coordinate.y == coordinate.y) {
			allPieces[i]->coordinate = allPieces[i]->formerCoordinate;
			syncAllPiecesToBoard();
			updateAllPossibleCoordinates();
		}
	}
}

int Board::getKingIndex(Owner owner) {
	if (owner == Owner::Blue) {
		return allPieces.size() - 2;
	} else if (owner == Owner::Red) {
		return allPieces.size() - 1;
	}
}

bool Board::movePiece(char symbol, Coordinate start, Coordinate destination, bool simulate) {	
	for (size_t i = 0; i < allPieces.size(); i++) {
		if (allPieces[i]->owner == turn) {
			std::cout << "1";
			if (allPieces[i]->symbol == symbol) {
				std::cout << "2";

				if (allPieces[i]->coordinate.x == start.x && allPieces[i]->coordinate.y == start.y) {
					std::cout << "3";

					for (size_t j = 0; j < allPieces[i]->possibleCoordinates.size(); j++) {
						if (allPieces[i]->possibleCoordinates[j].x == destination.x 
							&& allPieces[i]->possibleCoordinates[j].y == destination.y) {
							std::cout << "4";

							if (simulate == false) {
								captureSquare(destination);
								if (allPieces[i]->firstMove) allPieces[i]->firstMove = false;
							}

							allPieces[i]->formerCoordinate = start;
							allPieces[i]->coordinate = destination;
							if (simulate == false ) {
								clearBoard();
							} else {
								syncAllPiecesToBoard();
							}
							
							updateAllPossibleCoordinates();
							
							if (simulate == false) {
								drawBoard();
							}
							
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

void Board::updateAllPossibleCoordinates() {
	for (size_t i = 0; i < allPieces.size(); i++) {
		allPieces[i]->updatePossibleCoordinates(board);
	}
}
void Board::drawBoard() {
	for (int i = 7; i >= 0; i--) {
		std::cout << '|' << i + 1 << "| ";
		for (int j = 0; j < 8; j++) {
			if (board[i][j].owner == Owner::Blue) {
				SetConsoleTextAttribute(h_console, 9);
			}

			if (board[i][j].owner == Owner::Red) {
				SetConsoleTextAttribute(h_console, 12);
			}

			std::cout << '[' << board[i][j].symbol << ']';
			SetConsoleTextAttribute(h_console, 7);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "    |a||b||c||d||e||f||g||h|" << std::endl;
}
void Board::clearBoard() {
	system("cls");
	syncAllPiecesToBoard();
}

void Board::syncAllPiecesToBoard() {
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = BoardSquare(' ', Owner::None);
		}
	}
	
	for (size_t i = 0; i < allPieces.size(); i++) {
		board[allPieces[i]->coordinate.y][allPieces[i]->coordinate.x] = BoardSquare(allPieces[i]->symbol, allPieces[i]->owner);
	}
}

void Board::resetBoardPieces() {
	allPieces.clear();

	// Spawning Pawns
	for (int i = 0; i < 8; i++) {
		allPieces.emplace_back(new Pawn(Coordinate(i, 1), Owner::Blue, 'P'));
		allPieces.emplace_back(new Pawn(Coordinate(i, 6), Owner::Red, 'P'));
	}

	// Spawning Rooks
	allPieces.emplace_back(new Rook(Coordinate(0, 0), Owner::Blue, 'R'));
	allPieces.emplace_back(new Rook(Coordinate(7, 0), Owner::Blue, 'R'));
	allPieces.emplace_back(new Rook(Coordinate(0, 7), Owner::Red, 'R'));
	allPieces.emplace_back(new Rook(Coordinate(7, 7), Owner::Red, 'R'));

	//// Spawning Knights
	allPieces.emplace_back(new Knight(Coordinate(1, 0), Owner::Blue, 'N'));
	allPieces.emplace_back(new Knight(Coordinate(6, 0), Owner::Blue, 'N'));
	allPieces.emplace_back(new Knight(Coordinate(1, 7), Owner::Red, 'N'));
	allPieces.emplace_back(new Knight(Coordinate(6, 7), Owner::Red, 'N'));

	// Spawning Bishops
	allPieces.emplace_back(new Bishop(Coordinate(2, 0), Owner::Blue, 'B'));
	allPieces.emplace_back(new Bishop(Coordinate(5, 0), Owner::Blue, 'B'));
	allPieces.emplace_back(new Bishop(Coordinate(2, 7), Owner::Red, 'B'));
	allPieces.emplace_back(new Bishop(Coordinate(5, 7), Owner::Red, 'B'));

	//// Spawning Queens
	allPieces.emplace_back(new Queen(Coordinate(3, 0), Owner::Blue, 'Q'));
	allPieces.emplace_back(new Queen(Coordinate(3, 7), Owner::Red, 'Q'));

	//// Spawning Kings
	allPieces.emplace_back(new King(Coordinate(4, 0), Owner::Blue, 'K'));
	allPieces.emplace_back(new King(Coordinate(4, 7), Owner::Red, 'K'));

}
