#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Global variables */
int thread_count;
int m, n;
double *A;
double *x;
double *y;

/* Parallel function */
void *Pth_mat_vect(void *rank);

/*------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
  long thread;
  pthread_t *thread_handles;

  thread_count = atoi(argv[1]);
  thread_handles = malloc(thread_count * sizeof(pthread_t));

  A = malloc(m * n * sizeof(double));
  x = malloc(n * sizeof(double));
  y = malloc(m * sizeof(double));

  /* Read A, x, m, n from a file (code omitted) */

  for (thread = 0; thread < thread_count; thread++)
    pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *)thread);

  for (thread = 0; thread < thread_count; thread++)
    pthread_join(thread_handles[thread], NULL);

  Print_vector("The product is", y, m);

  free(A);
  free(x);
  free(y);
  return 0;
} /* main */

void *Pth_mat_vect(void *rank) {
  long my_rank = (long)rank;
  int i, j;
  int local_m = m / thread_count;
  int my_first_row = my_rank * local_m;
  int my_last_row = (my_rank + 1) * local_m - 1;

  double local_row[local_m];
  for (i = 0; i < local_m; i++) {
    local_row[i] = 0.0;
    // update local variable multiple times
    for (j = 0; j < n; j++)
      local_row[i] += A[i * n + j] * x[j];
  }

  // update global once
  memcpy(y + my_first_row, &local_row, local_m * sizeof(double));
  return NULL;
} /* Pth_mat_vect */
