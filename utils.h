#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <functional>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "timer.h"

// Typy rozk³adu danych do generowania
enum class Distribution {
    RANDOM,
    ASCENDING,
    DESCENDING,
    PARTIALLY_SORTED_33,
    PARTIALLY_SORTED_66
};

// Deklaracje szablonowych funkcji
template<typename T>
void generateData(T* array, size_t size, Distribution dist);

template<typename T>
bool isSorted(T* array, size_t size);

template<typename T>
void calculateStatistics(const std::vector<int>& times, int& min, int& max, double& avg, int& median);

template<typename T>
void generateData(T* array, size_t size, Distribution dist) {
    std::mt19937 rng(std::random_device{}());

    // Losowanie danych w zale¿noœci od typu
    if (std::is_same_v<T, int>) {
        std::uniform_int_distribution<int> distInt(0, 100000);
        for (size_t i = 0; i < size; ++i)
            array[i] = static_cast<T>(distInt(rng));
    }
    else if (std::is_same_v<T, float>) {
        std::uniform_real_distribution<float> distFloat(0.0, 100000.0);
        for (size_t i = 0; i < size; ++i)
            array[i] = static_cast<T>(distFloat(rng));
    }
    else if (std::is_same_v<T, char>) {
        std::uniform_int_distribution<int> distChar(65, 90);
        for (size_t i = 0; i < size; ++i)
            array[i] = static_cast<T>(distChar(rng));
    }
    else {
        throw std::invalid_argument("Unsupported type");
    }

    // Dodatkowe przetwarzanie w zale¿noœci od rozk³adu
    switch (dist) {
    case Distribution::ASCENDING:
        std::sort(array, array + size);
        break;
    case Distribution::DESCENDING:
        std::sort(array, array + size, std::greater<T>());
        break;
    case Distribution::PARTIALLY_SORTED_33:
        std::sort(array, array + (size * 33) / 100);
        break;
    case Distribution::PARTIALLY_SORTED_66:
        std::sort(array, array + (size * 66) / 100);
        break;
    default:
        break;
    }
}

// Sprawdzenie, czy tablica jest posortowana
template<typename T>
bool isSorted(T* array, size_t size) {
    for (size_t i = 1; i < size; ++i)
        if (array[i - 1] > array[i])
            return false;
    return true;
}

// Obliczanie statystyk na podstawie czasów
template<typename T>
void calculateStatistics(const std::vector<int>& times, int& min, int& max, double& avg, int& median) {
    std::vector<int> sorted = times;
    std::sort(sorted.begin(), sorted.end());
    min = sorted.front();
    max = sorted.back();
    avg = std::accumulate(sorted.begin(), sorted.end(), 0.0) / sorted.size();
    median = sorted[sorted.size() / 2];
}


#endif#pragma once
