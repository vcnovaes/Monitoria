#include <bits/stdc++.h>
#include <omp.h>
#include "./../utils.hpp"

using namespace std;

/***
   Temos varios tipos de diretivas em openMP
     - Temos parallel para paralelismo
     - Alguma para divisão de tarefas
       - for, section single, task etc
     - Algumas de sincronização
       -barrier, master, critical, atomic, ordered
   */
/***
     Clausulas
     - if , private, shared, default(none|shared), reduction(operador: list)
     - copyin , first private, num_threads
 *  */
void ifExample(int val)
{
    #pragma omp parallel if (val)
    if (omp_in_parallel())
    {
        #pragma omp single
        printf("val = %d, parallelized with %d threads\n",
                 val, omp_get_num_threads());
    }
    else
    {
        printf("val = %d, serialized\n", val);
    }
}


void helloOpenMP()
{
  // check if libgomp-dev is present in your system
  int numberOfThreads, threadId;
  #pragma omp parallel private(numberOfThreads, threadId) // cada thread vai ter uma copia de numberOfThreads e threadId
  {
    threadId = omp_get_thread_num(); // get the current thread id
    printf("Hello by the thread %d\n", threadId); 
    if (!threadId)
      cout << "... and we are running ... "
           << omp_get_num_threads()
           << " threads!"
           << "<<  MASTER THREAD!!\n"; 
  }
}

void wsFOR(int n)
{
  // barreira IMPLICITA - exceto adicição de nowait 
  IntMatrix matrixA = generateRndIntMatrix(n, n);
  cout << "Matrix A:\n";
  printMatrix(matrixA);
  cout << "\n\nMatrix B:\n";
 
  IntMatrix matrixB = generateRndIntMatrix(n, n);
  printMatrix(matrixB);
}

bool isOdd(int number) { return number % 2; }

void wsSections(int matrixSize, bool paralell)
{
  /**
   * @brief
   *  - Serve para listar blocos que serão processados por threads separadas
   *  - Precisam de {}
   *  ! se uma thread for muito rapida ela pode executar mais de uma section
   *  - ou se um  num_threads  definido pelo programador for menor do que o número de sections
   */
  int i,  threadId;
  int oddCount = 0;
  IntMatrix matrix = generateRndIntMatrix(matrixSize, matrixSize);
  cout << "\n Matrix: ";
  printMatrix(matrix);
  #pragma omp paralell private(i, threadId)
  {
    #pragma omp paralell for shared(oddCount)
    for(i = 0;  i < matrixSize; i++) 
    {
      #pragma omp sections 
      {
        #pragma omp section
        {
          for(int j = 0; j < matrixSize/2; j++)
            oddCount += isOdd(matrix[i][j]); 
        }
        #pragma omp section
        {
          for(int j = matrixSize/2; j < matrixSize; j++) 
            oddCount += isOdd(matrix[i][j]); 
        }
      }
    }
  }
  cout << "\n Total of odd numbers: " << oddCount << '\n'; 
}



/**
 * @brief 
 *  Barreiras servem em casos que desejamos evitar race condition 
 *    - Dependencia de dados
 * 
 * @param barrier
 *   - Barreira implicita tipo o for 
 */

/**
 * @brief 
 *  CRITICAL 
 *  - Delimita região critica ( apenas uma thread pode entrar por vez na região crítica )
 *  - Cria barreira implicita    
 * 
 * @param critical
 * @param [name]  // opcional 
 * 
 */
void syncCritical() 
{
  int data = 0, threadId; 
  #pragma omp parallel num_threads(5) private(threadId) shared(data) 
  {
  #pragma critical
    {
      data++; 
      threadId = omp_get_thread_num(); 
      printf("Thread : %d \n ", threadId); 
      printf(" data: %d \n ", data); 
    }
  }
}
/***
 *  !Single 
 *    = somente uma thread deve executar aquelee trecho de código 
 *    - Random choose
 *    -  As outras ficam esperando , estilo barreira implicita caso não tenha nowait 
 *  !Master  
 *    - Essa diretiva especifica que somente a thread master deve executar o 
 *    código delimitado
 * 
 * 
 * **/

/**
 * @brief  Funções de lock . tipo critical só que não é diretiva 
 *  - Permite que não adquiram lock façam as outras eseprar 
 */

/**
 * @brief  Variáveis de ambiente 
 *  OMP_NUM_THREADS  -> quantidade de threads 
 *  OMP_DYNAMIC -> controla se a quantidade de threads deve ser dinamica ou não 
 * OMP_NESTED  -> aninhamento de paralelismo
 * 
 */
void opmFunctions()
{
  int threadQtd = 10;
  omp_set_num_threads(threadQtd); 
  int threadNumbers = omp_get_num_threads(); 
  omp_get_num_procs(); 
  // Lock
  omp_lock_t myLock; 
  omp_init_lock(&myLock);
  omp_set_lock(&myLock); 
  int isLocked = omp_test_lock(&myLock);
  omp_unset_lock(&myLock); 
  omp_destroy_lock(&myLock); 
}

int main(int argc, char **argv)
{
  // helloOpenMP();
  string arg(argv[1]);
  int dimensionOfMatrix = stoi(arg, nullptr);
  // wsFOR(dimensionOfMatrix);
  //wsSections(dimensionOfMatrix,false); 
  syncCritical(); 
}