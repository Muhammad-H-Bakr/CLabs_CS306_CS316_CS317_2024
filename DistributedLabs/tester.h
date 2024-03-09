#ifndef DESKTOP_TESTER_H
#define DESKTOP_TESTER_H

#include <iostream>
#include <chrono>
#include <cmath>
#include <random>

using namespace std;
using namespace std::chrono;

void createMatrix(int **&, int, int);

void createMatrix2(double **&, int, int);

void addMatrices1(int **&, int **&, int **&, int, int);

void addMatrices2(int **&, int **&, int **&, int, int);

double trapQuad(double, double);

void multiplyMatrix(double **&, double **&, double **&, int, int, int, int);

#endif //DESKTOP_TESTER_H