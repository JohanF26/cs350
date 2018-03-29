#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

cond_t empty, fill;
mutex_t mutex;

void put(int value){
  assert(count == 0);
  count = 1;
  buffer = value;
}

int get() {
  assert(count == 1);
  count = 0;
  return buffer;
}

void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    pthread_mutex_lock(&mutex);
    while (count == 1)
      pthread_cond_wait(&empty, &mutex);
    put(i);
    pthread_cond_signal(&fill);
    pthread_mutex_unlock(&mutex);
  }
}

void *consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    pthread_mutex_lock(&mutex);
    while (count == 0)
      pthread_cond_wait(&fill, &mutex);
    int tmp = get();
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);
    printf("%d\n", tmp);
  }
}

int main(int argc, char *argv[]){
  printf("parent: begin\n");
  pthread_t prod;
  pthread_t cons;
  pthread_create(&prod, NULL, producer, 5);
  pthread_create(&cons, NULL, consumer, 5);
  thr_join();
  printf("parent: end\n");
  return 0;
}
