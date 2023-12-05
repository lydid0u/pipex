#include "pipex.h"

int main(int argc, char **argv)
{
    int id = fork();
    printf("og id: %d\n", id);
    // if (id == 0)
    // {
    //     sleep(1);
    // }
    printf("current id: %d, parent id: %d\n", getpid(), getppid());
    return (0);
}