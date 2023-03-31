#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define M 1500
#define P 500
#define N 300

int main(int argc, char const *argv[])
{
	int **matrix1,**matrix2,**result;
	matrix1=(int**) malloc (M*sizeof(int*));
	matrix2=(int**) malloc (P*sizeof(int*));
	result=(int**) malloc (M*sizeof(int*));

	for (int i = 0; i < M; ++i)
	{
		matrix1[i]=(int *)malloc(P*sizeof(int));
		result[i]=(int *)malloc(N*sizeof(int));
	}
	for (int i = 0; i < P; ++i)
	{
		matrix2[i]=(int *)malloc(N*sizeof(int));
	}
	//fill matrices with numbers
	for (int i = 0; i < M; ++i)
	{
		for(int j=0;j<P;j++){
			matrix1[i][j]=rand()%20;
		}
	}
	for (int i = 0; i < P; ++i)
	{
		for(int j=0;j<N;j++){
			matrix2[i][j]=rand()%20;
		}
	}
	double begin,end,sum;
	int i,j,k;
	begin=omp_get_wtime();
	#pragma omp parallel for private(i,j,k,sum) shared(matrix1,matrix2,result)
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			sum=0.0;
			for(int k=0;k<P;k++){
				sum+=matrix1[i][k]*matrix2[k][j];
			}
			result[i][j]=sum;
		}
	}
	end=omp_get_wtime();
	printf("Time elapsed: %f seconds\n", end - begin);


	return 0;
}
