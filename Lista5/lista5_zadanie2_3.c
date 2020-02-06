#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int counter = 0;

void odbior(int numer) {
  counter++;
  printf("Otrzymalem sygnal nr %i\n", counter);
}
 
int main() {
  int status;
  signal(SIGUSR1, odbior);
  __pid_t k=fork();
  if (k == 0){
    for (int i=0; i<100; i++){
      kill(getppid(), SIGUSR1);
      printf("Wyslalem sygnal nr %i\n", i+1);
    }
    exit(1);
  }
  else {
    wait(&status);
  }
}
