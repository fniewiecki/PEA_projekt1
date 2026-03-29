#include "BruteForce.h"
#include <climits>
#include <chrono>

using namespace std;

BruteForce::BruteForce(const Graph& g) : graph(g) {

    N = graph.getN();
    macierz = graph.getMacierz();

    bestPath = new int[N];
    minCost = INT_MAX;
	overallTime = 0.0;
}

BruteForce::~BruteForce() {
    delete[] bestPath;
}

//Zamiana elementów
void BruteForce::swapElements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Odwracanie fragmentu tablicy 
void BruteForce::reverseArray(int* array, int start, int end) {
    while (start < end) {
        swapElements(array[start], array[end]);
        start++;
        end--;
    }
}

// Jeśli jest możliwa to wyliczanie nowej permutacji
bool BruteForce::nextPermutation(int* array, int length) {

    int k = -1;
    for (int i = 0; i < length - 1; ++i) {
        if (array[i] < array[i + 1]) {
            k = i;
        }
    }

    if (k == -1) return false;

    int l = -1;
    for (int i = k + 1; i < length; ++i) {
        if (array[k] < array[i]) {
            l = i;
        }
    }

    swapElements(array[k], array[l]);

    reverseArray(array, k + 1, length - 1);

    return true; 
}

// Główna funkcja algorytmu
int* BruteForce::FindPath() {
    int N = graph.getN();
    if (N <= 1) return nullptr;

    int* currentPath = new int[N];
    minCost = INT_MAX;

    // Inicjalizacja pierwszej, bazowej trasy 
    for (int i = 0; i < N; ++i) {
        currentPath[i] = i;
    }

    // ITERACYJNE PRZESZUKIWANIE ZUPEŁNE
	auto beginTime = chrono::high_resolution_clock::now();
    do {
        int currentCost = 0;

        for (int i = 0; i < N - 1; ++i) {
            currentCost += macierz[currentPath[i]][currentPath[i + 1]];
        }

        currentCost += macierz[currentPath[N - 1]][currentPath[0]];

        if (currentCost < minCost) {
            minCost = currentCost;

            for (int i = 0; i < N; ++i) {
                bestPath[i] = currentPath[i];
            }
        }


    } while (nextPermutation(currentPath, N));
	auto endTime = chrono::high_resolution_clock::now();

	overallTime = chrono::duration<double, std::milli>(endTime - beginTime).count();

    delete[] currentPath;
    return bestPath;      
}

int BruteForce::getMinCost() const {
    return minCost;
}
double BruteForce::getOverallTime() const {
    return overallTime;
}