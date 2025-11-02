#include <iostream>
#include "LinkedList.h"

using namespace std;

int main () {
	LinkedList<int> lista;
	lista.pushBack(1);
	lista.pushBack(2);
	lista.pushBack(3);

	lista.print();

	lista[0] = 12;

	cout << lista[0] << endl;


	lista.print();


	return 0;
}
