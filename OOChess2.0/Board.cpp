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
start:

	std::string turnText = (turn == Owner::Blue) ? "BLUE" : "RED";
	int textColor = turn == Owner::Blue ? 9 : 12;

	std::string input;

	std::cout << "It's ";
	SetConsoleTextAttribute(h_console, textColor);
	std::cout << turnText;
	SetConsoleTextAttribute(h_console, 7);
	std::cout << "'s turn to make a move!: ";

	std::cin >> input;

	char symbol = input[0];


	if (input.size() == 2) {
		if (input[0] == 'C') {
			if (input[1] == 'K') {
				if (castle(turn, true)) {
					turn = turn == Owner::Blue ? Owner::Red : Owner::Blue;
					goto start;
				}
			}

			if (input[1] == 'Q') {
				if (castle(turn, false)) {
					turn = turn == Owner::Blue ? Owner::Red : Owner::Blue;
					goto start;
				}
			}
			
			std::cout << "Castling failed...";
			goto start;
		}
		std::cout << "Castling failed...";
		goto start;
	}



	if (input.size() == 5) {
		Coordinate start(std::tolower(input[1]) - 97, (int)input[2] - 49);
		Coordinate destination(std::tolower(input[3]) - 97, (int)input[4] - 49);
		
		if (std::isalpha(input[0]) && std::isalpha(input[1]) && std::isalpha(input[3]) ) {
			if (start.y >= 0 && start.y < 8 && destination.y >= 0 && destination.y < 8) {
				if (!kingBecomesChecked(symbol, start, destination)) {
					
					if (movePiece(symbol, start, destination, false)) {
						turn = turn == Owner::Blue ? Owner::Red : Owner::Blue;
						clearBoard();
						drawBoard();
						
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



bool Board::movePiece(char symbol, Coordinate start, Coordinate destination, bool simulate) {
	for (size_t i = 0; i < allPieces.size(); i++) {
		if (allPieces[i]->owner == turn) {
			if (allPieces[i]->symbol == symbol) {
				if (allPieces[i]->coordinate.x == start.x && allPieces[i]->coordinate.y == start.y) {
					for (size_t j = 0; j < allPieces[i]->possibleCoordinates.size(); j++) {
						if (allPieces[i]->possibleCoordinates[j].x == destination.x
							&& allPieces[i]->possibleCoordinates[j].y == destination.y) {


							if (simulate == false) {
								checkEnPassantPawns(turn);
								tryCaptureEnpassant(symbol, start, destination);
								deleteSquare(destination);
								if (allPieces[i]->firstMove) {
									allPieces[i]->firstMove = false;
									allPieces[i]->justMadeFirstMove = true;
								}
							}
							
							allPieces[i]->formerCoordinate = start;
							allPieces[i]->coordinate = destination;

							if (simulate == false) {
								clearBoard();
							}
							else {
								syncAllPiecesToBoard();
							}

							updateAllPossibleCoordinates();

							if (simulate == false) {
								drawBoard();
								clearEmptyPieces();
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
int Board::findPieceIndex(char symbol, int x, int y) {
	for (size_t i = 0; i < allPieces.size(); i++) {
		if (allPieces[i]->symbol == symbol) {
			if (allPieces[i]->coordinate.x == x && allPieces[i]->coordinate.y == y) {
				return i;
			}
		}
	}

	return -1;
}
int Board::kingIsUnderCheck(Owner owner) {
	Piece* king = allPieces[getKingIndex(owner)];
	
	for (size_t i = 0; i < allPieces.size(); i++) {
		for (size_t j = 0; j < allPieces[i]->possibleCoordinates.size(); j++) {
			if (allPieces[i]->owner != owner) {
				if (allPieces[i]->possibleCoordinates[j].x == king->coordinate.x && allPieces[i]->possibleCoordinates[j].y == king->coordinate.y) {
					return true;
				}
			}
		}
	}

	return false;
}
bool Board::castle(Owner owner, bool kingSide) {
	Piece* king = allPieces[getKingIndex(owner)];
	if (king->firstMove && kingIsUnderCheck(owner) == false) {
		Coordinate kingStartCoordinate = king->coordinate;
		
		int row = owner == Owner::Blue ? 0 : 7;
		int column = kingSide == true ? 7 : 0;
		
		int rookIndex = findPieceIndex('R', column, row);
		if (rookIndex == -1) return false;
		Piece* rook = allPieces[rookIndex];

		if (!rook->firstMove) return false;

		if (kingSide) {
			for (int i = 1; i < 3; i++) {
				if (board[kingStartCoordinate.y][kingStartCoordinate.x + i].owner == Owner::None) {
					if (kingBecomesChecked('K', king->coordinate, Coordinate(kingStartCoordinate.x + i, kingStartCoordinate.y))) {
						king->coordinate = kingStartCoordinate;
						updateAllPossibleCoordinates();
						return false;
					}
				}
				else {
					king->coordinate = kingStartCoordinate;
					updateAllPossibleCoordinates();
					return false;
				}
			}

			rook->coordinate = Coordinate(kingStartCoordinate.x + 1, kingStartCoordinate.y);
			king->coordinate = Coordinate(kingStartCoordinate.x + 2, kingStartCoordinate.y);
			clearBoard();
			updateAllPossibleCoordinates();
			drawBoard();
			
			return true;
		} else {
			for (int i = 1; i < 4; i++) {
				if (board[kingStartCoordinate.y][kingStartCoordinate.x - i].owner == Owner::None) {
					if (kingBecomesChecked('K', king->coordinate, Coordinate(kingStartCoordinate.x - i, kingStartCoordinate.y))) {
						king->coordinate = kingStartCoordinate;
						king->updatePossibleCoordinates(board, allPieces);
						return false;
					}
				}
				else {
					king->coordinate = kingStartCoordinate;
					king->updatePossibleCoordinates(board, allPieces);
					return false;
				}
			}

			rook->coordinate = Coordinate(kingStartCoordinate.x - 1, kingStartCoordinate.y);
			king->coordinate = Coordinate(kingStartCoordinate.x - 2, kingStartCoordinate.y);
			
			clearBoard();
			updateAllPossibleCoordinates();
			drawBoard();
			return true;
		}
	}
	return false;
}

void Board::tryCaptureEnpassant(char symbol, Coordinate start, Coordinate destination) {
	if (symbol != 'P') return;
	if (start.x == destination.x) return;
	
	if (board[destination.y][destination.x].owner == Owner::None) {
		if (turn == Owner::Blue) {
			deleteSquare(Coordinate(destination.x, destination.y-1));
		} else {
			deleteSquare(Coordinate(destination.x, destination.y + 1));
		}
	}
	
}


bool Board::deleteSquare(Coordinate destination) {
	for (size_t i = 0; i < allPieces.size(); i++) {
		if (allPieces[i]->coordinate.x == destination.x && allPieces[i]->coordinate.y == destination.y) {
			allPieces[i]->symbol = ' ';
			allPieces[i]->owner = Owner::None;
			allPieces[i]->possibleCoordinates.clear();
			return true;
		}
	}

	return false;
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
		if (allPieces[i]->symbol == symbol 
			&& allPieces[i]->coordinate.x == coordinate.x 
			&& allPieces[i]->coordinate.y == coordinate.y
			&& allPieces[i]->owner == turn) {
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

	return ERROR;
}

void Board::clearEmptyPieces() {
	for (size_t i = 0; i < allPieces.size(); i++) {
		if (allPieces[i]->symbol == ' ' && allPieces[i]->owner == Owner::None) {
			allPieces.erase(allPieces.begin() + i);
		}
	}
}


void Board::updateAllPossibleCoordinates() {
	for (size_t i = 0; i < allPieces.size(); i++) {
		allPieces[i]->updatePossibleCoordinates(board, allPieces);
	}
}

void Board::checkEnPassantPawns(Owner owner) {
	for (size_t i = 0; i < allPieces.size(); i++) {
		if (allPieces[i]->symbol == 'P' && allPieces[i]->owner == owner) {
			if (allPieces[i]->justMadeFirstMove) {
				allPieces[i]->justMadeFirstMove = false;
			}
		}
	} 
}


void Board::drawBoard() {
	bool lightSquare = true;
	for (int i = 7; i >= 0; i--) {
		std::cout << '|' << i + 1 << "| ";
		for (int j = 0; j < 8; j++) {
			if (lightSquare) {
				SetConsoleTextAttribute(h_console, 7);
			} else {
				SetConsoleTextAttribute(h_console, 2);
			}

			std::cout << '[';

			
			if (board[i][j].owner == Owner::Blue) {
				SetConsoleTextAttribute(h_console, 9);
			} else if (board[i][j].owner == Owner::Red) {
				SetConsoleTextAttribute(h_console, 12);
			}
			
			std::cout << board[i][j].symbol;
			
			if (lightSquare) {
				SetConsoleTextAttribute(h_console, 7);
				if (j != 7) {
					lightSquare = lightSquare == true ? false : true;
				}
			}
			else {
				SetConsoleTextAttribute(h_console, 2);
				if (j != 7) {
					lightSquare = lightSquare == true ? false : true;
				}
			}

			std::cout << ']';

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
	std::cout << "syncing...";
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
