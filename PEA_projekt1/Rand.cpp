#include "Rand.h"
#include <iostream>
#include "Rand.h"
using namespace std;

Rand::Rand(const Graph& g) : graph(g) {

}
Rand::~Rand() {
	
}
int* Rand::FindPath() {
    int** macierz = graph.getMacierz();
    int N = graph.getN();
    int* rozw = new int[N];

    if (macierz == nullptr) return rozw;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << macierz[i][j] << " ";
        cout << endl;
    }
        
    return rozw;
}