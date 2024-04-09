#include <stdio.h>
#include <unistd.h> // necessário para termos acesso à função execl
#include <sys/wait.h> // necessário para termos acesso à função wait()

// Sem fork o ultimo printf não é executado porque o execl substitui-se ao processo atual.
int main() {
  printf("Mostrar o conteudo da diretoria :/\n");

  pid_t pid = fork();
  if(pid < 0) {
    printf("o fork falhou");
  } else if (pid == 0) {
    execl("/bin/ls", "ls", "-l", "/", NULL);
  } else {
    wait(NULL);
    printf("Fim do comando: ls -l /\n");
  }
  
}