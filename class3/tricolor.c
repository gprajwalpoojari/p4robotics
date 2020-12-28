#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define N_TRITS 243
#define TRITS 3
#define TRITS_PER_BYTE 5
char *trit_encodings[N_TRITS];

int main(void) {
    // at the very beginning of your program, making the table
    for (int i = 0; i < N_TRITS; i++) {
        trit_encodings[i] = calloc(sizeof(char), TRITS_PER_BYTE + 1);
    }
    char ch[3] = {' ', ':', '@'};
    for (int i = 0; i < N_TRITS; i++) {
        int count = i;
      for (int j = TRITS_PER_BYTE - 1; j >= 0; j--) {
          int k = count / pow(TRITS, j);
          trit_encodings[i][j] = ch[k];
          count = count - pow(TRITS, j) * k;
      }
    }
    int img_rows = 40;
    int row_length = 18;
    FILE *f = fopen("img.bin", "rb");
    for (int i = 0; i < img_rows; i++) {
      for (int j = 0; j < row_length; j++) {
        char c = fgetc(f);
        printf("%s", trit_encodings[(uint8_t)c]);
      }
      printf("\n");
    }
    // at the very end of your program, cleaning up memory
    for (int i = 0; i < N_TRITS; i++) {
        free(trit_encodings[i]);
    }
    return 0;
}
