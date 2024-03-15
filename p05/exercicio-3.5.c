#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int idade;
  char nome [20], apelido [20];
  char completo [40];
  char buffer [10];

  printf("Escreva o seu nome ");
  fgets(nome, sizeof(nome), stdin);
  nome[strlen(nome) - 1] = '\0';

  printf("Escreva o seu apelido ");
  fgets(apelido, sizeof(apelido), stdin);
  apelido[strlen(apelido) - 1] = '\0';

  printf("Escreva a sua idade ");
  fgets(buffer, sizeof(buffer), stdin);
  idade = atoi(buffer);

  sprintf(completo, "%s-%s", nome, apelido);
  printf("%s \n", completo);

  if(strcmp(completo, "ISCTE-IUL") == 0) {
    printf("Nice :)");
  }

}