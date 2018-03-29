#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value) {
  buffer[fill_ptr] = value;
  fill_ptr = (fill_ptr + 1) % MAX;
  count++;
}

int get() {
  int tmp = buffer[use_ptr];
  use_ptr = (use_ptr + 1) % MAX;
  count--;
  return tmp;
}

cond_t empty, fill;
mutex_t mutex;

void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    pthread_mutex_lock(&mutex); // p1
    while (count == MAX) // p2
      pthread_cond_wait(&empty, &mutex); // p3
    put(i); // p4
    pthread_cond_signal(&fill); // p5
    pthread_mutex_unlock(&mutex); // p6
  }
}

void *consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    pthread_mutex_lock(&mutex); // c1
    while (count == 0) // c2
      pthread_cond_wait(&fill, &mutex); // c3
    int tmp = get(); // c4
    pthread_cond_signal(&empty); // c5
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

//
