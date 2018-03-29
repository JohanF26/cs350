// how many bytes of the heap are free?
int bytesLeft = MAX_HEAP_SIZE;

// need lock and condition too
cond_t c;
mutex_t m;

void *
allocate(int size) {
  pthread_mutex_lock(&m);
  while (bytesLeft < size)
    pthread_cond_wait(&c, &m);
  void *ptr = ...; // get mem from heap
  bytesLeft -= size;
  pthread_mutex_unlock(&m);
  return ptr;
}

void free(void *ptr, int size) {
  pthread_mutex_lock(&m);
  bytesLeft += size;
  pthread_cond_signal(&c); // whom to signal??
  pthread_mutex_unlock(&m);
}
