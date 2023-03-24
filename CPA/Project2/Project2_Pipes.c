#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{

    int fd[2][2];

    for (int i = 0; i < 2; i++)
    {
        if (pipe(fd[i]) < 0)
        {
            return 1;
        }
    }



    int id1 = fork();
    if (id1 < 0)
    {
        return 2;
    }

    //Child process 1
    if (id1 == 0)
    {
        //Close unused pipes
        close(fd[0][1]);
        close(fd[1][0]);
        
        //READ
        int x;
        if (read(fd[0][0], &x, sizeof(int)) < 0)
        {
            return 3;
        }

        //PROCESS
        x += 5;

        //WRITE
        if (write(fd[1][1], &x, sizeof(int)) < 0)
        {
            return 4;
        }

        //Close after use
        close(fd[0][0]);
        close(fd[1][1]);
        return 0;

    }



    int id2 = fork();
    if (id2 < 0)
    {
        return 5;
    }

    //Child process 2
    if (id2 == 0)
    {
        //Close unused pipes
        close(fd[0][1]);
        close(fd[0][0]);
        close(fd[1][1]);
        
        //READ
        int x;
        if (read(fd[1][0], &x, sizeof(int)) < 0)
        {
            return 6;
        }

        //PROCESS
        x += 5;
        printf("x = %d", x);
        

        //Close after use
        close(fd[1][0]);
        return 0;

    }



    // Parent process
    // Close unused pipes
    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);

    // PROCESS
    int x = 0;

    // WRITE
    if (write(fd[0][1], &x, sizeof(int)) < 0)
    {
        return 8;
    }

    waitpid(id1, NULL, 0);
    waitpid(id2, NULL, 0);

    // Close after use
    close(fd[0][1]);

    return 0;
}