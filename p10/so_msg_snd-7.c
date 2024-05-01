#include "defines.h"

typedef struct {
  long msg_type;
  struct {
    char text [MSGDATA_MAX_SIZE];
  } msg_data;
} msg_content_t;

int main(int argc, char *argv[]) {
  #define IPC_GET 0

  if(argc < 3) {
    printf("Foram passados apenas %d parametros, ex: ./so_msg_snd-7.out <msg_type> <msg_size>", argc);
    exit(1);
  }

  int msg_type = atoi(argv[1]);
  int msg_size = atoi(argv[2]);
  if(msg_size > MSGDATA_MAX_SIZE) {
    printf("O parametro msg_size de %d nao pode ser maior que %d", msg_size, MSGDATA_MAX_SIZE);
    exit(1);
  }

  int id = msgget(IPC_KEY, IPC_GET);
  so_exit_on_error(id, "Erro msgget");

  msg_content_t msg = { .msg_type = msg_type };
  snprintf(msg.msg_data.text, MSGDATA_MAX_SIZE, "Mensagem com %d Bytes", msg_size);

  int status = msgsnd(id, &msg, msg_size, 0);
  so_exit_on_error(status, "Erro msgsnd");
  so_debug("A mensagem foi enviada com o tipo %ld, tamanho %ld, e conteudo %s", msg.msg_type, sizeof(msg.msg_data), msg.msg_data.text);

  return 0;
}