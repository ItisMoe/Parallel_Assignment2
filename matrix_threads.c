#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define M 1500
#define P 500
#define N 300
#define NUM_THREADS 4

int matrix1[M][P];
int matrix2[P][N];
int result[M][N];

struct bounds
{
    int begin;
    int end;
};
void * matrixm(void * arg){
    struct bounds *c;
    c=(struct bounds*)arg;
    for (int i = c->begin; i < c->end; ++i)
    {
        for(int j=0;j<N;j++){
            for(int k=0;k<P;k++){
                result[i][j]+=matrix1[i][k]*matrix2[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

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
    pthread_t threads[NUM_THREADS];
    struct bounds c[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        c[i].begin=i*M/NUM_THREADS;
        c[i].end=c[i].begin+M/NUM_THREADS;
        if(i==NUM_THREADS-1){
            c[i].end=M;
        }
        pthread_create(&threads[i],NULL,matrixm,(void*)&c[i]);
    }
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(threads[i],NULL);
    }
    
    clock_t end = clock();
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", time_taken);
    pthread_exit(NULL);

    return 0;
}
