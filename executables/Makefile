all: openmp_2d openmp_3d pthreads_2d pthreads_3d

openmp_2d: ../src/matrix_2d_openmp.c
	gcc ../src/matrix_2d_openmp.c -fopenmp -o openmp_2d

openmp_3d: ../src/matrix_3d_openmp.c
	gcc ../src/matrix_3d_openmp.c -fopenmp -o openmp_3d

pthreads_2d: ../src/matrix_2d_pthreads.c
	gcc ../src/matrix_2d_pthreads.c -lpthread -o pthreads_2d

pthreads_3d: ../src/matrix_3d_pthreads.c
	gcc ../src/matrix_3d_pthreads.c -lpthread -o pthreads_3d

clean:
	rm openmp_2d openmp_3d pthreads_2d pthreads_3d
