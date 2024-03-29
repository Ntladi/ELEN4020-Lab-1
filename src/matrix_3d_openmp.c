#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "populate.h"

int NUM_THREADS;
int MAT_LENGTH;
int MAT_SQUARE;
int MAT_DEPTH;

int **matrix_A;
int **matrix_B;
int **matrix_C;

void rank3TensorMultOpenMP();
void rank2TensorMultOpenMP(int depth);
void indexMultiplication(int index, int depth);

void main(int argc, char* argv[])
{
	if(argc > 1)
	{
		NUM_THREADS = atoi(argv[1]);
		MAT_LENGTH = atoi(argv[2]);
		MAT_DEPTH = atoi(argv[2]);
	}
	else
	{
		printf("No thread count or matrix length entered.\n");
		printf("The default values (threads = 1, length = 10)\n");
		printf("will be used instead\n\n");
		NUM_THREADS = 1;
		MAT_LENGTH = 10;
		MAT_DEPTH = 10;
	}


	MAT_SQUARE = MAT_LENGTH*MAT_LENGTH;

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

	rank3TensorMultOpenMP();

	// printf("Matrix A\n");
	// print3D(matrix_A,MAT_LENGTH,MAT_DEPTH);
	// printf("Matrix B\n");
	// print3D(matrix_B,MAT_LENGTH,MAT_DEPTH);
	// printf("Matrix C\n");
	// print3D(matrix_C,MAT_LENGTH,MAT_DEPTH);

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

void rank3TensorMultOpenMP()
{
	for(int depth = 0; depth < MAT_DEPTH; depth ++)
		rank2TensorMultOpenMP(depth);
}


void rank2TensorMultOpenMP(int depth)
{
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int thread_id = omp_get_thread_num(); 
		int threads_given = omp_get_num_threads();

		for(int index = thread_id; index < MAT_SQUARE; index += threads_given)
			indexMultiplication(index, depth);
	}
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
