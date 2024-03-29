#include <vector>
#include <iostream>

// Технические функции.
void fillVector(std::vector<int>& vec, size_t count, int min, int max); // Заполнить вектор count случайными числами из отрезка [min; max].
void printVector(const std::vector<int>& vec, std::ostream& out); // Напечатать вектор в поток out.
int power10(int power); // Получить десять в степени power.
int getTheLongestNumberLength(const std::vector<int>& vec); // Длинна самого длинного числа в векторе.
typedef void (*SortFunctionPointer) (std::vector<int>&); // Определения типа указателя на сортирующую функцию.
void testSort(SortFunctionPointer sortFunction, bool isPrint = false); // Функция тестирования сортировки вектора, указатель на функцию подается в качестве параметра.
void testSortComplex(); // Функция тестирования временной сложности сортировок.

// Вспомогательные функции для сортировок.
bool isVectorSorted(const std::vector<int>& vec); // Проверка, отсортирован ли вектор по неубыванию.
size_t binarySearchPlace(const std::vector<int>& vec, int element, size_t left, size_t right); // Бинарный поиск самого левого элемента, который надо передвинуть.
int getDigit(int number, int digit); // Получить digit-ый разряд числа number.
void mergeVector(std::vector<int>& vec, size_t left, size_t middle, size_t right); // Слить в векторе два отрезка: [left; middle] и [middle + 1; right].

// Сортировки.
void insertionBinarySort(std::vector<int>& vec); // Сортировка по методу вставок с двоичным поиском места вставки.
void radixSort(std::vector<int>& vec); // Поразрядная сортировка.
void mergeIterativeSort(std::vector<int>& vec); // Итеративная сортировка слиянием.
