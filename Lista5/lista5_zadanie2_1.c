#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv){
    signal(SIGKILL, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    raise(SIGTERM);
    printf("Nie zostalem zabity przez SIGTERM\n");
    raise(SIGKILL);
    printf("Nie zostalem zabity przez SIGKILL\n");
    return 0;
}
