#include "defines.h"

int main() {
  #define ACCESS_PERMS 0600

  // No segundo argumento tambem podemos passar 0 caso queiramos todas as queues daquela key
  int id = msgget(IPC_KEY, ACCESS_PERMS);

  if(id == -1) {
    id = msgget(IPC_KEY, IPC_CREAT | IPC_EXCL | ACCESS_PERMS);
    printf("%d\n", id);

    so_exit_on_error(id, "Erro msgget Create");
    so_debug("Estou a usar a fila de mensagens com key = 0x%x e id = %d", IPC_KEY, id);
  } else {
    printf("A fila ja existe com o o id = %d\n", id);
  }

  return 0;
}