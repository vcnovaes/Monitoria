#include <stdio.h>

void print(int value) { printf("%d\n", value); }

int vecSum(int* arr, int arrSize) 
{
  int sum = 0;
  for(int i = 0; i < arrSize; i++)
    sum += arr[i]; 
  return sum; 
}


