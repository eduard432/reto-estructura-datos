#include <iostream>
#include "Board.h"

using namespace std;

int main () {
	Board board;
	board.addSquare("Mazmorra 1", 0.8, false);
	board.addMonster("Monstruo 1");
	board.play();

	return 0;
}
