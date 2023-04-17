#include <iostream>
#include <ctime>
#include <chrono>
#include "binary.h"
#include "binary.cpp"
#include "RSA.h"
#include "RSA.cpp"

using namespace std;
using namespace binary_HB;
using namespace RSA_HB;

int main()
{
    
    //Test time
    auto begin = chrono::high_resolution_clock::now();

    //Set seed for random numbers
    srand(time(NULL));

    binary prime;
    prime = generatePrime(64);
    cout << "\nPrime: " << prime;


    //Calc and print time
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    
    printf("\n\nTime measured: %.3f seconds.\n\n", elapsed.count() * 1e-9);
    
    return 0;
}