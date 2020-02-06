#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>

bool bg = false;
int child_pid=0;

void sig_handler(int n){
    if (child_pid != 0) kill(child_pid, 15);
}

char **lsh_parsecmd(char *cmd){
    char **args = malloc(1024 * sizeof(char*));;
    int i = 0;
    if (cmd==NULL){
        args[0]="exit";
        args[1]=NULL;
        return args;
    }
    while (cmd != NULL){
        args[i] = strsep(&cmd, " ");
        i++;
    }
    if (i>0){
        if (strcmp(args[i-1],"&")==0){
            bg = true;
            args[i-1]=NULL;
        }
    }
    args[i] = NULL;
    return args;
}

int exit_lsh(){
    return 0;
}

int cd_lsh(char **args){
    if (args[1]==NULL){
        printf("Nie podano folderu");
    } else {
        int i = chdir(args[1]);
        if (i != 0) perror("Wystapil blad");
    }
    return 1;
}

int lsh_runchild(char **args){
    pid_t i;
    int stat;
    int k=0;
    int flow=-1, fd;

    i = fork();
    if (i==0){
        child_pid = getpid();
        while(args[k]!=NULL && flow == -1){
            if(strcmp(args[k],">")==0) flow = 1;
            else if(strcmp(args[k],"<")==0) flow = 0;
            else if (strcmp(args[k],"2>")==0) flow = 2;
            k++;
        }
       if (flow != -1){
           fd = open(args[k], O_RDWR);
           args[k]=NULL;
           args[k-1]=NULL;
           if (flow == 0) dup2(fd,0);
           else if (flow ==1 ) dup2(fd,1);
           else dup2(fd,2);
       }
       int j = execvp(args[0], args);
       if (flow != -1) close(fd);
       if (j==-1) perror("Wystapil blad");
    }
    else if (i>0){
        if (bg){
            signal(SIGCHLD, SIG_IGN);
        }
        else waitpid(i,&stat,0);
    }
    else if (i<0) perror("Wystapil blad");
    return 1;
}

int lsh_executecmd(char **args){
    int status;
    if (args[0] ==  NULL) status = 0;
    else if (strcmp(args[0],"exit")==0) {
        status = exit_lsh();
    }
    else if (strcmp(args[0],"cd")==0){
        status = cd_lsh(args);
    }
    else status = lsh_runchild(args);
    return status;
}

int lsh_executePiped(char *pipe1, char *pipe2){
    char **args1;
    char **args2;
    int i;
    int pipefd[2];
    pid_t p1, p2;
    args1 = lsh_parsecmd(pipe1);
    args2 = lsh_parsecmd(pipe2);
    i = pipe(pipefd);
    if (i == -1){
        perror("Nie udalo sie otworzyc potoku");
        return 1;
    }

    p1 = fork();
    if (p1 < 0){
        perror("Nie udalo sie zrobic forka");
        return 1;
    }

    if (p1 == 0){
        close(pipefd[0]);
        child_pid = getpid();
        if(dup2(pipefd[1],1) != 1){
            perror("Nie udalo sie przekierowac stdout");
            return 1;
        }
        close(pipefd[1]);
        
        if (execvp(args1[0], args1) < 0){
            perror("Nie udalo sie wykonac polecenia 1");
            exit(0);
        }
    } 
    else {
        p2 = fork();
        if (p2 < 0){
            perror("Nie udalo sie zrobic forka");
            return 1;
        }

        if (p2 == 0){
            child_pid=getpid();
            close(pipefd[1]);
            if (dup2(pipefd[0],0) != 0){
                perror("Nie udalo sie przekierowac stdin");
                return 1;
            }
            close(pipefd[0]);
            if (execvp(args2[0], args2) < 0){
                perror("Nie udalo sie wykonac polecenia 2");
                exit(0);
            }
        }
        else {
            close(pipefd[1]);
            close(pipefd[0]);
            wait(NULL);
            wait(NULL);
        }
    }
    return 1;
}

void run_lsh(){
    char* username = getenv("USER");
    char curDir[1024];
    int keepRunning = 1;
    char *cmd;
    char **pipes = malloc(sizeof(char*)*2);
    char **args;
    
    while (keepRunning){
        getcwd(curDir,sizeof(curDir));
        printf("\033[38;5;81m");
        printf("\n%s@dominika-VirtualBox:%s",username,curDir);
        printf("\033[38;5;231m");
        cmd = readline(">");
        pipes[0] = strsep(&cmd,"|");
        pipes[1] = strsep(&cmd, "|");
        if (pipes[1]==NULL){
            args = lsh_parsecmd(pipes[0]);
            keepRunning = lsh_executecmd(args);
        }
        else {
            keepRunning = lsh_executePiped(pipes[0],pipes[1]);
        }
        bg = false;
        child_pid = 0;
    }
}

int main(int argc, char **argv){
    int stat;
    signal(2, sig_handler);
    run_lsh();
    wait(&stat);
    printf("\n");
    return EXIT_SUCCESS;
}
