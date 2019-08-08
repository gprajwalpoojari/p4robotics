#include <stdlib.h>

char *trit_encodings[243];

int main(void) {
    for (int i = 0; i < 243; i++) {
        trit_encodings[i] = calloc(sizeof(char), 6);
    }
    return 0;
}
