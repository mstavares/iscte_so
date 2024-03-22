#include "pauta.h"
#include <stdlib.h>

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

void le_pauta(aluno_t pauta [], int size_pauta) { 
  aluno_t aluno;
  char buffer [256];
  FILE *file = fopen("pauta.csv", "r");
  so_exit_on_null(file, "Não foi possível abrir o ficheiro 'pauta.csv' para leitura.");

  for(int i = 0; i < size_pauta; i++) {
    if(fscanf(file, "%d,%[^,],%f\n", &aluno.num, aluno.nome, &aluno.nota) < 0) {
      break;
    }

    pauta[i] = aluno;
  }

  fclose(file);
}

int main() {
  aluno_t pauta [TAMANHO_TURMA];

  for(int i = 0; i < TAMANHO_TURMA; i++) {
    pauta[i].num = ALUNO_INVALIDO;
  }

  le_pauta(pauta, TAMANHO_TURMA);
  mostra_pauta(pauta, TAMANHO_TURMA);

  /*
  char linha[100];
  FILE *f = fopen("pauta.csv", "r");
  so_exit_on_null(file, "Não foi possível abrir o ficheiro 'pauta.csv' para leitura.");

  int i = 0;
  whilte(so_gets(linha, sizeof(linha), f) != NULL) {
    printf("Linha %d: %s", i++, linha);
  }

  flose(f);
  */
}