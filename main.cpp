#include <iostream>
#include "timer.h"
#include "sorter.h"
#include "utils.h"
#include "modes.h"

// Funkcja pomocnicza do wyœwietlania pomocy
void showHelp() {
    std::cout << "PROGRAM SORTUJ¥CY \n";
    std::cout << "====================\n";
    std::cout << "Sposób u¿ycia:\n";
    std::cout << "  --test <algorytm> <typ> <rozmiar> <rozk³ad> <plik_wyjsciowy>\n";
    std::cout << "    algorytm: insert | bininsert | heap | quick | quickdrunk\n";
    std::cout << "    typ: int | float | char\n";
    std::cout << "    rozk³ad: random | ascending | descending | partly sorted 33% | partly sorted 66%\n";
    std::cout << "    rozmiar: liczba elementów do wygenerowania i posortowania\n";
    std::cout << "    plik_wyjsciowy: nazwa pliku, do którego zostan¹ zapisane statystyki\n";
    std::cout << "Przyk³ad: --test insert int 1000 dane.txt\n";
    std::cout << "  --file <algorytm> <typ> <plik_wejsciowy> [plik_wyjsciowy]\n";
    std::cout << "    algorytm: insert | bininsert | heap | quick | quickdrunk\n";
    std::cout << "    typ: int | float | char\n";
    std::cout << "    plik_wejsciowy: nazwa pliku z danymi do posortowania\n";
    std::cout << "    plik_wyjsciowy: nazwa pliku, do którego zostan¹ zapisane posortowane dane (opcjonalnie)\n";
    std::cout << "Przyk³ad: --file insert int dane.txt posortowane.txt\n";
    std::cout << "  --help\n";
    std::cout << "    Wyœwietla tê pomoc.\n";
}

// Funkcja pomocnicza do parsowania algorytmu
SortType parseAlgorithm(const std::string& alg) {
    if (alg == "insert") return SortType::INSERTION;
    if (alg == "bininsert") return SortType::BINARY_INSERTION;
    if (alg == "heap") return SortType::HEAP;
    if (alg == "quick") return SortType::QUICK;
	if (alg == "drunk") return SortType::DRUNK;

    throw std::invalid_argument("Unknown algorithm");
}

// Funkcja pomocnicza do parsowania algorytmu
Distribution parseDistribution(const std::string& cos) {
    if (cos == "random") return Distribution::RANDOM;
    if (cos == "ascending") return Distribution::ASCENDING;
    if (cos == "descending") return Distribution::DESCENDING;
    if (cos == "partly33") return Distribution::PARTIALLY_SORTED_33;
    if (cos == "partly66") return Distribution::PARTIALLY_SORTED_66;
    throw std::invalid_argument("Unknown algorithm");
}

// Funkcja g³ówna
int main(int argc, char* argv[]) {
    if (argc < 2) {
        showHelp();
        return 1;
    }

    std::string mode = argv[1];

    try {
        if (mode == "--help") {
            showHelp();
        }
        else if (mode == "--test" && argc == 7) {
            SortType alg = parseAlgorithm(argv[2]);
            std::string type = argv[3];
            size_t size = std::stoul(argv[4]);
            Distribution dist = parseDistribution(argv[5]);
            std::string outFile = argv[6];

            if (type == "int") testSorting<int>(alg, dist, size, outFile);
            else if (type == "float") testSorting<float>(alg, dist, size, outFile);
            else if (type == "char") testSorting<char>(alg, dist, size, outFile);
            else throw std::invalid_argument("Unknown type");
        }
        else if (mode == "--file" && (argc == 5 || argc == 6)) {
            SortType alg = parseAlgorithm(argv[2]);
            std::string type = argv[3];
            std::string inputFile = argv[4];
            std::string outputFile = (argc == 6) ? argv[5] : "";

            if (type == "int") fileMode<int>(alg, inputFile, outputFile);
            else if (type == "float") fileMode<float>(alg, inputFile, outputFile);
            else if (type == "char") fileMode<char>(alg, inputFile, outputFile);
            else throw std::invalid_argument("Unknown type");
        }
        else {
            std::cerr << "Invalid arguments\n";
            showHelp();
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
