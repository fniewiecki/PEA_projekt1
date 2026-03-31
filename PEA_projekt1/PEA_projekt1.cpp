#include <iostream>
#include <string>
#include "Graph.h"
#include "BruteForce.h"
#include "NearestNeighbour.h"
#include "RNN.h"
#include "Rand.h"
#include <fstream>
#include <vector>
#include <iomanip>

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
        cout << "4. Random Search" << endl;
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
        else if (algChoice == '4')
        {
            Rand r(graph,100000000);
            int N = graph.getN();
            int* bestRoute = r.getPath();

            if (bestRoute != nullptr) {
                cout << "\nWynik Repetetive Nearest Neighbour:" << endl;
                cout << "Najmniejszy koszt: " << r.getMinCost() << endl;
                cout << "Czas wykonania: " << r.getTime() << " milisekund" << endl;
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
    cout << "Badania" << endl;
    
    // --- CZĘŚĆ 1: BADANIA BRUTE FORCE ---
    string plikiBF[] = { "br5.atsp", "br8.atsp", "br9.atsp", "br10.atsp", "br11.atsp", "br12.atsp", "br13.atsp" };
    int liczbaPlikowBF = 7;
    int powtorzeniaBF = 10; // 10 prób wystarczy dla dokładnego pomiaru

    cout << ">>> ETAP 1: Testy Algorytmu Dokladnego (Brute Force) <<<" << endl;
    ofstream plikCSV_BF("wyniki_bruteforce.csv");
    if (plikCSV_BF.is_open()) {
        plikCSV_BF << "Plik;Rozmiar_N;Czas_BF_ms;Koszt_BF\n";

        for (int i = 0; i < liczbaPlikowBF; i++) {
            Graph graph;
            if (!graph.loadFromFile(plikiBF[i])) {
                cout << "Pominiecie pliku " << plikiBF[i] << " (brak na dysku)." << endl;
                continue;
            }

            int N = graph.getN();
            cout << "Badam plik: " << plikiBF[i] << " (N = " << N << ") " << flush;

            double sumaCzasuBF = 0.0;
            int kosztBF = 0;

            for (int r = 0; r < powtorzeniaBF; r++) {
                BruteForce bf(graph);
                bf.FindPath();
                sumaCzasuBF += bf.getOverallTime();
                kosztBF = bf.getMinCost();
            }

            plikCSV_BF << plikiBF[i] << ";" << N << ";"
                << (sumaCzasuBF / powtorzeniaBF) << ";" << kosztBF << "\n";
            cout << "-> Gotowe!" << endl;
        }
        plikCSV_BF.close();
        cout << "Etap 1 zakonczony! Zapisano 'wyniki_bruteforce.csv'.\n" << endl;
    }
    
    // --- CZĘŚĆ 2: BADANIA HEURYSTYK (NN, RNN, Random) ---
    string plikiHeur[] = { "br5.atsp", "br13.atsp", "ftv38.atsp", "ftv70.atsp", "kro124p.atsp", "ftv170.atsp", "rbg323.atsp" };
    int liczbaPlikowHeur = 7;
    int powtorzeniaHeur = 10; // Heurystyki są błyskawiczne, uśredniamy ze 100 prób

    cout << ">>> ETAP 2: Testy Heurystyk (NN, RNN, Random Search) <<<" << endl;
    ofstream plikCSV_Heur("wyniki_heurystyki.csv");
    if (plikCSV_Heur.is_open()) {
        // Potężny nagłówek z podziałem na iteracje algorytmu losowego
        plikCSV_Heur << "Plik;Rozmiar_N;Czas_NN;Koszt_NN;Czas_RNN;Koszt_RNN;"
            << "Czas_Rand_1k;Koszt_Rand_1k;"
            << "Czas_Rand_10k;Koszt_Rand_10k;"
            << "Czas_Rand_100k;Koszt_Rand_100k\n";

        for (int i = 0; i < liczbaPlikowHeur; i++) {
            Graph graph;
            if (!graph.loadFromFile(plikiHeur[i])) {
                cout << "Pominiecie pliku " << plikiHeur[i] << " (brak na dysku)." << endl;
                continue;
            }

            int N = graph.getN();
            cout << "Badam plik: " << plikiHeur[i] << " (N = " << N << ") " << flush;

            double sumCzasNN = 0, sumCzasRNN = 0;
            double sumCzasR1 = 0, sumCzasR2 = 0, sumCzasR3 = 0;

            // Do zapisania średniego kosztu z prób (opcjonalnie można też zbierać najlepszy, ale weźmy uśredniony koszt z przebiegów badawczych)
            long long sumKosztNN = 0, sumKosztRNN = 0;
            long long sumKosztR1 = 0, sumKosztR2 = 0, sumKosztR3 = 0;

            for (int r = 0; r < powtorzeniaHeur; r++) {
                // 1. Zwykły NN (Z losowym startem)
                
                NearestNeighbour nn(graph);
                nn.getPath();
                sumCzasNN += nn.getTime();
                sumKosztNN += nn.getMinCost();

                // 2. Repetitive NN
                RNN rnn(graph);
                rnn.getPath();
                sumCzasRNN += rnn.getTime();
                sumKosztRNN += rnn.getMinCost();
                
                // 3. Random Search (1 000 000 iteracji)
                Rand rand1k(graph, 1000000);
                rand1k.getPath();
                sumCzasR1 += rand1k.getTime();
                sumKosztR1 += rand1k.getMinCost();

                // 4. Random Search (10 000 000 iteracji)
                Rand rand10k(graph, 10000000);
                rand10k.getPath();
                sumCzasR2 += rand10k.getTime();
                sumKosztR2 += rand10k.getMinCost();

                // 5. Random Search (100 000 000 iteracji)
                Rand rand100k(graph, 100000000);
                rand100k.getPath();
                sumCzasR3 += rand100k.getTime();
                sumKosztR3 += rand100k.getMinCost();
            }

            // Zapis uśrednionych wyników do CSV
            plikCSV_Heur << plikiHeur[i] << ";" << N << ";"
                << (sumCzasNN / powtorzeniaHeur) << ";" << (sumKosztNN / powtorzeniaHeur) << ";"
                << (sumCzasRNN / powtorzeniaHeur) << ";" << (sumKosztRNN / powtorzeniaHeur) << ";"
                << (sumCzasR1 / powtorzeniaHeur) << ";" << (sumKosztR1 / powtorzeniaHeur) << ";"
                << (sumCzasR2 / powtorzeniaHeur) << ";" << (sumKosztR2 / powtorzeniaHeur) << ";"
                << (sumCzasR3 / powtorzeniaHeur) << ";" << (sumKosztR3 / powtorzeniaHeur) << "\n";

            cout << "-> Gotowe!" << endl;
        }
        plikCSV_Heur.close();
        cout << "Etap 2 zakonczony! Zapisano 'wyniki_heurystyki.csv'.\n" << endl;
    }

    cout << "Koniec" << endl;
    cout << "Wcisnij ENTER, aby wrocic do menu." << endl;

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