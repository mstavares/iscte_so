#include <stdio.h>
#include <stdlib.h>

int main() {

  int altura, largura = 0;
  char buffer [10];

  printf("Escreva a altura do rectangulo: ");
  fgets(buffer, sizeof(buffer), stdin);
  altura = atoi(buffer);

  printf("Escolhida altura de: %d \n", altura);

  printf("Escreva a largura do rectangulo: ");
  fgets(buffer, sizeof(buffer), stdin);
  largura = atoi(buffer);

  printf("Escolhida largura de: %d \n\n", largura);

  for(int i = 0; i < altura; i++) {
    for(int k = 0; k < largura; k++) {
      if(i == 0 || i == altura - 1) {
        printf("*");
      } else if(k == 0 || k == largura - 1) {
        printf("*");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }

}