#include <stdio.h>
#include <time.h>

#define M 1500
#define P 500
#define N 300

int matrix1[M][P];
int matrix2[P][N];
int result[M][N];

int main()
{
  
    int i, j, k;

    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            matrix1[i][j] = i + j;
        }
    }
    for (i = 0; i < P; i++) {
        for (j = 0; j < N; j++) {
            matrix2[i][j] = i - j;
        }
    }

    clock_t start = clock();
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < P; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    clock_t end = clock();
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
