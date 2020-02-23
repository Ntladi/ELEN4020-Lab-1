#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "populate.h"

int NUM_THREADS;
int MAT_LENGTH;
int MAT_SQUARE;

int *matrix_A;
int *matrix_B;
int *matrix_C;

void rank2TensorMultPThreads();
void *pThreadsPointer(void* arg);
void indexMultiplication(int index);

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		NUM_THREADS = atoi(argv[1]);
		MAT_LENGTH = atoi(argv[2]);
	}
	else
	{
		printf("No thread count or matrix length entered.\n");
		printf("The default values (threads = 1, length = 10)\n");
		printf("will be used instead\n\n");
		NUM_THREADS = 1;
		MAT_LENGTH = 10;
	}

	MAT_SQUARE = MAT_LENGTH*MAT_LENGTH;

	matrix_A = (int *)malloc(MAT_SQUARE * sizeof(int));
	matrix_B = (int *)malloc(MAT_SQUARE * sizeof(int));
	matrix_C = (int *)malloc(MAT_SQUARE * sizeof(int));

	populate_2D(matrix_A,matrix_B,MAT_LENGTH);

	rank2TensorMultPThreads();

	// print2D(matrix_A, MAT_LENGTH);
	// print2D(matrix_B, MAT_LENGTH);
	// print2D(matrix_C, MAT_LENGTH);

	free(matrix_A);
	free(matrix_B);
	free(matrix_C);

}

void rank2TensorMultPThreads()
{
	pthread_t threads[NUM_THREADS];
	int thread_ids[NUM_THREADS];

	for(int index = 0; index < NUM_THREADS; index ++)
	{
		thread_ids[index] = index;
		pthread_create(&threads[index], NULL,pThreadsPointer, &thread_ids[index]);
	}

	for(int index = 0; index < NUM_THREADS; index ++)
		pthread_join(threads[index], NULL);
}

void *pThreadsPointer(void* arg)
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
