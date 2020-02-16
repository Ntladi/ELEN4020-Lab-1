#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define MAT_LENGTH 3
#define MAT_SQUARE MAT_LENGTH*MAT_LENGTH

int matrix_A[MAT_SQUARE] = {9,15,37,1,93,7,108,117,203};
int matrix_B[MAT_SQUARE] = {115,197,6,7,5,11,113,19,17};
int matrix_C[MAT_SQUARE];

void rank2TensorMultOpenMP();
int indexMultiplication(int index);

void main(void)
{
	rank2TensorMultOpenMP();	
}

void rank2TensorMultOpenMP()
{
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int thread_id = omp_get_thread_num(); 
		int threads_given = omp_get_num_threads();

		for(int index = thread_id; index < MAT_SQUARE; index += threads_given)
			matrix_C[index] = indexMultiplication(index);
	}

	for(int index = 0; index < MAT_SQUARE; index ++)
	{
		printf("%d ",matrix_C[index]);
		if(index % MAT_LENGTH == MAT_LENGTH - 1) 
			printf("\n");
	}
}

int indexMultiplication(int index)
{
	int sum = 0;

	for(int row = 0, col = 0; row < MAT_LENGTH; row ++, col += MAT_LENGTH)
	{
		int row_offset = ((index / MAT_LENGTH) * MAT_LENGTH);
		int col_offset = (index % MAT_LENGTH);
		sum += matrix_A[row + row_offset] * matrix_B[col + col_offset];		
	}
	return sum;
}
