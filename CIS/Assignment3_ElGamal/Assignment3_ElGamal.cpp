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

    ELGAMAL hasKey("Has Key");//, sender("Sender");

    string result = hasKey.Div("11110", "11");
    cout << "\nTEST: " << result;


    //Sender encrypts and sends message
    //sender.Drive();

    //Has Key receives and decrypts message
    //hasKey.Drive();

    return 0;
}

