#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void trata_sinal_alarm(int sinal) {
  if(!fork()) {
    execl("/bin/date", "date", NULL);
  }
}

int main() {
  signal(SIGALRM, trata_sinal_alarm);

  while(1) {
    alarm(5);
    pause();
  }

}