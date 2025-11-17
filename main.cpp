#include <iostream>
#include "Board.h"

using namespace std;

int main () {
	Board board;
	board.addSquare("Mazmorra 1", 0.8, false);
	board.addMonster("Monstruo 1");
	board.addMonster("Monstruo 2");
	board.addMonster("Monstruo 3");
	board.play();

	board.combat();

	return 0;
}
