#include <stdio.h>
#include <unistd.h> // necessário para termos acesso à função fork()

int main() {
  printf("Início PID=%d filho de %d\n", getpid(), getppid());
  printf("Fim de PID=%d filho de %d\n", getpid(), getppid());
}

/**
Início PID=24625 filho de 38535
Fim de PID=24625 filho de 38535

echo $$
38535
*/