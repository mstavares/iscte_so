#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("Numero de argumentos recebidos: %d \n", argc);

  for(int i = 0; i < argc; i++) {
    printf("%d -> %s -> %lu \n", i, argv[i], strlen(argv[i]));
  }

}