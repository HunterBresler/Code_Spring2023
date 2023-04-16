#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include "binary.h"
#include "binary.cpp"

using namespace std;

int main()
{
    //Test time
    auto begin = chrono::high_resolution_clock::now();

    //Set seed for random numbers
    srand(time(NULL));

    binary prime;
    prime = generatePrime(512);
    cout << "\nPrime: " << prime;


    //Calc and print time
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    
    printf("\n\nTime measured: %.3f seconds.\n\n", elapsed.count() * 1e-9);

    return 0;
}