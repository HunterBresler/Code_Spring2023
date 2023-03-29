#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main() {

  int fd[2][2];

  for (int i = 0; i < 2; i++) {
    if (pipe(fd[i]) < 0) {
      return 1;
    }
  }


  
  int id1 = fork();
  if (id1 < 0) {
    return 2;
  }

  // Child process 1
  if (id1 == 0) {
    // Close unused pipes
    close(fd[0][1]);
    close(fd[1][0]);

    //Declare
    char reverseCase[100];
    int size = 1;

    // READ
    if (read(fd[0][0], &size, sizeof(int)) < 0) { //reads size of string
      return 3;
    }
    if (read(fd[0][0], &reverseCase, size) < 0) { //reads string
      return 3;
    }

    // PROCESS
    //reverse the cases of a string
    for (int i = 0; i < size; i ++)
    {
      if (islower(reverseCase[i]))
      {
        reverseCase[i] = toupper(reverseCase[i]);
      }
      else
      {
        reverseCase[i] = tolower(reverseCase[i]);
      }
    }

    // WRITE
    if (write(fd[1][1], &size, sizeof(int)) < 0) { //write size of string
      return 4;
    }
    if (write(fd[1][1], &reverseCase, size) < 0) { //write string
      return 4;
    }
    
    // Close after use
    close(fd[0][0]);
    close(fd[1][1]);
    return 0;
  }


  
  int id2 = fork();
  if (id2 < 0) {
    return 5;
  }

  // Child process 2
  if (id2 == 0) {
    // Close unused pipes
    close(fd[0][1]);
    close(fd[0][0]);
    close(fd[1][1]);

    //Declare
    FILE *fp;
    int size = 1;
    char outputToFile[100];

    // READ
    if (read(fd[1][0], &size, sizeof(int)) < 0) { //read size of string
      return 6;
    }
    if (read(fd[1][0], &outputToFile, size) < 0) { //read string
      return 6;
    }
    
    // PROCESS
    //write a line to output.txt
    fp = fopen("output.txt", "w");
    fputs(outputToFile, fp);

    // Close after use
    fclose(fp);
    close(fd[1][0]);
    return 0;
  }


  
  // Parent process
  // Close unused pipes
  close(fd[0][0]);
  close(fd[1][0]);
  close(fd[1][1]);

  //Declare
  FILE *fp;
  char writeToPipe[100];
  int size;

  // PROCESS
  //read one line at a time from input.txt until the end of the file
  fp = fopen("input.txt", "r");

  while (fgets(writeToPipe, 100, fp))
  {

    printf("%s", writeToPipe);
    
    // WRITE
    size = strlen(writeToPipe);
    if (write(fd[0][1], &size, sizeof(int)) < 0) { //write size of string
      return 8;
    }
    if (write(fd[0][1], &writeToPipe, strlen(writeToPipe)+1) < 0) { //write string
      return 8;
    }
  }
  
  waitpid(id1, NULL, 0);
  waitpid(id2, NULL, 0);

  // Close after use
  fclose(fp);
  close(fd[0][1]);
  
  return 0;
}