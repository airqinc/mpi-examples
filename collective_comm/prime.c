#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LIMIT   25000000
#define ROOT    0

int is_prime(int n) {
  if (n > 10) {                   /* se asume que los primos menores que 10 son triviales */
    for (int i = 3; i <= (int) sqrt(n); i = i + 2){
      if ((n % i) == 0){
        return 0;
      }
    }
    return 1;
  }
  else{
    return 0;
  }
}


int main (int argc,  char *argv[]){
  int   world_size,
        world_rank,
        i,
        pc,                       /* Contador de primos */
        pcsum,                    /* Suma de números primos encontrados */
        found_prime,              /* Último primo encontrado */
        max_prime,                /* Primo más grande encontrado */
        start,                    /* Punto en que empieza a buscar cada proceso */
        stride;                   /* Salto entre iteraciones para cada proceso */

  double start_time,  end_time;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  if (((world_size % 2) != 0) || ((LIMIT % world_size) != 0)) {
    printf("Se requiere un número par de procesos que sea divisible entre %d.\n", LIMIT);
    MPI_Finalize();
    exit(0);
  }

  start_time = MPI_Wtime();
  start = (world_rank * 2) + 1;   /* Punto en que empieza a buscar cada proceso */
  stride = world_size * 2;        /* Salto entre iteraciones para cada proceso */
  pc = 0;
  found_prime = 0;

  /******************** ROOT process ********************/
  if (world_rank == ROOT) {
    printf("%d procesos para buscar entre %d números\n", world_size, LIMIT);
    /* COMPLETAR (1 línea) */
    for (i = start; i <= LIMIT; i = i + stride) {
      if (is_prime(i)) {
        /* COMPLETAR (1 línea) */
        /* COMPLETAR (1 línea) */
      }
    }
    /* COMPLETAR (1 línea). Usa MPI */
    /* COMPLETAR (1 línea). Usa MPI */
    end_time = MPI_Wtime();
    printf("Hecho. El primo más grande es %d. Número total de primos encontrados: %d\n", max_prime, pcsum);
    printf("Tiempo consumido: %.2lf segundos\n", end_time - start_time);
  }

  /******************** Resto de procesos que no son ROOT ***********************/
  if (world_rank > ROOT) {
    for (i = start; i <= LIMIT; i = i + stride) {
      if (is_prime(i)) {
        /* COMPLETAR (1 línea) */
        /* COMPLETAR (1 línea) */
      }
    }
    /* COMPLETAR (1 línea). Usa MPI */
    /* COMPLETAR (1 línea). Usa MPI */
  }

  MPI_Finalize();
}
