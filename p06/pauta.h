#ifndef __PAUTA_H__
#define __PAUTA_H__

#include "../include/so_utils.h" 

#define TAMANHO_TURMA 10    // Tamanho máximo da turma de alunos
#define ALUNO_INVALIDO -1   // Valor de número de aluno correspondente a "Aluno inválido"

typedef struct {
  int num;
  char nome[100];
  float nota;
} aluno_t;

#endif	// __PAUTA_H__