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

  msg_content_t msg;

  /**
  Sobre o último argumento..
  https://linux.die.net/man/2/msgrcv
  ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)

  Se ele contiver o flag IPC_NOWAIT, a chamada à msgrcv retorna imediatamente com um código de erro quando a fila não contiver uma mensagem do tipo desejado.
  Se ele não contiver o flag IPC_NOWAIT, o processo que chama a função msgrcv ficará bloqueado até que haja uma mensagem do tipo requerido (msgtyp na fila;
  Se ele contiver o flag MSG_NOERROR, a mensagem é truncada com um tamanho máximo msgsz bytes, sendo a parte truncada perdida;
  Se ele não contiver o flag MSG_NOERROR, a mensagem não é lida, e msgrcv retorna um código de erro.
  O flag MSG_EXCEPT é utlizado em conjunto com msgtyp > 0 para a leitura da primeira mensagem da fila cujo tipo de mensagem difere de msgtyp.

  */
  int status = msgrcv(id, &msg, sizeof(msg.msg_data), 33, 0);
  so_exit_on_error(status, "Erro msgrcv");

  so_debug("A mensagem foi recebida com o tipo %ld, tamanho %ld, e conteudo %s", msg.msg_type, sizeof(msg.msg_data), msg.msg_data.text);

  return 0;
}