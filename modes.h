#ifndef MODES_H
#define MODES_H

#include <string>
#include "sorter.h"
#include "utils.h"

// Deklaracje funkcji szablonowych
template<typename T>
void fileMode(SortType type, const std::string& input, const std::string& output);

template<typename T>
void testSorting(SortType type, Distribution dist, size_t size, const std::string& outFile);

// Implementacja funkcji odczytuj¹cej dane z pliku i sortuj¹cej je
template<typename T>
void fileMode(SortType type, const std::string& input, const std::string& output) {
    std::ifstream in(input);
    if (!in) throw std::runtime_error("Cannot open input file");

    int size;
    in >> size;
    if (size <= 0) throw std::runtime_error("Invalid data size in input file");

    T* data = new T[size];
    for (int i = 0; i < size; ++i) {
        if (!(in >> data[i])) {
            delete[] data;
            throw std::runtime_error("Error reading input data");
        }
    }
    in.close();

    Timer timer;
    timer.start();
    Sorter<T>::sort(data, size, type);
    timer.stop();

    std::cout << "Sorting took " << timer.result() << " ms\n";

    if (!output.empty()) {
        std::ofstream out(output);
        if (!out) {
            delete[] data;
            throw std::runtime_error("Cannot open output file");
        }
        out << size << '\n';
        for (int i = 0; i < size; ++i) {
            out << data[i] << '\n';
        }
        out.close();
    }

    delete[] data;// jak usuwam data to powinnam zapisaæ potem przypisaæ null
}

// Implementacja funkcji generuj¹cej dane i testuj¹cej sortowanie
template<typename T>
void testSorting(SortType type, Distribution dist, size_t size, const std::string& outFile) {
    const int trials = 100;
    std::vector<int> times;
    Timer timer;

    T* data = new T[size];
    T* backup = new T[size];

    for (int i = 0; i < trials; ++i) {
        generateData<T>(backup, size, dist);
        std::copy(backup, backup + size, data);

        /* std::cout << "Dane PRZED sortowaniem:\n";
         for (size_t i = 0; i < size; ++i)
             std::cout << data[i] << " ";
         std::cout << "\n";*/

        timer.start();
        Sorter<T>::sort(data, size, type);
        timer.stop();
        
        /*std::cout << "Dane PO sortowaniu:\n";
        for (size_t i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << "\n";*/

        if (!isSorted(data, size))
            std::cerr << "Sorting failed on trial " << i << "\n";

        std::cout << "Posortowano " << i<<"\n";
        times.push_back(timer.result());
    }

    std::cout << "Kompilacja przebieg³a poprawnie, pliki zapisane do " << outFile;
    int min, max, median;
    double avg;
    calculateStatistics<T>(times, min, max, avg, median);

    std::ofstream out(outFile);
    if (!out) {
        std::cerr << "Nie mo¿na otworzyæ pliku wyjœciowego!\n";
        return;
    }

    out << "Data i godzina,Czas sortowania [ms]\n";

    // Zapisz ka¿dy wynik z dat¹ i godzin¹
    for (int time : times) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm localTime;
        localtime_s(&localTime, &now_time);
        out << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << ",";
        out << time << "\n";
    }

    // Statystyki
    out << "\nStatystyki\n";
    out << "MIN," << min << "\n";
    out << "MAX," << max << "\n";
    out << "AVG," << avg << "\n";
    out << "MEDIAN," << median << "\n";

    out.close();


    delete[] data;
    delete[] backup;
}


#endif

