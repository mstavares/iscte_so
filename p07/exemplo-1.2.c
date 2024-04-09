#include <stdio.h>
#include <unistd.h> // necessário para termos acesso à função fork()
#include <sys/wait.h> // necessário para termos acesso à função wait()

int main() {
  printf("Início PID=%d filho de %d \n", getpid(), getppid());

  pid_t pid = fork();
  if(pid < 0) {
    printf(">> Fork falhou \n");
  } else if(pid == 0) {
    printf(">> Processo filho %d \n", getpid());
  } else {
    printf(">> Processo pai %d \n", getpid());
    wait(NULL); // waits for 
  }

  printf("Fim de PID=%d filho de %d \n", getpid(), getppid());
}

/*
Início PID=43926 filho de 38535 
Fim de PID=43931 filho de 43926 
Fim de PID=43926 filho de 38535 

A new process was created right before second prinf execution, hence, second printf will be printed twice
one from the process created by the program execution and another one created by fork() call
*/