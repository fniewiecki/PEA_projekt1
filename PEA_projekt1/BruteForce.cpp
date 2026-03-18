#include "BruteForce.h"
#include <iostream>
#include <climits> 

using namespace std;

BruteForce::BruteForce(const Graph& g) : graph(g) {
    int N = graph.getN();
    bestPath = new int[N];
    minCost = INT_MAX;
}

BruteForce::~BruteForce() {
    delete[] bestPath;
}

// Główna funkcja rekurencyjna 
void BruteForce::search(int currentCity, int visitedCount, int currentCost, int* currentPath, bool* visited) {
    int N = graph.getN();
    int** macierz = graph.getMacierz();

    if (visitedCount == N) {
        int finalCost = currentCost + macierz[currentCity][0];

        if (finalCost < minCost) {
            minCost = finalCost;
            for (int i = 0; i < N; ++i) {
                bestPath[i] = currentPath[i];
            }
        }
        return;
    }

    for (int i = 1; i < N; ++i) {
        if (!visited[i]) {

            visited[i] = true;
            currentPath[visitedCount] = i;

            search(i, visitedCount + 1, currentCost + macierz[currentCity][i], currentPath, visited);

            visited[i] = false;
        }
    }
}

// Metoda uruchamiająca algorytm
int* BruteForce::FindPath() {
    int N = graph.getN();
    if (N == 0) return nullptr;

    int* currentPath = new int[N];
    bool* visited = new bool[N];

    for (int i = 0; i < N; ++i) {
        visited[i] = false;
        currentPath[i] = -1;
    }

    currentPath[0] = 0;
    visited[0] = true;
    minCost = INT_MAX; 

    search(0, 1, 0, currentPath, visited);

    delete[] currentPath;
    delete[] visited;

    return bestPath;
}

int BruteForce::getMinCost() const {
    return minCost;
}