#include "NearestNeighbour.h"
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

NearestNeighbour::NearestNeighbour(const Graph& g) : graph(g) {
    N = graph.getN();
    macierz = graph.getMacierz();
    bestPath = new int[N];
    overallTime = 0.0;
}

NearestNeighbour::~NearestNeighbour() {
    delete[] bestPath;
}

int* NearestNeighbour::getPath() {
    if (N <= 1) return nullptr;

    bool* visited = new bool[N];
    minCost = 0;

    auto beginTime = chrono::high_resolution_clock::now();

    // Reset listy odwiedzin
    for (int i = 0; i < N; ++i) {
        visited[i] = false;
    }
    srand(time(NULL));
	int startCity = rand() % N;
    int currentCity = startCity;
    bestPath[0] = currentCity;
    visited[currentCity] = true;

    // Budujemy trasę zachłannie
    for (int step = 1; step < N; ++step) {
        int nearestCity = -1;
        int shortestDistance = INT_MAX;

        for (int i = 0; i < N; ++i) {
            if (!visited[i] && macierz[currentCity][i] < shortestDistance) {
                nearestCity = i;
                shortestDistance = macierz[currentCity][i];
            }
        }

        visited[nearestCity] = true;
        bestPath[step] = nearestCity;
        minCost += shortestDistance;
        currentCity = nearestCity;
    }

    // Dopisanie kosztu powrotu do 1 miasta 
    minCost += macierz[currentCity][startCity];

    auto endTime = chrono::high_resolution_clock::now();
    overallTime = chrono::duration<double, std::milli>(endTime - beginTime).count();

    delete[] visited;
    return bestPath;
}

double NearestNeighbour::getTime() const { return overallTime; }
int NearestNeighbour::getMinCost() const { return minCost; }