#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define MAT_LENGTH 3
#define MAT_SQUARE MAT_LENGTH*MAT_LENGTH
#define MAT_DEPTH 2

int matrix_A[2][9] = {{9,15,37,1,93,7,108,117,203},{1,90,3,66,7,43,8,3,5}};
int matrix_B[2][9] = {{115,197,6,7,5,11,113,19,17},{87,76,3,56,2,36,85,26,3}};
int matrix_C[2][9];

void rank3TensorMultOpenMP();
void rank2TensorMultOpenMP(int depth);
int indexMultiplication(int index, int depth);

void main(void)
{
	rank3TensorMultOpenMP();
}

void rank3TensorMultOpenMP()
{
	for(int depth = 0; depth < MAT_DEPTH; depth ++)
		rank2TensorMultOpenMP(depth);

	for(int depth = 0; depth < MAT_DEPTH; depth ++)
	{
		for(int index = 0; index < MAT_SQUARE; index ++)
		{
			printf("%d ",matrix_C[depth][index]);
			if(index % MAT_LENGTH == MAT_LENGTH - 1) printf("\n");
		}

		printf("\n");
	}
}


void rank2TensorMultOpenMP(int depth)
{
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int thread_id = omp_get_thread_num(); 
		int threads_given = omp_get_num_threads();

		for(int index = thread_id; index < MAT_SQUARE; index += threads_given)
			matrix_C[depth][index] = indexMultiplication(index, depth);
	}
}

int indexMultiplication(int index, int depth)
{
	int sum = 0;

	for(int row = 0, col = 0; row < MAT_LENGTH; row ++, col += MAT_LENGTH)
	{
		int row_offset = ((index / MAT_LENGTH) * MAT_LENGTH);
		int col_offset = (index % MAT_LENGTH);
		sum += matrix_A[depth][row + row_offset] * matrix_B[depth][col + col_offset];		
	}

	return sum;
}
