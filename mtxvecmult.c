#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/* Global variables */
int     thread_count;
int     m, n;
double* A;
double* x;
double* y;

/* Function declarations */
void read_matrix(double A[], int m, int n);
void read_vector(double x[], int n);
void print_matrix(double A[], int m, int n);
void print_vector(double y[], int m);
void mat_vect(void* rank);

int main(int argc, char* argv[]) {
	pthread_t* thread_ids;
	thread_count = strtol(argv[1], NULL, 10);
	thread_ids = (pthread_t*)malloc(thread_count * sizeof(pthread_t));

	printf("Enter m and n\n");
	scanf("%d%d", &m, &n);

	A = (double*)malloc(m * n * sizeof(double));
	x = (double*)malloc(n * sizeof(double));
	y = (double*)malloc(m * sizeof(double));

	read_matrix(A, m, n);
	print_matrix(A, m, n);

	read_vector(x, n);
	print_vector(x, n);

	for (long thread = 0; thread < thread_count; thread++) {
		pthread_create(&thread_ids[thread], NULL, (void* (*)(void*))mat_vect, (void*)thread);
	}

	for (long thread = 0; thread < thread_count; thread++) {
		pthread_join(thread_ids[thread], NULL);
	}

	print_vector(y, m);

	free(A);
	free(x);
	free(y);
	free(thread_ids);

	return 0;
}

void read_matrix(double A[], int m, int n) {
	srand(time(NULL));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			A[i * n + j] = rand() / (double) RAND_MAX * 10;
		}
	}
}

void read_vector(double x[], int n) {
	srand(time(NULL) / 3753);
	for (int i = 0; i < n; i++) {
		x[i] = rand() / (double) RAND_MAX * 10;
	}
}

void mat_vect(void* rank) {
	long thread_rank = (long)rank;
	int local_m = m / thread_count;
	int first_row = thread_rank * local_m;
	int last_row = (thread_rank + 1) * local_m - 1;

	for (int i = first_row; i <= last_row; i++) {
		y[i] = 0.0;
		for (int j = 0; j < n; j++) {
			y[i] += A[i * n + j] * x[j];
		}
	}
}

void print_matrix(double A[], int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			printf("%4.1f ", A[i*n + j]);
		printf("\n");
	}
}

void print_vector(double y[], int m) {
	for (int i = 0; i < m; i++)
		printf("%4.1f ", y[i]);
	printf("\n");
}