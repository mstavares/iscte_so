#include "pauta.h"

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

void le_pauta_bin(aluno_t pauta [], int size_pauta) {
  aluno_t aluno;
  FILE *file = fopen("pauta.dat", "r");
  so_exit_on_null(file, "Não foi possível abrir o ficheiro 'pauta.dat' para leitura.");

  for(int i = 0; i < size_pauta; i++) {
    if(fread(&aluno, sizeof(aluno), 1, file) > 0) {
      pauta[i] = aluno;
    }
  }
}

int main() {
  aluno_t pauta [TAMANHO_TURMA];

  for(int i = 0; i < TAMANHO_TURMA; i++) {
    pauta[i].num = ALUNO_INVALIDO;
  }

  le_pauta_bin(pauta, TAMANHO_TURMA);
  mostra_pauta(pauta, TAMANHO_TURMA);

  /*
  aluno_t aluno;
  
  FILE *file = fopen("pauta.dat", "r");
  so_exit_on_null(file, "Não foi possível abrir o ficheiro 'pauta.dat' para leitura.");

  int i = 0;
  while(fread(&aluno, sizeof(aluno), 1, file) > 0) {
    printf("%d %s %5.2f \n", aluno.num, aluno.nome, aluno.nota);
  }

  fclose(file);
  */
  
}