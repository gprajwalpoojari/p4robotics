#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int encrypt_decrypt(char *command, char *password, char *text) {
  char encrypt[] = "encrypt";
  char decrypt[] = "decrypt";
  int encrypt_ = 0;
  int decrypt_ = 0;
  if (strcmp(command, encrypt) == 0) {
    encrypt_ = 1;
    decrypt_ = 0;
  }
  else if (strcmp(command, decrypt) == 0) {
    encrypt_ = 0;
    decrypt_ = 1;
  }
  else {
    fprintf(stderr, "expected command encrypt or decrypt. Got %s\n", command);
    return 1;
  }
  for (int i = 0, j = 0, n = strlen(text), l = strlen(password); i < n; i++, j = j % l) {
    if (tolower(password[j]) >= 'a' && tolower(password[j] <= 'z')) {
      if (tolower(text[i]) >= 'a' && tolower(text[i]) <= 'z') {
        char key = tolower(password[j]) - 'a';
        if (tolower(text[i] + (encrypt_ - decrypt_) * key) >= 'a' && tolower(text[i] + (encrypt_ - decrypt_) * key) <= 'z'){
          text[i] = text[i] + (encrypt_ - decrypt_) * key;
        }
        else {
          text[i] = text[i] + (encrypt_ - decrypt_) * (key - ('z' - 'a'));
        }
        j++;
      }
    }
    else {
      j++, i--;
    }
  }
  printf("%s\n", text);
  return 0;
}

int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "usage: ./cryptogram <encrypt|decrypt> <password> <text>\n");
    return 1;
  }
  int count = 0;
  for (int i = 0, l = strlen(argv[2]); i < l; i++) {
    if (tolower(argv[2][i]) >= 'a' && tolower(argv[2][i] <= 'z')) {
      count++;
    }
  }
  if (count == 0) {
    printf("%s\n", argv[3]);
    return 0;
  }
  return encrypt_decrypt(argv[1], argv[2], argv[3]);
}
