#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>

pid_t *childs;
int nb_childs;

int print_help(char *program_name)
{
    printf("USAGE:\n\t%s IP_ADRESS NB_PROCESS\n", program_name);
    printf("\nDESCRIPTION:\n\tIP_ADRESS\tThe target you want to ping\n");
    printf("\tNB_PROCESS\tThe number of process you want to create to ping the target (try 100 to test)\n");
    return 0;
}

int need_help(int argc, char **argv)
{
    int i = 1;

    while (i < argc){
        if (strcmp(argv[i], "-h") == 0)
            return 1;
        i++;
    }
    return 0;
}

void kill_all_childs(int sig)
{
    int i = 0;

    while (i < nb_childs){
        kill(childs[i], SIGKILL);
        i++;
    }
    free(childs);
    return;
}

int ping(char *ip_adress, int nb)
{
    char *command[] = {"/usr/bin/ping", "-i", "0.002", ip_adress, NULL};
    pid_t child;

    if (nb <= 0){
        write(2, "Invalid number of process !\n", 29);
        return 84;
    }
    nb_childs = nb;
    childs = malloc(sizeof(pid_t) * nb_childs);
    if (childs == NULL){
        return 84;
    }
    signal(SIGINT, kill_all_childs);
    close(STDOUT_FILENO);
    for (int i = 0; i < nb_childs; i++){
        child = fork();
        if (child < 0){
            write(2, "Can't create a fork !\n", 23);
            return 84;
        }
        if (child == 0){
            childs[i] = child;
            execv(command[0], command);
        }
    }
    while (wait(NULL) > 0);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 3 || need_help(argc, argv))
        return print_help(argv[0]);
    return ping(argv[1], atoi(argv[2]));
}
