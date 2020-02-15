#include <stdlib.h>
#include <stdio.h>

void main(void)
{
	int matrix_A[9] = {12,15,17,22,96,44,256,99,84};
	int matrix_B[9] = {77,69,54,21,4,33,62,74,11};
	int matrix_C[9]; 

	for(int index=0; index<9; index++)
	{
		int sum = 0;
		for(int row=0, col=0; row<3; row++, col+=3)
		{
			int row_offset = ((index/3)*3);
			int col_offset = (index%3);
			sum += matrix_A[row + row_offset] * matrix_B[col + col_offset];		
		}

		matrix_C[index] = sum;
	}

	for(int i=0; i<9; i++)
	{
		printf("%d ",matrix_C[i]);
		if(i%3==2) printf("\n");
	}
}
