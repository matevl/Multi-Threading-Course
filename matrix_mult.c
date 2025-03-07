#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/**
 * MatrixArgs is a struct to pass arguments to the thread function.
 */
typedef struct {
    int **matrixA;
    int **matrixB;
    int **matrixC;
    int start_row;
    int end_row;
    int size;
} MatrixArgs;

/**
 * Function executed by each thread to compute a portion of the result matrix.
 *
 * @param arg Pointer to MatrixArgs containing matrix data and row range.
 * @return NULL
 */
void* compute_matrix_rows(void* arg) {
    MatrixArgs* args = (MatrixArgs*)arg;
    for (int i = args->start_row; i < args->end_row; ++i) {
        for (int j = 0; j < args->size; ++j) {
            args->matrixC[i][j] = 0;
            for (int k = 0; k < args->size; ++k) {
                args->matrixC[i][j] += args->matrixA[i][k] * args->matrixB[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

/**
 * Function to compute the entire result matrix using a single thread.
 *
 * @param matrixA Pointer to the first input matrix.
 * @param matrixB Pointer to the second input matrix.
 * @param matrixC Pointer to the result matrix.
 * @param size Size of the matrices.
 */
void compute_matrix_single_thread(int** matrixA, int** matrixB, int** matrixC, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrixC[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

int main() {
    const int size = 1000; // Size of the matrices (e.g., 1000x1000)
    int **matrixA = malloc(size * sizeof(int*));
    int **matrixB = malloc(size * sizeof(int*));
    int **matrixC_single = malloc(size * sizeof(int*));
    int **matrixC_multi = malloc(size * sizeof(int*));

    // Allocate memory for the matrices
    for (int i = 0; i < size; ++i) {
        matrixA[i] = malloc(size * sizeof(int));
        matrixB[i] = malloc(size * sizeof(int));
        matrixC_single[i] = malloc(size * sizeof(int));
        matrixC_multi[i] = malloc(size * sizeof(int));
    }

    // Initialize matrices A and B with random values
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrixA[i][j] = rand() % 10; // Fill with random numbers
            matrixB[i][j] = rand() % 10;
        }
    }

    // Single-threaded matrix multiplication
    clock_t start_time_single = clock();
    compute_matrix_single_thread(matrixA, matrixB, matrixC_single, size);
    clock_t end_time_single = clock();
    double execution_time_single = ((double)(end_time_single - start_time_single)) / CLOCKS_PER_SEC;
    printf("Single-threaded execution time: %f seconds\n", execution_time_single);

    // Multithreaded matrix multiplication with fewer threads
    const int num_threads = 8; // Number of threads
    pthread_t threads[num_threads];
    MatrixArgs args[num_threads];
    int rows_per_thread = size / num_threads;

    clock_t start_time_multi = clock();

    // Create threads
    for (int i = 0; i < num_threads; ++i) {
        args[i].matrixA = matrixA;
        args[i].matrixB = matrixB;
        args[i].matrixC = matrixC_multi;
        args[i].start_row = i * rows_per_thread;
        args[i].end_row = (i == num_threads - 1) ? size : args[i].start_row + rows_per_thread;
        args[i].size = size;
        pthread_create(&threads[i], NULL, compute_matrix_rows, &args[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time_multi = clock();
    double execution_time_multi = ((double)(end_time_multi - start_time_multi)) / CLOCKS_PER_SEC;
    printf("Multithreaded execution time: %f seconds\n", execution_time_multi);

    // Free allocated memory
    for (int i = 0; i < size; ++i) {
        free(matrixA[i]);
        free(matrixB[i]);
        free(matrixC_single[i]);
        free(matrixC_multi[i]);
    }
    free(matrixA);
    free(matrixB);
    free(matrixC_single);
    free(matrixC_multi);

    return 0;
}
