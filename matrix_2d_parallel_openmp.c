#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 1
#define MAT_LENGTH 10
#define MAT_SQUARE MAT_LENGTH*MAT_LENGTH

int matrix_A[MAT_SQUARE] = {21,5,4,99,9,44,99,10,88,75,
77,43,9,66,45,95,72,59,74,66,
90,65,8,3,86,45,76,8,1,76,
4,7,5,8,43,78,54,8,6,9,
6,5,22,7,5,9,2,8,4,99,
65,44,89,5,87,14,732,64,8,5,
86,43,78,54,67,80,55,7,99,4,
78,2,667,3,775,2,66,3,55,3,
66,3,8,4,76,46,874,6,43,5522,
69,7,3,69,65,12,48,43,665,2};

int matrix_B[MAT_SQUARE] = {48,45,77,33,77,5,32,5,96,3,
58,67,5487,3,45,53,67,4,65,87,
45,98,132,78,9,45,764,77,33,75,
54,77,44,77,44,77,56,34,1,76,
45,9,567,54,89,45,77,456,632,56,
54,542,65,22,87,643,9,32,83,87,
38,56,8667,96,55,58,675,86,12,78,
4,7,56,22,98,345,23,38,53,6,
36,96,42,75,24,78,53,75,23,35,
38,13,74,42,78,24,75,53,85,53};

int matrix_C[MAT_SQUARE];

void rank2TensorMultOpenMP();
int indexMultiplication(int index);
void printMatrix();

void main(void)
{
	rank2TensorMultOpenMP();
	printMatrix();
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

void printMatrix()
{
	for(int index = 0; index < MAT_SQUARE; index ++)
	{
		printf("%d ",matrix_C[index]);
		if(index % MAT_LENGTH == MAT_LENGTH - 1) 
			printf("\n");
	}	
}
