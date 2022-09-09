#include <omp.h>
#include <stdio.h>
void syncCritical() 
{
  int data = 0, threadId; 
  #pragma omp parallel num_threads(5) private(threadId) shared(data) 
  {
    #pragma omp critical
    {
      data++; 
      threadId = omp_get_thread_num(); 
      printf("Thread : %d \n ", threadId); 
      printf(" data: %d \n ", data); 
    }
  }
}

int main() {
  syncCritical(); 
}