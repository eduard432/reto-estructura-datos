#include <iostream>
#include "Board.h"

using namespace std;

int main () {
	Board board;
	board.addSquare("Mazmorra 1", 0.8, false);
	board.play();

	return 0;
}
