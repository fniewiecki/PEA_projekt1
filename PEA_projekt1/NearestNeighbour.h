#pragma once
#include "Graph.h"
class NearestNeighbour{
	private: 
		const Graph& graph;
		int N;
		int** macierz;
		int* bestPath;
		int minCost;
		double overallTime;

	public:
		NearestNeighbour(const Graph& graph);
		~NearestNeighbour();

		int getMinCost() const; 
		int* getPath();
		double getTime() const;
		



};

