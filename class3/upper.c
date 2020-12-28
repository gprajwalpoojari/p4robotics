#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
    if (argc == 1) {
      fprintf(stderr, "Usage ./upper <text>\n");
    }
    else {
      for (int i = 1; i < argc; i++) {
        char *str = argv[i];
        for (int j = 0, n = strlen(str); j < n + 1; j++) {
          str[j] = toupper(str[j]);
        }
        printf("%s", str);
      }
      printf("\n");
    }
    return 0;
}
