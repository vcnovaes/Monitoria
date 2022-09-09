#include "utils.hpp"

std::vector<int> generateRndIntVec(int sz)
{
  std::vector<int> vec(sz);
  int i;
#pragma omp paralell for shared(vec) 
  for (i = 0; i < sz; i++)
  {
    vec[i] = rand() % 10;
  }
  return vec;
}

IntMatrix generateRndIntMatrix(int numberOfRows, int numberOfCols)
{
  IntMatrix matrix = IntMatrix();
  matrix.resize(numberOfRows);
  int i;
#pragma omp parallel for shared(matrix)
  for (i = 0; i < numberOfRows; i++)
  {
    matrix[i] = generateRndIntVec(numberOfCols);
    printf("Número de threads: %d", omp_get_num_threads()); 
  }
  return matrix;
}

void printMatrix(IntMatrix matrix)
{
  for (auto row : matrix)
  {
    std::cout << '\n';
    for (auto el : row)
      std::cout << el << ' ';
  }
  std::cout << '\n';
}