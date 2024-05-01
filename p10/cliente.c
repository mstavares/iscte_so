#include "defines.h"

#define MSG_LOGIN 1
#define NAME_SIZE 20
#define TEXT_SIZE 80
#define ACCESS_PERMS 0600

typedef struct {
  long msg_type;
  struct {
    char text[TEXT_SIZE];
    char name[NAME_SIZE];
    int client_pid;
  } msg_data;
} msg_content_t;

int main(int argc, char *argv[]) {
  if(argc < 2) {
    printf("Foram passados apenas %d parametros, ex: ./cliente.out <name>", argc);
    exit(1);
  }

  if(strlen(argv[1]) > NAME_SIZE) {
    printf("O argumento do nome tem %ld caracteres, no maximo pode ter %d", strlen(argv[1]), NAME_SIZE);
    exit(1);
  }

  int id = msgget(IPC_KEY, MSG_LOGIN);
  if(id == -1) {
    id = msgget(IPC_KEY, IPC_CREAT | IPC_EXCL | ACCESS_PERMS);
    so_exit_on_error(id, "Erro msgget Create");
  }

  so_debug("Estou a usar a fila de mensagens com a key = 0x%x e id = %d", IPC_KEY, id);

  pid_t pid = fork();
  if(pid < 0) {
    printf(">> Fork falhou \n");
  } else if(pid == 0) {
    msg_content_t msg;
    while(TRUE) {
      int status = msgrcv(id, &msg, sizeof(msg.msg_data), getppid(), 0);
      so_exit_on_error(status, "Erro msgrcv");
      so_debug("<<< Recebi de %s (PID %d) a msg: %s", msg.msg_data.name, msg.msg_data.client_pid, msg.msg_data.text);
    }
  } else {
    msg_content_t msg = { .msg_type = MSG_LOGIN, .msg_data.client_pid = getpid() };
    strncpy(msg.msg_data.name, argv[1], NAME_SIZE);

    while(TRUE) {
      printf("Escreva uma mensagem: ");
      so_gets(msg.msg_data.text, sizeof(msg.msg_data.text));

      int status = msgsnd(id, &msg, sizeof(msg.msg_data), 0);
      so_exit_on_error(status, "Erro msgsnd");
      so_debug(">>> A mensagem foi enviada com o tipo %ld, tamanho %ld, nome %s, conteudo %s e pid %d",
        msg.msg_type, sizeof(msg.msg_data), msg.msg_data.name, msg.msg_data.text, msg.msg_data.client_pid);
    }
  }

  return 0;
}