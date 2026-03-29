#pragma once
#include "Graph.h"
class RNN
{
private:
	const Graph& graph;
	int N;
	int** macierz;
	int* bestPath;
	double time;
	int minCost;

public:
	RNN(const Graph& g);
	~RNN();

	int* getPath();
	double getTime() const;
	int getMinCost() const;

};

