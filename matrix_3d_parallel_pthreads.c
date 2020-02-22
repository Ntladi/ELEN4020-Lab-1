#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 1
#define MAT_LENGTH 3
#define MAT_SQUARE MAT_LENGTH*MAT_LENGTH
#define MAT_DEPTH 2

int matrix_A[MAT_DEPTH][MAT_SQUARE] = {{1,4,2,6,44,2,77,2},{1,90,3,66,7,43,8,3,5}};
int matrix_B[MAT_DEPTH][MAT_SQUARE] = {{115,197,6,7,5,11,113,19,17},{87,76,3,56,2,36,85,26,3}};
int matrix_C[MAT_DEPTH][MAT_SQUARE];

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
	rank3TensorMultPThreads();

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



