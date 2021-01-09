#include<stdio.h>
#include<stdlib.h>

typedef struct vector {
  size_t size;
  size_t capacity;
  int *data;
} vector_t;

vector_t vector_create() {
  vector_t vec;
  vec.size = 0;
  vec.capacity = 8;
  vec.data = malloc(sizeof(*(vec.data)) * vec.capacity);
  return vec;
}

void vector_append (vector_t *vec, int value) {
  if (vec->size == vec->capacity) {
    vec->capacity *= 2;
    vec->data = realloc(vec->data, sizeof(*(vec->data)) * vec->capacity);
  }
  vec->data[(vec->size)++] = value;
}

int main (int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: ./golomb <max golomb number>\n");
    return 1;
  }
  vector_t vec = vector_create();
  vector_append(&vec, 1);
  vector_append(&vec, 2);
  vector_append(&vec, 2);
  for (int i = 3, n = atoi(argv[1]); i <= n; i++) {
    int s = vec.data[i - 1];
    for (int j = 0; j < s; j++) {
      vector_append(&vec, i);
    }
  }
  if (atoi(argv[1]) >= 2) {
    for (int i = vec.size - 1; i >= 0; i--) {
      printf("%i\n", vec.data[i]);
    }
  }
  else if (atoi(argv[1]) == 1){
      printf("%i\n", vec.data[0]);
  }

  return 0;
}
