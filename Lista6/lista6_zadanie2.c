#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

int rowsCalculated = 0;
pthread_mutex_t myMutex= PTHREAD_MUTEX_INITIALIZER;

struct matArgs {
    int rows;
    int columns;
    bool* mat1;
    bool* trans2;
    bool* outcome;
};

void fillMatrix(int rows, int columns, bool matrix[rows][columns]){
    for (int i=0;i<rows;i++){
        for (int j=0;j<columns;j++){
            matrix[i][j] = random()%2;
        }
    }
}

void printMatrix(int rows, int columns, bool matrix[rows][columns]){
    for (int i=0;i<rows;i++){
        for (int j=0;j<columns;j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void transposeMatrix(int rows, int columns, bool matrix[rows][columns], bool transposition[columns][rows]){
    for (int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            transposition[j][i] = matrix[i][j];
        }
    }
}

void *calculateRow(void *arguments){
    struct matArgs *args = arguments;
    while (rowsCalculated < args->rows){
        pthread_mutex_lock(&myMutex);
        if (rowsCalculated >= args->rows){
            pthread_mutex_unlock(&myMutex);
            break;
        }
        int row = rowsCalculated;
        rowsCalculated++;
        pthread_mutex_unlock(&myMutex);
        for (int i=0;i<args->rows;i++){
            bool dot = false;
            for (int j=0;j<args->columns;j++){
                dot = dot || (*(args->mat1 + row*args->columns + j) && *(args->trans2 + i*args->columns + j));
                if (dot) break;
            }
            *(args->outcome + row*args->rows + i) = dot;
        }
        
    }
    return NULL;
}

void multiplyMatrices(int rows, int columns, int threads, bool* mat1, bool* trans2, bool* outcome){
    pthread_t thread[threads];
    struct matArgs args;
    args.columns = columns;
    args.rows = rows;
    args.mat1 = mat1;
    args.trans2 = trans2;
    args.outcome = outcome;
    struct matArgs *arguments = &args;
    pthread_mutex_lock(&myMutex);
    for (int i=0;i<threads;i++){
        if ( pthread_create(&thread[i], NULL, calculateRow, arguments)){
            printf("nie udalo sie odpalic watku :c");
            abort();
        }
    }
    pthread_mutex_unlock(&myMutex);
    for (int i=0;i<threads;i++){
        if (pthread_join(thread[i], NULL)){
            printf("cos sie popsulo po drodze :c");
            abort();
        }
    }
}

int main(){
    int rows, columns, threads;
    scanf("%d", &rows);
    scanf("%d", &columns);
    scanf("%d", &threads);

    bool mat1[rows][columns];
    bool mat2[columns][rows];
    bool trans2[rows][columns];
    bool outcome[rows][rows];

    fillMatrix(rows, columns, mat1);
    fillMatrix(columns, rows, mat2);
    transposeMatrix(columns, rows, mat2, trans2);

    printf("\nMacierz 1\n");
    printMatrix(rows, columns, mat1);
    printf("Macierz 2\n");
    printMatrix(columns, rows, mat2);
    printf("Transpozycja macierzy 2\n");
    printMatrix(rows, columns, trans2);

    multiplyMatrices(rows, columns, threads, *mat1, *trans2, *outcome);
    printf("Wynik\n");
    printMatrix(rows, rows, outcome);
}