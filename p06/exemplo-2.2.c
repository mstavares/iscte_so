#include "pauta.h"
#include <stdlib.h>

void apaga_aluno(aluno_t pauta [], int size_pauta, int numero_aluno) {
  for(int i = 0; i < size_pauta; i++) {
    if(pauta[i].num == numero_aluno) {
      pauta[i].num = ALUNO_INVALIDO;
      return;
    }
  }

  fprintf(stderr, "%s %d %s \n", ">> O aluno com o numero", numero_aluno, "nao foi encontrado");
}

void adiciona_aluno(aluno_t pauta [], int size_pauta, aluno_t *aluno) {
  for(int i = 0; i < size_pauta; i++) {
    if(pauta[i].num < 0) {
      pauta[i] = *aluno;
      return;
    }
  }

  fprintf(stderr, ">> Nao existem vagas disponiveis na pauta \n");
}

aluno_t novo_aluno() {
  aluno_t aluno;
  char buffer[50];

  printf("Escreva o nome do aluno: ");
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strlen(buffer) - 1] = '\0';
  strcpy(aluno.nome, buffer);

  printf("Escreva o numero do aluno: ");
  fgets(buffer, sizeof(buffer), stdin);
  aluno.num = atoi(buffer);

  printf("Escreva a nota do aluno: ");
  fgets(buffer, sizeof(buffer), stdin);
  aluno.nota = atoi(buffer);
  
  return aluno;
}

void mostra_pauta(aluno_t pauta [], int size_pauta) {
  int alunos_inscritos = 0;
  
  for(int i = 0; i < size_pauta; i++) {
    if(pauta[i].num > 0) {
      alunos_inscritos++;
      printf("Aluno: Nº: %6d, Nome: %s, Nota: %5.2f \n", pauta[i].num, pauta[i].nome, pauta[i].nota);
    }
  }

  printf("# alunos inscritos: %d \n", alunos_inscritos);
}

int main() {
  aluno_t pauta [TAMANHO_TURMA], aluno1;

  for(int i = 0; i < TAMANHO_TURMA; i++) {
    pauta[i].num = ALUNO_INVALIDO;
  }

  strcpy(aluno1.nome, "Manuel Fernandes");
  aluno1.num = 23500;
  aluno1.nota = 19.5;

  pauta[0] = aluno1;

  mostra_pauta(pauta, TAMANHO_TURMA);
  
  aluno_t aluno2 = novo_aluno();
  adiciona_aluno(pauta, TAMANHO_TURMA, &aluno2);
  mostra_pauta(pauta, TAMANHO_TURMA);
  apaga_aluno(pauta, TAMANHO_TURMA, 100);
  mostra_pauta(pauta, TAMANHO_TURMA);
}