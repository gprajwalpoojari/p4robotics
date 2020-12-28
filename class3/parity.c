#include<stdio.h>
#include<stdbool.h>
#include<string.h>

int main(int argc, char **argv) {
  if (argc <= 2) {
    bool parity = 0;
    if (argc == 2) {
      char *str = argv[1];
      for (int i = 0, n = strlen(str); i < n; i++) {
        char c = *(str + i);
        for (int j = 0; j < 8; j++) {
            parity = parity ^ (c & 0x01);
            c = c >> 1;
        }
      }
    }
    printf("%i\n", parity);
  }
  else {
    fprintf(stderr, "usage: ./parity [<text>]\n");
  }
  return 0;
}
