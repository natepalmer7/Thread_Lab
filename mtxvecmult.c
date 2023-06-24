#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Global variables */
int     thread_count; // the number of threads
int     m, n; // the dimensions of the matrix
double* A; // the input matrix
double* x; // the input vector
double* y;

/* Serial functions */
void read_matrix(double A[], int m, int n);
void read_vector(double x[], int n);
void print_matrix(double A[], int m, int n);
void print_vector(double y[], int m);

/* Parallel function */
void mat_vect(void* rank);

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   
	pthread_t* tids;

	//note: the second command line argument indicates the number of threads we wish to deploy
	thread_count = strtol(argv[1], NULL, 10); //"string to long"
	tids = malloc(thread_count*sizeof(pthread_t)); //make space for our thread ids

	printf("Enter m and n\n");	//ask for the dimensions of our matrix
	scanf("%d%d", &m, &n);

	A = malloc(m*n*sizeof(double)); // allocate memory for our input matrix A
	x = malloc(n*sizeof(double)); // allocate memory for our input vector x
	y = malloc(m*sizeof(double)); // allocate memory for our output vector y


	/* your task for the lab is following
	* 1) fill in the entries of A and x with random numbers 
    * 2) use pthreads to compute the matrix-vector product Ax = y where y is the result
    * remember from linear algebra that m X n * n x 1 = m x 1 */ 
   
	read_matrix(A, m, n);
	print_matrix(A, m, n);

	read_vector(x, n);
	print_vector(x, n);

	// use pthreads here to compute Ax
	// for completing this part, first assume that the number of threads equals m, the number of rows in your matrix A.
	// once you get that working, figure out how to divide the work amongst the threads when the number of threads is less than m.
   
	print_vector(y, m);

	free(A);
	free(x);
	free(y);
	free(tids);

	return 0;
}  /* main */


void read_matrix(double A[], int m, int n) {
	int i, j;
	for (i = 0; i < m; i++) 
		for (j = 0; j < n; j++)
		// here is where we should produce a random number for the i,j-th entry of A
		// note: A is *not* a 2-dimensional array, we have flattened it to be 1-dimensional.
} 


void read_vector(double x[], int n) {
	int   i;
	for (i = 0; i < n; i++) 
	// here is where we generate a random number for the ith entry of x
}  


/*------------------------------------------------------------------
 * Function:       mat_vect
 * Purpose:        Multiply an mxn matrix by an nx1 column vector
 * In arg:         rank
 * Global in vars: A, x, m, n, thread_count
 * Global out var: y
 */
void mat_vect(void* thread_num) {
	long my_num = (long) thread_num;		//this is a hack. what assumption have we made about the underlying architecture of the machine?
	// for the programming assignment you should not do this, i.e., you should create a struct and pass that struct in as an argument.	

	// here is where we need to implement the pthread's function
	// think about whether you need a mutex to carry out the operation Ax = y.    
}  /* mat_vect */


// print functions for your convenience

void print_matrix(double A[], int m, int n) {
	int   i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			printf("%4.1f ", A[i*n + j]);
		printf("\n");
	}
} 

void print_vector(double y[], int m) {
	int   i;
	for (i = 0; i < m; i++)
		printf("%4.1f ", y[i]);
	printf("\n");
} 
