#include<stdio.h>
#include<stdlib.h>

char char1;
int int1;
double doubles[3];
int main (void) {
  int distance = (long)&char1 - (long)&int1;
  printf("%p\n", (void *)&char1);
  printf("%p\n", (void *)&int1);
  printf("%i\n", distance);
  printf("%p\n", doubles);
  for (int i = 0; i < 3; i++) {
    printf("%p\n", (void *)&doubles[i]);
  }
  printf("%li\n", (void *)&doubles[0] - (void *)&doubles[1]);
  printf("%li\n\n", (long)&doubles[0] - (long)&doubles[1]);

  char char2;
  int int2;
  float floats[3];
  int dist = (long)&char2 - (long)&int2;
  printf("%p\n", (void *)&char2);
  printf("%p\n", (void *)&int2);
  printf("%i\n", dist);
  printf("%p\n", floats);
  for (int i = 0; i < 3; i++) {
    printf("%p\n", (void *)&floats[i]);
  }
  printf("%li\n", (void *)&floats[0] - (void *)&floats[1]);
  printf("%li\n\n", (long)&floats[0] - (long)&floats[1]);

  void *mem = malloc(1); // ask for memory
  printf("%p\n", mem); // memory is already "given" to us as an address!
  free(mem); // give memory back
}
