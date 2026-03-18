#pragma once
#include <string>
using namespace std;
class Graph
{
private:
	int N;
	int** macierz;

public:
	Graph();
	~Graph();
	
	bool loadFromFile(string filename);
	void display();
	int getN() const;
	int** getMacierz() const;
	


};


