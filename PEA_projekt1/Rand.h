#pragma once
#include "Graph.h"

class Rand
{
private:
	const Graph& graph;
public:
	Rand(const Graph& g);
	~Rand();

	int * FindPath();
};

