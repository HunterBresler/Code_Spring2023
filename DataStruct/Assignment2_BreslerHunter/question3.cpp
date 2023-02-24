/*
    Author: Hunter Bresler
    Date: 2/23/2023
    question3: Two Largest
*/

#include <iostream>
#include <vector>

using namespace std;



//*Finds the two largest numbers
void TwoLargest(vector<int> &arr, int size, int* large1, int* large2)
{
  
    //Set the base large values
    *large1 = arr[0];
    *large2 = arr[1];

    
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > *large1)
        {
        *large2 = *large1;
        *large1 = arr[i];
        }
        else if (*large2 < arr[i])
        {
        *large2 = arr[i];
        }
    }
}



//*MAIN
int main(){

    //Get array size
    //Declare variables
    int size, large1, large2;

    //Reusing code from question 1 to save time
    cout << "\nEnter the size of the array you wish to input: ";
    cin >> size;


    //Create array of user inputted values
    vector<int> arr(size, 0);

    for (int i = 0; i < size; i++)
    {
        cout << "Enter the value for index " << i << ": ";
        cin >> arr[i];
    }

    
    //Call Two Largest function
    TwoLargest(arr, size, &large1, &large2);
    
    //Print 2 largest values
    cout << "\n\nThe largest value in the array is " << large1 << " and the second largest value is " << large2;
    
    return 0;
}