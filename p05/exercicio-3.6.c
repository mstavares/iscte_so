#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
  int matches = 0;
  char buffer [256];

  printf("Escreva a sua string \n");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strlen(buffer) - 1] = '\0'; 

  for(int i = 0; i < strlen(buffer); i++) {
    if(buffer[i] == ',') {
      matches++;
    }
  }

  printf("Encontrei %d virgulas \n", matches);

  for(int i = 0; i < strlen(buffer); i++) {
    printf("%c", toupper(buffer[i]));
  }

}