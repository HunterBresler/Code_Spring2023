/*
  Hunter Bresler
  02/01/2023
  Employee info
*/

#include <stdio.h>


int main(void) {

  //Declare variables
  char name1[20], name2[20], name3[20];
  int age1, age2, age3;
  double salary1, salary2, salary3;

    
  //Get input
  printf("\nInput the first employee's name, age, and salary: ");
  scanf(" %s %d %lf", name1, &age1, &salary1);

  printf("\nInput the second employee's name, age, and salary: ");
  scanf(" %s %d %lf", name2, &age2, &salary2);

  printf("\nInput the third employee's name, age, and salary: ");
  scanf(" %s %d %lf", name3, &age3, &salary3);

  
  //Print statements
  printf("\n\n%s is %d years old with a salary of %.2lf.\n"
    "\n%s is %d years old with a salary of %.2lf.\n"
    "\n%s is %d years old with a salary of %.2lf.\n\n"
    , name1, age1, salary1, name2, age2, salary2, name3, age3, salary3);

  return 0;
}