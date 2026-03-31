#include "Rand.h"
#include <chrono>
#include <cstdlib> 
#include <ctime>   
#include <climits>

using namespace std;

Rand::Rand(const Graph& g, int iter) : graph(g), iterations(iter) {
    N = graph.getN();
    macierz = graph.getMacierz();
    bestPath = new int[N];
    minCost = INT_MAX;
    overallTime = 0.0;
}

Rand::~Rand() {
    delete[] bestPath;
}

int* Rand::getPath() {
    if (N <= 1) return nullptr;

    int* currentPath = new int[N];

    // Inicjalizacja tablicy pocz¹tkowej: 0, 1, 2, ..., N-1
    for (int i = 0; i < N; ++i) {
        currentPath[i] = i;
    }

    // Odpalamy ziarno losowoœci
    srand(time(NULL));

    auto beginTime = chrono::high_resolution_clock::now();

    // Wykonujemy 'k' losowych prób
    for (int k = 0; k < iterations; ++k) {

        // --- RÊCZNE TASOWANIE FISHERA-YATESA ---
        for (int i = N - 1; i > 0; --i) {
            // Losujemy indeks od 0 do i
            int j = rand() % (i + 1);

            // Zamieniamy miejscami (Swap)
            int temp = currentPath[i];
            currentPath[i] = currentPath[j];
            currentPath[j] = temp;
        }
        // --------------------------------------

        int currentCost = 0;

        // Liczymy koszt tej wylosowanej trasy
        for (int i = 0; i < N - 1; ++i) {
            currentCost += macierz[currentPath[i]][currentPath[i + 1]];
        }
        // Bilet powrotny z ostatniego miasta do pierwszego
        currentCost += macierz[currentPath[N - 1]][currentPath[0]];

        // Sprawdzamy, czy wylosowaliœmy nowy rekord
        if (currentCost < minCost) {
            minCost = currentCost;
            for (int i = 0; i < N; ++i) {
                bestPath[i] = currentPath[i];
            }
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    overallTime = chrono::duration<double, std::milli>(endTime - beginTime).count();

    delete[] currentPath;
    return bestPath;
}

double Rand::getTime() const {
    return overallTime;
}

int Rand::getMinCost() const {
    return minCost;
}