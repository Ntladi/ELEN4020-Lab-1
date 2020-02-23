#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "populate.h"

int NUM_THREADS;
int MAT_LENGTH;
int MAT_SQUARE;

int *matrix_A;
int *matrix_B;
int *matrix_C;

void rank2TensorMultOpenMP();
void indexMultiplication(int index);

void main(int argc, char* argv[])
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

	rank2TensorMultOpenMP();

	// print2D(matrix_A, MAT_LENGTH);
	// print2D(matrix_B, MAT_LENGTH);
	// print2D(matrix_C, MAT_LENGTH);

	free(matrix_A);
	free(matrix_B);
	free(matrix_C);
}

void rank2TensorMultOpenMP()
{
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int thread_id = omp_get_thread_num(); 
		int threads_given = omp_get_num_threads();

		for(int index = thread_id; index < MAT_SQUARE; index += threads_given)
			indexMultiplication(index);
	}


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
	matrix_C[index] = sum;
}
