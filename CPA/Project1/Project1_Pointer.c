/*
  Hunter Bresler
  02/10/2023
  Test out a pointer variable
*/

#include <stdio.h>


int main(void){

    int num = 10, *numPtr;

    numPtr = &num;


    printf("\nThe address of the pointer is %p\nThe value stored in the pointer is %d"
            "\nThe value referenced by the pointer is %d\n", *numPtr, numPtr, *numPtr);


    num *= 3;


    printf("\nAfter changing the value of num:\nThe address of the pointer is %p\nThe value stored in the pointer is %d"
            "\nThe value referenced by the pointer is %d\n\n", *numPtr, numPtr, *numPtr);


    return 0;
}