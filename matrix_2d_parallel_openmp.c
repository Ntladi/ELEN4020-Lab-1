#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 1

void main(void)
{
	int matrix_A[9] = {9,15,37,1,93,7,108,117,203};
	int matrix_B[9] = {115,197,6,7,5,11,113,19,17};
	int matrix_C[9];

	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int thread_id = omp_get_thread_num(); 
		int threads_given = omp_get_num_threads();

		for(int index=thread_id; index<9; index+=threads_given)
		{
			int sum = 0;

			for(int row=0, col=0; row<3; row++, col+=3)
			{
				int row_offset = ((index/3)*3);
				int col_offset = (index%3);
				sum += matrix_A[row + row_offset] * matrix_B[col + col_offset];		
			}

			matrix_C[index] = sum;

			//printf("sum = %d, ", sum);
			//printf("thread id = %d, ", thread_id);
			//printf("index id = %d \n", t);
		}
	
	}

	for(int i=0; i<9; i++)
	{
		printf("%d ",matrix_C[i]);
		if(i%3==2) printf("\n");
	}

	


	
}
