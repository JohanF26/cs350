#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

cond_t cond;
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
    pthread_mutex_lock(&mutex); // p1
    while (count == 1) // p2
      pthread_cond_wait(&cond, &mutex); // p3
    put(i); // p4
    pthread_cond_signal(&cond); // p5
    pthread_mutex_unlock(&mutex); // p6
  }
}

void *consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    pthread_mutex_lock(&mutex); // c1
    while (count == 0) // c2
      pthread_cond_wait(&cond, &mutex); // c3
    int tmp = get(); // c4
    pthread_cond_signal(&cond); // c5
    pthread_mutex_unlock(&mutex); // c6
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
