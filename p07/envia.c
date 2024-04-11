#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

int main() {
  int n;

  printf("Enviar sinal para: ");
  // Não há problema em usar scanf aqui porque estamos a ler inteiros
  scanf("%d", &n);

  // killed ./p1.out
  //kill(n, SIGKILL);
  // user-defined signal 1 ./p1.out
  kill(n, SIGUSR1);

  return 0;
}