#ifndef SORTER_H
#define SORTER_H

#include <cstddef>
#include <random>
#include "utils.h"

// Typy sortowania
enum class SortType {
    INSERTION,
    BINARY_INSERTION,
    HEAP,
    QUICK,
    DRUNK
};

// Szablonowa klasa Sorter
template<typename T>
class Sorter {
public:
    static void sort(T* array, size_t size, SortType type);
private:
    static void insertionSort(T* array, size_t size);
    static void binaryInsertionSort(T* array, size_t size);
    static void heapSort(T* array, size_t size);
    static void heapify(T* array, size_t size, size_t root);
    static void quickSort(T* array, int left, int right);
    static void drunkInsertionSort(T* array, size_t size);
};

// Implementacja szablonowej klasy Sorter
template<typename T>
void Sorter<T>::sort(T* array, size_t size, SortType type) {
    switch (type) {
    case SortType::INSERTION:
        insertionSort(array, size);
        break;
    case SortType::BINARY_INSERTION:
        binaryInsertionSort(array, size);
        break;
    case SortType::HEAP:
        heapSort(array, size);
        break;
    case SortType::QUICK:
        quickSort(array, 0, static_cast<int>(size) - 1);
        break;
    case SortType::DRUNK:
        drunkInsertionSort(array, size);
        break;
    default:
        throw std::invalid_argument("Nieznany typ sortowania");
    }
}

// Implementacja algorytmu sortowania przez wstawianie
template<typename T>
void Sorter<T>::insertionSort(T* array, size_t size) {
    for (int i = 1; i < static_cast<int>(size); ++i) {
        T key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

// Implementacja algorytmu sortowania przez wstawianie binarne
template<typename T>
void Sorter<T>::binaryInsertionSort(T* array, size_t size) {
    if (!array || size == 0) return;

    for (size_t i = 1; i < size; ++i) {
        T key = array[i];
        int left = 0;
        int right = static_cast<int>(i) - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (array[mid] > key)
                right = mid - 1;
            else
                left = mid + 1;
        }

        for (int j = static_cast<int>(i); j > left; --j)
            array[j] = array[j - 1];
        array[left] = key;
    }
}

// Implementacja algorytmu sortowania przez kopcowanie
template<typename T>
void Sorter<T>::heapify(T* array, size_t size, size_t root) {
    size_t largest = root;
    size_t left = 2 * root + 1;
    size_t right = 2 * root + 2;

    if (left < size && array[left] > array[largest])
        largest = left;
    if (right < size && array[right] > array[largest])
        largest = right;

    if (largest != root) {
        std::swap(array[root], array[largest]);
        heapify(array, size, largest);
    }
}

template<typename T>
void Sorter<T>::heapSort(T* array, size_t size) {
    for (size_t i = size / 2; i-- > 0; )
        heapify(array, size, i);
    for (size_t i = size - 1; i > 0; --i) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

// Implementacja algorytmu sortowania szybkim
template<typename T>
void Sorter<T>::quickSort(T* array, int left, int right) {
    if (left >= right) return;
    T pivot = array[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (array[i] < pivot) ++i;
        while (array[j] > pivot) --j;
        if (i <= j) std::swap(array[i++], array[j--]);
    }
    if (left < j) quickSort(array, left, j);
    if (i < right) quickSort(array, i, right);
}

// Implementacja algorytmu sortowania przez wstawianie w trybie "pijanym"
template<typename T>
void Sorter<T>::drunkInsertionSort(T* array, size_t size) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> chance(1, 100);
    int drunkness = 50; // % szans, ¿e student pominie liczbê

    while (!isSorted(array, size)) {
        for (size_t i = 1; i < size; ++i) {
            // Student mo¿e pomin¹æ ten element
            if (chance(rng) <= drunkness) {
                continue; // nie chce mu siê sortowaæ tej liczby
            }

            T key = array[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                --j;
            }
            array[j + 1] = key;
        }
    }

    
}



#endif
