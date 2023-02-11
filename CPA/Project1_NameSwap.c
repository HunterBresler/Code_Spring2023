/*
  Hunter Bresler
  02/10/2023
  Swap strings
*/

#include <stdio.h>
#include <string.h>


int main(void){

    char name1[20], name2[20], swap[20];

    //Get user input
    printf("\nEnter the first name: ");
    scanf(" %s", name1);
    printf("Enter the second name: ");
    scanf(" %s", name2);


    //Output before swap
    printf("\n\nThe first name is: %s", name1);
    printf("\nThe second name is: %s", name2);


    //Swap names
    strcpy(swap,name1);
    strcpy(name1,name2);
    strcpy(name2,swap);


    //Output after swap
    printf("\n\nThe first name is: %s", name1);
    printf("\nThe second name is: %s\n\n", name2);


    return 0;
}