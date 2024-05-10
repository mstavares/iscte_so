#include "defines.h"

int sem_create(int nr_semaphores) {
  #define ACCESS_PERMS 0600
  #define IPC_GET 0

  int id = semget(IPC_KEY, 0, IPC_GET);
  if(id < 0) {
    int id = semget(IPC_KEY, nr_semaphores, IPC_CREAT | IPC_EXCL | ACCESS_PERMS);
    so_exit_on_error(id, "Erro semget Create");
  }

  return id;
}

int sem_set(int id, int idx, int value) {
  // SETVAL está definido na biblioteca sem
  int result = semctl(id, idx, SETVAL, value);
  so_exit_on_error(result, "Erro semctl SET");
  so_debug("O valor do semáforo: %d é: %d\n", idx, value);

  return result;
}

int sem_get(int id, int idx) {
  // GETVAL está definido na biblioteca sem
  int value = semctl(id, idx, GETVAL);
  so_debug("O valor do semáforo: %d é: %d\n", idx, value);

  return value;
}

int sem_change(int id, int idx, int value) {
  struct sembuf operation = { idx, value, 0 };
  int status = semop(id, &operation, 1);
  
  if(status < 0) {
    so_exit_on_error(status, "Erro semop OP");
  }

  return sem_get(id, idx);
}

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
    so_debug("Posição %2d: %6d | %s | %2.3f", i, turma[i].numero, turma[i].nome, turma[i].nota);
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
  #define NR_SEMAPHORES 1
  #define SEM_UP 1
  #define SEM_DOWN -1

  int sem_id = sem_create(NR_SEMAPHORES);
  int shm_id = shm_create(sizeof(aluno_t) * NR_ALUNOS);
  aluno_t *turma = shm_attach(shm_id);
  
  shm_init(turma, NR_ALUNOS);
  shm_view(turma, NR_ALUNOS);

  while(TRUE) {
    aluno_t aluno = criar_aluno();

    // o segundo argumento é sempre 0 porque como só tenho 1 semáforo, o idx vai ser sempre 0
    sem_change(sem_id, 0, SEM_UP);
    int result = registar_aluno(turma, NR_ALUNOS, aluno);
    sem_change(sem_id, 0, SEM_DOWN);

    so_exit_on_error(result, "Erro registar aluno");
    shm_view(turma, NR_ALUNOS);
  }

  return 0;
}