#include <iostream>
#include "Vector.h"
#include "Graph.h"

using namespace std;

int main () {
	Graph<int> grafo;

	grafo.addVertex(5);
	grafo.addVertex(3);
	grafo.addVertex(4);
	
	grafo.addEdge(5, 3);


	grafo.print();

	return 0;
}
