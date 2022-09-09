#include <stdio.h>
extern int sum(int, int, int);
extern int subtraction(int,int); 

int main() {
  int var1 = 1, var2 = 2, var3 = 3;
  printf("Sum: %d\n", sum(var1, var2, var3));
  printf("Subtraction: %d\n", subtraction(var1,var2));
  return 0;
}