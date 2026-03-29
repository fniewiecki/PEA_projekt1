#include "RNN.h"
#include <chrono>
using namespace std;

RNN::RNN(const Graph& g) : graph(g) {
	N = g.getN();
	macierz = g.getMacierz();
	bestPath = new int[N];
	time = 0.0;
	minCost = INT_MAX;
}
RNN::~RNN() {
	delete[] bestPath;
}

int* RNN::getPath() {
	bool* visited = new bool[N];
	int* currentPath = new int[N];


	auto beginTime = chrono::high_resolution_clock::now();

	for (int startCity = 0; startCity < N; startCity++)
	{		
		for (int i = 0; i < N; ++i)
		{
			visited[i] = false;
		}

		int currentCity = startCity;
		currentPath[0] = currentCity;
		visited[currentCity] = true;
		int currentCost = 0;

		for (int step = 1; step  < N; step ++)
		{
			int nearestCity = -1;
			int shortestDistance = INT_MAX;

			for (int i = 0; i < N; i++)
			{
				if (!visited[i] && macierz[currentCity][i] < shortestDistance) {
					nearestCity = i;
					shortestDistance = macierz[currentCity][i];
				}
			}

			visited[nearestCity] = true;
			currentPath[step] = nearestCity;
			currentCost += shortestDistance;
			currentCity = nearestCity;
		}
		currentCost += macierz[currentCity][startCity];
		if (currentCost < minCost)
		{
			minCost = currentCost;
			for (int i = 0; i < N; i++)
			{
				bestPath[i] = currentPath[i];
			}
		}
	}

	auto endTime = chrono::high_resolution_clock::now();
	time = chrono::duration<double, std::milli>(endTime - beginTime).count();
	delete[] visited;
	delete[] currentPath;

	return bestPath;
}
double RNN::getTime() const {
	return time;
}
int RNN::getMinCost() const {
	return minCost;
}