#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv){

    setuid(0);
    printf("Wykonuje kill -9 1 z poziomu roota\n");
    kill(1,9);
    return 0;
}
