/*
  Hunter Bresler
  02/10/2023
  Calculate values for 6 IO numbers
*/

#include <stdio.h>


int main(void){

    const int arrSize = 6;
    double min, max, average, sum, inputNumbers[arrSize];

    
    //Prompt input
    printf("\nInput your 6 numbers leaving a space in between each: ");


    //Get first value for a base value of min/max
    scanf(" %lf", &inputNumbers[0]);
    min = inputNumbers[0];
    max = inputNumbers[0];
    sum = inputNumbers[0];

    //Loop for array inputs
    //Do calculations while recieving input
    
    for (int i = 1; i < arrSize; i++)
    {
        scanf(" %lf", &inputNumbers[i]);

        //Compute sum
        sum += inputNumbers[i];

        //min/max checking
        if (inputNumbers[i] < min)
        {
            min = inputNumbers[i];
        }
        else if (inputNumbers[i] > max)
        {
            max = inputNumbers[i];
        }
    }   
    

    //Compute avg
    average = sum/arrSize;


    //Output
    printf( "\n\nCalculations Complete.\n\n"
            "Sum = %lf\n"
            "Average = %lf\n"
            "Max = %lf\n"
            "Min = %lf\n\n",
            sum, average, max, min);

    return 0;
}
