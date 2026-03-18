#include <iostream>
#include "Graph.h"
#include "Rand.h"
#include "BruteForce.h"
using namespace std;


int main()
{   
	Graph graph;
	graph.loadFromFile("test.txt");

    BruteForce bf(graph);

    int* bestRoute = bf.FindPath();
    int N = graph.getN();

    cout << "Najmniejszy koszt: " << bf.getMinCost() << endl;
    cout << "Najlepsza trasa: ";
    for (int i = 0; i < N; i++) {
        cout << bestRoute[i] << " -> ";
    }
    cout << bestRoute[0] << endl; // Powrót na start

	return 0;
}
