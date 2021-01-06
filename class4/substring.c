#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char file_buffer[64*1024];

char *get_context(char *ptr, char *key, int n_lines) {
  if (n_lines == 0) {
    return (ptr - strlen(key));
  }
  char *temp = ptr;
  for (int i = 0; i < n_lines; i++) {
    while (*temp != '\n' && temp != file_buffer) {
      temp--;
    }
    if (*temp == '\n') {
      temp--;
    }
  }
  if (temp <= file_buffer) {
    return file_buffer;
  }
  return (temp + 2);
}
int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s <file> <key> <lines before>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "Could not open %s: ", argv[1]);
        perror("");
        return 1;
    }
    int bytes_read = fread(file_buffer, 1, sizeof(file_buffer) - 1, f);
    if (!feof(f)) {
        fprintf(stderr, "Could not read entire file. Is it too big?\n");
        return 1;
    }
    fclose(f);
    // we want this to be a null-treminated string,
    // but fread just reads the file as binary, so we add it ourselves
    file_buffer[bytes_read] = '\0';
    char *key = argv[2];
    int n_lines = atoi(argv[3]);
    char *ptr = strstr(file_buffer, key);
    while (ptr != NULL) {
      ptr += strlen(key);
      char *start = get_context(ptr, key, n_lines);
      while (start != ptr) {
        printf("%c", *start);
        start++;
      }
      printf("\n\n");
      ptr = strstr(ptr, key);
    }
    return 0;
  }
