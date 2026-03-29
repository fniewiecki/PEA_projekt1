#include <iostream>
#include <string>
#include "Graph.h"
#include "BruteForce.h"
#include "NearestNeighbour.h"
#include "RNN.h"

using namespace std;

void trybPokazowy() {
    string filename;
    cout << "\nPodaj nazwe pliku (wcisnij ENTER, aby uzyc domyslnego 'test.txt'): \n";
    getline(cin, filename);

    if (filename.empty()) {
        filename = "test.txt";
    }

    Graph graph;

    if (!graph.loadFromFile(filename)) {
        cout << "Powrot do menu." << endl;
        return;
    }

    cout << "\n--- Wczytane dane ---" << endl;
    graph.display();

    while (true) {
        cout << "\nWybierz algorytm do uruchomienia:" << endl;
        cout << "1. Brute Force" << endl;
        cout << "2. Nearest Neighbour" << endl;
		cout << "3. Repetetive Nearest Neghbour" << endl;
        cout << "0. Powrot" << endl;
        cout << "Wybor: ";

        string algChoiceStr;
        getline(cin, algChoiceStr);
        if (algChoiceStr.empty()) continue;
        char algChoice = algChoiceStr[0];

        if (algChoice == '1') {
            BruteForce bf(graph);

            int* bestRoute = bf.FindPath();
            int N = graph.getN();

            if (bestRoute != nullptr) {
                cout << "\nWynik Brute Force:" << endl;
                cout << "Najmniejszy koszt: " << bf.getMinCost() << endl;
				cout << "Czas wykonania: " << bf.getOverallTime() << " milisekund" << endl;
                cout << "Najlepsza trasa: ";
                for (int i = 0; i < N; i++) {
                    cout << bestRoute[i] << " -> ";
                }
                cout << bestRoute[0] << endl;
            }
        }
        else if (algChoice == '2') {
            NearestNeighbour nn(graph);
            int N = graph.getN();
            int* bestRoute = nn.getPath();

            if (bestRoute != nullptr) {
                cout << "\nWynik Nearest Neighbour:" << endl;
                cout << "Najmniejszy koszt: " << nn.getMinCost() << endl;
                cout << "Czas wykonania: " << nn.getTime() << " milisekund" << endl;
                cout << "Najlepsza trasa: ";
                for (int i = 0; i < N; i++) {
                    cout << bestRoute[i] << " -> ";
                }
                cout << bestRoute[0] << endl;
            }
        }
        else if (algChoice == '3')
        {
            RNN rnn(graph);
            int N = graph.getN();
            int* bestRoute = rnn.getPath();

            if (bestRoute != nullptr) {
                cout << "\nWynik Repetetive Nearest Neighbour:" << endl;
                cout << "Najmniejszy koszt: " << rnn.getMinCost() << endl;
                cout << "Czas wykonania: " << rnn.getTime() << " milisekund" << endl;
                cout << "Najlepsza trasa: ";
                for (int i = 0; i < N; i++) {
                    cout << bestRoute[i] << " -> ";
                }
                cout << bestRoute[0] << endl;
            }
        }
        else if (algChoice == '0') {
            break;
        }
        else {
            cout << "Nieznana opcja." << endl;
        }
    }
}

void trybBadan() {
    cout << "\n--- TRYB BADAN ---" << endl;
    cout << "TO DO" << endl;
    cout << "Wcisnij ENTER, aby wrocic." << endl;
    string temp;
    getline(cin, temp);
}

int main() {
    while (true) {
        cout << "1. Tryb pokazowy (test jednego pliku)" << endl;
        cout << "2. Tryb badan (pomiary czasu)" << endl;
        cout << "0. Wyjscie z programu" << endl;
        cout << "Wybor: ";

        string choiceStr;
        getline(cin, choiceStr);
        if (choiceStr.empty()) continue;

        char choice = choiceStr[0];

        if (choice == '1') {
            trybPokazowy();
        }
        else if (choice == '2') {
            trybBadan();
        }
        else if (choice == '0') {
            break;
        }
    }
    return 0;
}