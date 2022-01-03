#include <windows.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include <fstream>
#include <string>
#include "Timer.h"
#include "Params1.h"
#include "Params2.h"

std::vector<std::vector<int>> matrix1;
std::vector<std::vector<int>> matrix2;
std::vector<std::vector<int>> result;
int size;
int amountOfThreads;
std::mutex lockMultiply3;

void readData();
std::vector<std::vector<int>> multiplyRowsByCols(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2);
std::vector<std::vector<int>> multiplyColsByRows(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2);

void multiply2();
void multiply3();

DWORD WINAPI threadMultiply2(void* pVoid);
DWORD WINAPI threadMultiply3(void* pVoid);

void print(const std::vector<std::vector<int>>& v);

int main() {
    readData();

    std::cout << "matrix1:\n";
    print(matrix1);

    std::cout << "matrix2:\n";
    print(matrix2);

    Timer timer;
    result = multiplyRowsByCols(matrix1, matrix2);
    std::cout << "multiply1:\nThe time: " << timer.elapsed() << '\n';
    print(result);
    result.clear();
    result.resize(size,std::vector<int>(size, 0));

    timer.reset();
    multiply2();
    std::cout << "\nmultiply2:\nThe time: " << timer.elapsed() << '\n';
    print(result);
    result.clear();
    result.resize(size,std::vector<int>(size, 0));

    timer.reset();
    multiply3();
    std::cout << "\nmultiply3:\nThe time: " << timer.elapsed() << '\n';
    print(result);
    result.clear();
    result.resize(size,std::vector<int>(size, 0));

    return 0;
}

void readData() {
    std::ifstream file("input.txt");

    if(file.is_open()) {
        std::string line, value;
        std::getline(file, value, ' ');
        size = std::stoi(value);
        std::getline(file, value);
        amountOfThreads = std::stoi(value);

        matrix1.resize(size,std::vector<int>(size));
        matrix2.resize(size,std::vector<int>(size));
        result.resize(size,std::vector<int>(size));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                (j == size - 1) ?
                    std::getline(file, value, '\n')
                    : std::getline(file, value, ' ');
                matrix1[i][j] = std::stoi(value);
            }
        }

        for (int i = 0; i <size; ++i) {
            for (int j = 0; j < size; ++j) {
                (j == size - 1) ?
                std::getline(file, value, '\n')
                                : std::getline(file, value, ' ');
                matrix2[i][j] = std::stoi(value);
            }
        }
    } else {
        throw std::exception("cannot open the file!");
    }
}

void multiply2() {
    auto* threads = new HANDLE[amountOfThreads];
    int blockSize = size / amountOfThreads;
    for (int i = 0; i < amountOfThreads; ++i) {
        int end = i * blockSize + blockSize;
        if(i == amountOfThreads - 1) {
            end = size;
        }
        auto* params = new Params1(i * blockSize, end);
        threads[i] = CreateThread(nullptr, 0, threadMultiply2, (void*)params, 0, nullptr);
    }
    WaitForMultipleObjects(amountOfThreads, threads, TRUE, INFINITE);
    delete[] threads;
}

void multiply3() {
    auto* threads = new HANDLE[amountOfThreads];
    int blockSize = size / amountOfThreads;
    for (int i = 0; i < amountOfThreads; ++i) {
        int end = i * blockSize + blockSize;
        if(i == amountOfThreads - 1) {
            end = size;
        }
        auto* params = new Params2(i * blockSize, end);
        threads[i] = CreateThread(nullptr, 0, threadMultiply3, (void*)params, 0, nullptr);
    }
    WaitForMultipleObjects(amountOfThreads, threads, TRUE, INFINITE);
    delete[] threads;
}

DWORD WINAPI threadMultiply2(void* pVoid) {
    auto *p = (Params1*) pVoid;

    std::vector<std::vector<int>> partialMatrix1;
    std::vector<std::vector<int>> partialResult;

    for (int i = p->row1; i < p->row2; ++i) {
        partialMatrix1.push_back(matrix1[i]);
    }
    partialResult = multiplyRowsByCols(partialMatrix1, matrix2);
    for (int i = p->row1, k = 0; i < p->row2; ++i, ++k) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = partialResult[k][j];
        }
    }
    delete p;
    return 0;
}

DWORD WINAPI threadMultiply3(void* pVoid) {
    auto *p = (Params2*) pVoid;

    std::vector<std::vector<int>> partialMatrix1(size, std::vector<int>(1, 0));
    std::vector<std::vector<int>> partialResult;

    for (int iter = p->col1; iter < p->col2; ++iter) {
        for (int j = 0; j < size; ++j) {
            partialMatrix1[j][0] = matrix1[j][iter];
        }

        partialResult = multiplyColsByRows(partialMatrix1, std::vector<std::vector<int>>(1, matrix2[iter]));

        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                lockMultiply3.lock();
                result[j][k] += partialResult[j][k];
                lockMultiply3.unlock();
            }
        }
    }

    delete p;
    return 0;
}

std::vector<std::vector<int>> multiplyRowsByCols(
        std::vector<std::vector<int>> v1,
        std::vector<std::vector<int>> v2) {
    int n1 = v1.size();
    int n2 = v2.size();
    int m1 = v1[0].size();
    int m2 = v2[0].size();
    if(m1 != n2) {
        throw std::exception("incorrect matrix sizes!");
    }
    std::vector<std::vector<int>> res(n1, std::vector<int>(m2));
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m2; ++j) {
            long sum = 0;
            for (int k = 0; k < m1; ++k) {
                sum += v1[i][k] * v2[k][j];
            }
            res[i][j] = sum;
        }
    }
    return res;
}

std::vector<std::vector<int>> multiplyColsByRows(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2) {
    int n1 = v1.size();
    int n2 = v2.size();
    int m1 = v1[0].size();
    int m2 = v2[0].size();
    if(m1 != n2) {
        throw std::exception("incorrect matrix sizes!");
    }
    std::vector<std::vector<int>> res(n1, std::vector<int>(m2, 0));
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < m2; ++j) {
            long sum = 0;
            for (int k = 0; k < n2; ++k) {
                sum += v1[i][k] * v2[k][j];
            }
            res[i][j] = sum;
        }
    }
    return res;
}

void print(const std::vector<std::vector<int>> &v) {
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[0].size(); ++j) {
            std::cout << v[i][j] << "\t";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}