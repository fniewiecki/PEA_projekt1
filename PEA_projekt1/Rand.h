#pragma once
#include "Graph.h"

class Rand
{
private:
    const Graph& graph;
    int* bestPath;
    int minCost;
    int** macierz;
    int N;
    double overallTime;

public:
	Rand(const Graph& g);
	~Rand();

	int * FindPath();
};

