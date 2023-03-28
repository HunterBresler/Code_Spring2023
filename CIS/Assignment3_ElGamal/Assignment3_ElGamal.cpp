//*MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
#include "elGamal.h"
#include "elgamal.cpp"


using namespace std;


int main(){

    //Test time
    auto begin = chrono::high_resolution_clock::now();

    //Set seed for random numbers
    srand(time(NULL));

    //Comment out what you aren't testing
    /*
    //Test Main Class Functions
    ELGAMAL memberTest;

    memberTest.Drive();
    memberTest.encrypt();
    memberTest.decrypt();

    //Test User Functionality
    ELGAMAL user("Jeff");

    user.encrypt();
    user.decrypt();
    */

    //Test Dev Mode (time test as well)
    int keySize = 128;
    string safePrimeCheckCount = "111111";
    ELGAMAL test(keySize, safePrimeCheckCount);

    //Calc and print time
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

    printf("\n\nTime measured: %.3f seconds.\n\n", elapsed.count() * 1e-9);

    return 0;
}

