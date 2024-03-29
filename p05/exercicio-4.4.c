#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUANTIDADE_DE_NUMEROS 10

int procuraMaior(int numeros [], int numeros_size) {
  int maior = 0;

  for(int i = 0; i < numeros_size - 1; i++) {
    if(numeros[i] > maior) {
      maior = numeros[i];
    }
  }

  return maior;
}

int main() {

  int numeros [QUANTIDADE_DE_NUMEROS];
  char buffer [10];

  for(int i = 0; i < QUANTIDADE_DE_NUMEROS; i++) {
    printf("Escreva o seu %dº número inteiro: ", i + 1);
    fgets(buffer, sizeof(buffer), stdin);
    numeros[i] = atoi(buffer);
  }

  printf("\nVou imprimir os números introduzidos pela ordem inversa \n");

  for(int i = QUANTIDADE_DE_NUMEROS - 1; i >= 0; i--) {
    printf("%d ", numeros[i]);
  }

  int maior = procuraMaior(numeros, QUANTIDADE_DE_NUMEROS);
  printf("\nO maior número registado é: %d", maior);
}
''