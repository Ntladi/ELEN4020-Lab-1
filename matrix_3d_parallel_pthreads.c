#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "populate.h"

#define NUM_THREADS 1
#define MAT_LENGTH 5
#define MAT_SQUARE MAT_LENGTH*MAT_LENGTH
#define MAT_DEPTH 2

int **matrix_A;
int **matrix_B;
int **matrix_C;

struct IndexData 
{
	int depth;
	int thread_id;
};

void rank3TensorMultPThreads();
void *rank2TensorMultPThreads(void* arg);
void indexMultiplication(int index, int depth);

void main()
{
	matrix_A = (int **)malloc(MAT_DEPTH * sizeof(int*));
	matrix_B = (int **)malloc(MAT_DEPTH * sizeof(int*));
	matrix_C = (int **)malloc(MAT_DEPTH * sizeof(int*));

	for (int index = 0; index < MAT_DEPTH; index++)
	{
		matrix_A[index] = (int *)malloc(MAT_SQUARE*sizeof(int));
		matrix_B[index] = (int *)malloc(MAT_SQUARE*sizeof(int));
		matrix_C[index] = (int *)malloc(MAT_SQUARE*sizeof(int));
	}

	populate_3D(matrix_A,matrix_B,MAT_LENGTH,MAT_DEPTH);

	rank3TensorMultPThreads();

	printf("This is Matrix A\n");
	print3D(matrix_A,MAT_LENGTH,MAT_DEPTH);
	printf("This is Matrix B\n");
	print3D(matrix_B,MAT_LENGTH,MAT_DEPTH);
	printf("This is Matrix C\n");
	print3D(matrix_C,MAT_LENGTH,MAT_DEPTH);

	for (int index = 0; index < MAT_DEPTH; index++)
	{
		free(matrix_A[index]);
		free(matrix_B[index]);
		free(matrix_C[index]);
	}

	free(matrix_A);
	free(matrix_B);
	free(matrix_C);
}

void rank3TensorMultPThreads()
{
	for(int depth = 0; depth < MAT_DEPTH; depth ++)
	{
		pthread_t threads[NUM_THREADS];
		struct IndexData data[NUM_THREADS];

		for(int index = 0; index < NUM_THREADS; index ++)
		{
			data[index].thread_id = index;
			data[index].depth = depth;
			pthread_create(&threads[index], NULL, rank2TensorMultPThreads, &data[index]);
		}

		for (int index = 0; index < NUM_THREADS; index++)
			pthread_join(threads[index], NULL);
	}
}

void *rank2TensorMultPThreads(void* arg)
{
	struct IndexData data = *((struct IndexData *)arg);
	int thread_id = data.thread_id;
	int depth = data.depth;

	for (int index = thread_id; index <= MAT_SQUARE; index += NUM_THREADS)
		indexMultiplication(index, depth);
}

void indexMultiplication(int index, int depth)
{
	int sum = 0;

	for(int row = 0, col = 0; row < MAT_LENGTH; row ++, col += MAT_LENGTH)
	{
		int row_offset = ((index / MAT_LENGTH) * MAT_LENGTH);
		int col_offset = (index % MAT_LENGTH);
		sum += matrix_A[depth][row + row_offset] * matrix_B[depth][col + col_offset];		
	}

	matrix_C[depth][index] =  sum;
} 