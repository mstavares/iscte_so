#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
  char s[100];

  printf("PID=%d\n", getpid());

  while(1) {
    printf("Comando ");
    fgets(s, 100, stdin);
    s[strlen(s) - 1] = 0;

    if(strcmp(s, "sair") == 0) {
      exit(0);
    }
  }
}