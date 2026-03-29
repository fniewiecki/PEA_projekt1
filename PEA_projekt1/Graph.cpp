#include "Graph.h"
#include <fstream>
#include <iostream>

using namespace std;

Graph::Graph()
{
	N = 0;
	macierz = nullptr;

}

Graph::~Graph()
{
	if (macierz != nullptr)
	{
		for (int i = 0; i < N; i++)
		{
			delete[] macierz[i];
		}
		delete[] macierz;
	}
}

bool Graph::loadFromFile(string filename)
{
    ifstream MyReadFile(filename);
    if (!MyReadFile.is_open())
    {
        cout << "Blad";
        return false;
    }
    MyReadFile >> N;
    cout << "Zadany graf ma: " << N << " wierzcholkow\n";
	macierz = new int* [N];
    for (int i = 0; i < N; i++)
    {
        macierz[i] = new int[N];
    }

    for (int i = 0; i < N; i++)
    {
        string wiersz = "";
        for (int j = 0; j < N; j++)
        {
            MyReadFile >> macierz[i][j];
        }
    }
    MyReadFile.close();
    return true;
}
void Graph::display()
{
    if (macierz == nullptr)
    {
        cout << "Macierz jest pusta";
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << macierz[i][j] << "     ";
        }
        cout << endl;
    }
}
int Graph::getN() const {
    return N;
}
int** Graph::getMacierz() const {
    return macierz;
}
