#include <vector>
#include <cstdlib>
#include <omp.h>
#include <iostream>

typedef std::vector<std::vector<int>> IntMatrix;

IntMatrix generateRndIntMatrix(int numberOfRows, int numberOfCols);

void printMatrix(IntMatrix matrix);

void printMatrixParallel(IntMatrix matrix);

std::vector<int> generateRndIntVec(int size);