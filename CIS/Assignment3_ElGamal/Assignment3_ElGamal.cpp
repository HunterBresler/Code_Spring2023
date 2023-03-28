//*MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
#include "elGamal.h"
#include "elgamal.cpp"


using namespace std;

//TODO: add getPlaintext() and find out why generator generation sucks
int main(){

    //Test time
    auto begin = chrono::high_resolution_clock::now();

    //Set seed for random numbers
    srand(time(NULL));

    ELGAMAL hasKey("Has Key"), sender("Sender");

    //Sender encrypts and sends message
    sender.encrypt();

    //Has Key receives and decrypts message
    hasKey.decrypt();

    //Calc and print time
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

    printf("\n\nTime measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    return 0;
}

