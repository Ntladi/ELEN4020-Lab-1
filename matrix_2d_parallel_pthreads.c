#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "populate.h"

#define NUM_THREADS 3
#define MAT_LENGTH 5
#define MAT_SQUARE MAT_LENGTH*MAT_LENGTH

int *matrix_A;
int *matrix_B;
int *matrix_C;

void *rank2TensorMultPThreads(void* arg);
void indexMultiplication(int index);

int main()
{

	matrix_A = (int *)malloc(MAT_SQUARE * sizeof(int));
	matrix_B = (int *)malloc(MAT_SQUARE * sizeof(int));
	matrix_C = (int *)malloc(MAT_SQUARE * sizeof(int));

	populate_2D(matrix_A,matrix_B,MAT_LENGTH);

	pthread_t threads[NUM_THREADS];
	int thread_ids[NUM_THREADS];

	for(int index = 0; index < NUM_THREADS; index ++)
	{
		thread_ids[index] = index;
		pthread_create(&threads[index], NULL,rank2TensorMultPThreads, &thread_ids[index]);
	}

	for(int index = 0; index < NUM_THREADS; index ++)
		pthread_join(threads[index], NULL);

	print2D(matrix_A,MAT_LENGTH);
	print2D(matrix_B,MAT_LENGTH);
	print2D(matrix_C,MAT_LENGTH);

	free(matrix_A);
	free(matrix_B);
	free(matrix_C);

}

void *rank2TensorMultPThreads(void* arg)
{
	int thread_id = *((int *) arg);

	for(int index = thread_id; index <= MAT_SQUARE; index += NUM_THREADS)
		indexMultiplication(index);

	pthread_exit(0);
}

void indexMultiplication(int index)
{
	int sum = 0;
	
	for(int row = 0, col = 0; row < MAT_LENGTH; row ++, col += MAT_LENGTH)
	{
		int row_offset = ((index / MAT_LENGTH) * MAT_LENGTH);
		int col_offset = (index % MAT_LENGTH);
		sum += matrix_A[row + row_offset] * matrix_B[col + col_offset];
	}

	matrix_C[index] =  sum;
}
