#pragma once
#include "Graph.h"

class BruteForce
{
private:
    const Graph& graph;   
    int* bestPath;        
    int minCost;           

    void search(int currentCity, int visitedCount, int currentCost, int* currentPath, bool* visited);

public:
    BruteForce(const Graph& g);
    ~BruteForce();

    int* FindPath();
    int getMinCost() const;
};