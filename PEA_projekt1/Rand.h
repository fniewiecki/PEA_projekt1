#pragma once
#include "Graph.h"

class Rand
{
private:
    const Graph& graph;
    int N;
    int** macierz;
    int* bestPath;
    int minCost;
    double overallTime;
    int iterations;

public:
    Rand(const Graph& g, int iter = 10000);
    ~Rand();

    int* getPath();
    double getTime() const;
    int getMinCost() const;
};