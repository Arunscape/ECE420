/* Program 1 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_function(void *arg) {
  int *b = (int *)malloc(sizeof(int));
  *b = 10;
  pthread_exit((void *)b);
}

int main() {
  pthread_t thread_id;
  int *status;

  pthread_create(&thread_id, NULL, &thread_function, NULL);

  pthread_join(thread_id, (void **)&status);

  printf("The worker thread has returned the status %d\n", *status);
  pthread_exit(NULL);
}
