#include "defines.h"

int shm_create(int size) {
  #define ACCESS_PERMS 0600
  #define NO_FLAGS 0

  int id = shmget(IPC_KEY, size, NO_FLAGS);
  if(id < 0) {
    id = shmget(IPC_KEY, size, IPC_CREAT | IPC_EXCL | ACCESS_PERMS);
    so_exit_on_error(id, "Erro shmget Create");
  }
  so_debug("Criei a memória partilhada com key=0x%x e id=%d", IPC_KEY, id);
  return id;
}

aluno_t *shm_attach(int shm_id) {
  #define NEW_ADDRESS NULL
  #define NO_FLAGS 0

  aluno_t *turma = (aluno_t *) shmat(shm_id, NEW_ADDRESS, NO_FLAGS);
  so_exit_on_null(turma, "Erro shmat Attach");
  so_debug("A shared memory foi atribuida no endereço %p", turma);
  return turma;
}

void shm_view(aluno_t *turma, int nr_alunos) {
  so_debug("Conteúdo da shared memory:");
  for(int i = 0; i < nr_alunos; i++) {
    so_debug("Posição %2d: %6d | %-99s | %2.3f", i, turma[i].numero, turma[i].nome, turma[i].nota);
  }
}

void shm_init(aluno_t *turma, int nr_alunos) {
  for(int i = 0; i < nr_alunos; i++){
    turma[i].numero = ENTRADA_VAZIA;
    strncpy(turma[i].nome, "[sem nada]", sizeof(turma[i].nome));
    turma[i].nota = 0.0;
  }
}

aluno_t criar_aluno() {
  aluno_t aluno;
  char buffer[256];

  printf("Indique o número do aluno: ");
  fgets(buffer, sizeof(buffer), stdin);
  aluno.numero = atoi(buffer);

  printf("Indique o nome do aluno: ");
  fgets(aluno.nome, sizeof(aluno.nome), stdin);
  aluno.nome[strlen(aluno.nome) -1] = '\0';

  printf("Indique a nota do aluno: ");
  fgets(buffer, sizeof(buffer), stdin);
  aluno.nota = atof(buffer);

  return aluno;
}

int registar_aluno(aluno_t *turma, int nr_alunos, aluno_t novo_aluno) {
  #define ERROR -1

  for(int i = 0; i < nr_alunos; i++) {
    if(turma[i].numero == ENTRADA_VAZIA) {
      turma[i] = novo_aluno;
      return i;
    }
  }
  return ERROR;
}

int main() {
  #define NR_ALUNOS 5

  int shm_id = shm_create(sizeof(aluno_t) * NR_ALUNOS);
  aluno_t *turma = shm_attach(shm_id);
  shm_init(turma, NR_ALUNOS);
  shm_view(turma, NR_ALUNOS);

  aluno_t aluno = criar_aluno();
  int result = registar_aluno(turma, NR_ALUNOS, aluno);
  so_exit_on_error(result, "Erro registar aluno");

  shm_view(turma, NR_ALUNOS);

  return 0;
}