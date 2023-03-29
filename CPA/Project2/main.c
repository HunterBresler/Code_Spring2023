#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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

    // Declare
    char reverseCase[100];
    char writes[100];

    // READ
    while (read(fd[0][0], reverseCase, sizeof(reverseCase)) != 0) { // reads string

      // PROCESS
      // reverse the cases of a string
      for (int i = 0; i < sizeof(reverseCase); i++) {
        if (islower(reverseCase[i])) {
          reverseCase[i] = toupper(reverseCase[i]);
        } else {
          reverseCase[i] = tolower(reverseCase[i]);
        }
      }

      //WRITE
      write(fd[1][1], reverseCase, sizeof(reverseCase));
      
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

  // Declare
  FILE *fp;
  char outputToFile[100];

  // PROCESS
  // write a line to output.txt
  fp = fopen("output.txt", "w");
  
  while (read(fd[1][0], outputToFile, sizeof(outputToFile) != 0)) { // read string
    fprintf(fp, "%s", outputToFile);
  }

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

// Declare
FILE *fp;
char writeToPipe[100];

fp = fopen("input.txt", "r");

// PROCESS
// read one line at a time from input.txt until the end of the file
while (fgets(writeToPipe, sizeof(writeToPipe), fp) != NULL) {
  // WRITE
  write(fd[0][1], writeToPipe, sizeof(writeToPipe));
}

// Close after use
close(fd[0][1]);
fclose(fp);

waitpid(id1, NULL, 0);
waitpid(id2, NULL, 0);

return 0;
}
