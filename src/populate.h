#ifndef POPULATE_H
#define POPULATE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void populate_2D(int *mat_A, int *mat_B, int length);
void populate_3D(int **mat_A_3D, int **mat_B_3D, int length, int depth);
void print2D(int *mat, int length);
void print3D(int **mat, int length, int depth);

void populate_2D(int *mat_A, int *mat_B, int length)
{
	for (int i = 0; i < length*length; ++i)
	{
		mat_A[i] = rand()%20;
		mat_B[i] = rand()%20;
	}
}

void populate_3D(int **mat_A_3D, int **mat_B_3D, int length, int depth)
{
	for(int i = 0; i < depth; i ++)
	{
		populate_2D(mat_A_3D[i],mat_B_3D[i],length);
	}
}

void print2D(int *mat, int length)
{
	for (int index = 1; index <= length*length; index++)
	{
		printf("%d ", mat[index-1]);

		if (index%length == 0)
			printf(" \n");
	}

	printf(" \n");	
}

void print3D(int **mat, int length, int depth)
{
	for (int index = 0; index < depth; index++)
	{
		print2D(mat[index],length);
	}
}

#endif
