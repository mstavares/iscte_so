#include "defines.h"

typedef struct {
  long msg_type;
  struct {
    char text [80];
  } msg_data;
} msg_content_t;

int main() {
  #define IPC_GET 0
  int id = msgget(IPC_KEY, IPC_GET);
  so_exit_on_error(id, "Erro msgget");

  msg_content_t msg = { .msg_type = 33 };
  printf("Escreva a mensagem: ");
  so_gets(msg.msg_data.text, sizeof(msg.msg_data.text));

  int status = msgsnd(id, &msg, sizeof(msg.msg_data), 0);
  so_exit_on_error(status, "Erro msgsnd");
  so_debug("A mensagem foi enviada com o tipo %ld, tamanho %ld, e conteudo %s", msg.msg_type, sizeof(msg.msg_data), msg.msg_data.text);


  return 0;
}