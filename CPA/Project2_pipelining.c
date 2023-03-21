/*
  Hunter Bresler
  03/20/2023
  Uses pipelining to change a text file
*/

#include <stdio.h>
#include <stdlib.h>

int main(void){

    //fd[0] = read
    //fd[1] = write
    int fd[2];

    //Check for pipe error
    if (pipe(fd) == -1)
    {
        printf("Pipe error\n");
        return 1;
    }

    int id = fork();
    if (id = 0)
    {
        //Child
        
    }
    else
    {
        //Parent

    }

    return 0;
}