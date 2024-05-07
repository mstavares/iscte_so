#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "../include/so_utils.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm/h>

#define NR_ALUNOS 5
#define IPC_KEY 0x0a123456

typedef struct {
  int numero;
  char nome [99];
  float nota;
} aluno_t;

#endif // __DEFINES_H__