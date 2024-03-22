#include "pauta.h"
#include <stdlib.h>

void adiciona_aluno(aluno_t pauta [], int size_pauta, aluno_t *aluno) {
  for(int i = 0; i < size_pauta; i++) {
    if(pauta[i].num == ALUNO_INVALIDO) {
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

void grava_pauta(aluno_t pauta [], int size_pauta) {
  FILE *file = fopen ("pauta.csv", "a");
  so_exit_on_null(file, "Não foi possível abrir o ficheiro 'pauta.csv' para escrita.");

  for(int i = 0; i < size_pauta; i++) {
    if(pauta[i].num != ALUNO_INVALIDO) {
      fprintf(file, "%d,%s,%5.2f", pauta[i].num, pauta[i].nome, pauta[i].nota);
      if(i + 1 <= size_pauta && pauta[i + 1].num != ALUNO_INVALIDO) {
        fprintf(file, "\n");
      }
    }
  }

  fclose(file);
}

int main() {
  aluno_t pauta [TAMANHO_TURMA];

  for(int i = 0; i < TAMANHO_TURMA; i++) {
    pauta[i].num = ALUNO_INVALIDO;
  }

  aluno_t aluno = novo_aluno();
  adiciona_aluno(pauta, TAMANHO_TURMA, &aluno);

  aluno = novo_aluno();
  adiciona_aluno(pauta, TAMANHO_TURMA, &aluno);

  mostra_pauta(pauta, TAMANHO_TURMA);

  grava_pauta(pauta, TAMANHO_TURMA);
}