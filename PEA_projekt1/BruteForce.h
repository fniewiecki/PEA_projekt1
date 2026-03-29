#pragma once
#include "Graph.h"

class BruteForce
{
private:
    const Graph& graph;   
    int* bestPath;        
    int minCost;
    int** macierz;
    int N;
	double overallTime;


public:
    BruteForce(const Graph& g);
    ~BruteForce();

    void swapElements(int& a, int& b);
    void reverseArray(int* array, int start, int end);
    bool nextPermutation(int* array, int length);
    int* FindPath();
    int getMinCost() const;
	double getOverallTime() const;
};