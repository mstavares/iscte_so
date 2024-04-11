#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int n = 0;

void trata_sinal_alarm(int sinal) {
  printf("Recebi sinal %d\n", sinal);
  n = 1;
}

void trata_sinal_sigint(int sinal) {
  printf("Vou terminar!");
}

int main() {
  printf("Esperar 5 segundos...\n");
  signal(SIGALRM, trata_sinal_alarm);
  signal(SIGINT, trata_sinal_sigint);
  alarm(5);
  
  //while(n == 0);
  pause();
  printf("ok\n");
  return 0;
}