/*
    Author: Hunter Bresler
    Date: 2/22/2023
    question1: selection sort
*/

#include <iostream>
#include <vector>

using namespace std;



//*Selction Sort
void SelectionSort(vector<int> &arr, int size)
{

    int maxIndex, temp;
    
    for (int i = 0; i < size-1; i++)
    {
        maxIndex = i;

        for (int j = i+1; j < size; j++)
        {
        if (arr[j] > arr[maxIndex])
        {
            maxIndex = j;
        }
        }
        
        temp = arr[i];
        arr[i] = arr[maxIndex];
        arr[maxIndex] = temp;
    }
}



//*MAIN
int main(){

    //Get array size
    int size;

    cout << "\nEnter the size of the array you wish to sort: ";
    cin >> size;


    //Create array of user inputted values
    vector<int> arr(size, 0);

    for (int i = 0; i < size; i++)
    {
        cout << "Enter the value for index " << i << ": ";
        cin >> arr[i];
    }


    //Print unsorted array
    cout << "\nThe unsorted array is: ";
    
    for (int i: arr)
    {
        cout << i << " ";
    }
    
    //Call selection sort function
    SelectionSort(arr, size);
    
    //Print sorted array (descending order)
    cout << "\n\nThe sorted array (in descending order) is: ";
    
    for (int i: arr)
    {
        cout << i << " ";
    }
    
    return 0;
}