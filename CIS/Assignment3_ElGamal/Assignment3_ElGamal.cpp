//*MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "elGamal.h"
#include "elgamal.cpp"


using namespace std;

//TODO: add getPlaintext() and find out why generator generation sucks
int main(){

    //Set seed for random numbers
    srand(time(NULL));

    ELGAMAL hasKey("Has Key"); //, sender("Sender");


    //Sender encrypts and sends message
    //sender.Drive();

    //Has Key receives and decrypts message
    //hasKey.Drive();


    
    //Test encryption
    ///sendsKey.getPublicKey_fromFile();

    //string gen = sendsKey.generateGenerator(sendsKey.getPrime());
    //cout << "\nTest: " << 1;
    //cout << "\nPrime: " << sendsKey.getPrime();

    return 0;
}

