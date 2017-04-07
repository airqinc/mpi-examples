#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define NUM_ELEM_DEFAULT 5
#define MAX_PROCESSES 50
#define MAX_ELEM_PER_PROCESS 50

void create_array(int n_elem, int a[]);
void print_array(int array[], int length);
void subarray(int a[], int length, int start, int b[]);
void sort_array(int array[], int length);
int cmp(const void* a, const void* b);
void merge_arrays(int m[MAX_PROCESSES][MAX_ELEM_PER_PROCESS], int result[], int n_processes, int n_elem_per_process);

int main(int argc, char ** argv)
{
	int n_elem_per_process, n_elem_global_array,
		rank, size,
		i;
	MPI_Status status;
	
	if (argc == 2) n_elem_per_process = atoi(argv[1]);
	else n_elem_per_process = NUM_ELEM_DEFAULT;
	
	/// INICIO DE MPI (obtener rank y size) ///
	
	// Calculamos el tamaño del array global
	n_elem_global_array = size * n_elem_per_process;
	int global_array[n_elem_global_array],
		array_to_sort[n_elem_per_process],
		data_recieved[MAX_PROCESSES][MAX_ELEM_PER_PROCESS],
		temp[size];
	
	if (rank == 0) {
		// Creamos el array global que se quiere ordenar
		printf("Proceso %d -\n  Procesos: %d\n  Tamano del vector a ordenar: %d\n",rank, size, n_elem_global_array);
		create_array(n_elem_global_array, global_array);
		printf("Proceso %d - Array para ordenar: ",rank); print_array(global_array, n_elem_global_array);
		
		// Dividimos el array global entre todos los procesos para que lo ordenen
		for(¿?){
			/// CÓDIGO AQUÍ ///
		}
		
		// Obtenemos el subarray que tiene que ordenar el proceso "maestro" y lo ordenamos
		subarray(global_array, n_elem_per_process, 0, data_recieved[0]);
		sort_array(data_recieved[0], n_elem_per_process);
		printf("  Proceso %d - Array ordenado: ",rank); print_array(data_recieved[0], n_elem_per_process);
		
		// Recibimos los arrays ordenados del resto de procesos y los almacenamos en la matriz de datos recibidos
		for (¿?){
			/// CÓDIGO AQUÍ ///
			printf("  Proceso %d - Array recibido de %d: ",rank,status.MPI_SOURCE); print_array(temp, n_elem_per_process);
			subarray(temp, n_elem_per_process, 0, data_recieved[i]);
		}
		
		// Unimos y ordenamos todos los arrays ordenados para obtener el array global ordenado
		merge_arrays(data_recieved, global_array, size, n_elem_per_process);
		printf("Proceso %d - Array global ordenado: ",rank); print_array(global_array, n_elem_global_array);
	} else {
		// Recibe los datos
		/// CÓDIGO AQUÍ ///
		
		// Ordena el array recibido
		sort_array(array_to_sort, n_elem_per_process);
		
		// Envía el array ordenado al proceso "maestro"
		/// CÓDIGO AQUÍ ///
	}
	
	/// FIN DE MPI ///
	return 0;
}


void create_array(int n_elem, int a[]){
	int i;
	srand(100);
	for (i=0; i<n_elem; i++){
		a[i] = rand()%100;
	}
}

void print_array(int array[], int length){
	int i;
	
	printf("[ ");
	for (i=0; i < length-1; i++)
		printf("%d, ",array[i]);
	printf("%d ]\n",array[i]);
}

void subarray(int a[], int length, int start, int b[]){
	int i;
	for (i=start ; i < length; i++)
		b[i] = a[i];
}

void sort_array(int array[], int length){
	qsort(array, length, sizeof(int), &cmp);
}

/* comparison function for qsort */
int cmp(const void* a, const void* b){
  return ( *(int*)a - *(int*)b );
}

void merge_arrays(int m[MAX_PROCESSES][MAX_ELEM_PER_PROCESS], int result[], int n_processes, int n_elem_per_process){
	int i, j, 
		min_index = 0, min,
		flags[n_processes],
		result_lenght = n_processes*n_elem_per_process;
	
	for (i=0; i<n_processes; i++) flags[i] = 0;
	
	for (i=0; i<result_lenght; i++){
		min = (int)INFINITY;
		
		// Comenzamos a partir el ultimo elemento ya incluido en el array global ordenado
		for (j=0; j<n_processes; j++){
			if (flags[j] < n_elem_per_process && m[j][flags[j]] < min){
				min_index = j;
				min = m[j][flags[j]];
				
			}
		}
		
		result[i] = m[min_index][flags[min_index]];
		flags[min_index]++;
	}
}