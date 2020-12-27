#include <stdio.h>

int main(void) {
    printf("Enter a number to factorize:\n");
    int number = 0;
    int factor = 2;
    int vals_read = scanf("%d", &number);
    if (vals_read != 1) {
        fprintf(stderr, "Invalid input. Please enter a number.\n");
        return 1;
    }
    if (number <= 0) {
      fprintf(stderr, "Invalid input. Please enter a number greater than zero.\n");
      return 1;
    }
    printf("Prime Factors:\n");
    while (number != 1) {
      if (number % factor == 0) {
        printf("%d\n", factor);
        number = number / factor;
      }
      else {
        factor++;
      }
    }
    return 0;
}
