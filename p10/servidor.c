#include "defines.h"

#define MSG_LOGIN 1

typedef struct {
  long msg_type;
  struct {
    char text[80];
    char name[20];
    int client_pid;
  } msg_data;
} msg_content_t;

int main() {
  #define ACCESS_PERMS 0600

  int id = msgget(IPC_KEY, 0);
  if(id == -1) {
    id = msgget(IPC_KEY, IPC_CREAT | IPC_EXCL | ACCESS_PERMS);
    so_exit_on_error(id, "Erro msgget Create");
  }

  so_debug("Estou a usar a fila de mensagens com a key = 0x%x e id = %d", IPC_KEY, id);

  msg_content_t msg;
  while(TRUE) {
    int status = msgrcv(id, &msg, sizeof(msg.msg_data), MSG_LOGIN, 0);
    so_exit_on_error(status, "Erro msgrcv");
    so_debug("Recebi de %s (PID %d) a msg: %s", msg.msg_data.name, msg.msg_data.client_pid, msg.msg_data.text);

    msg.msg_type = msg.msg_data.client_pid;
    snprintf(msg.msg_data.text, sizeof(msg.msg_data.text), "Sr(a) %s recevi a sua msg", msg.msg_data.name);
    status = msgsnd(id, &msg, sizeof(msg.msg_data), 0);
    so_exit_on_error(status, "Erro msgsnd");

    so_debug("Enviei esposta para o cliente %ld", msg.msg_type);
  }

  return 0;
}