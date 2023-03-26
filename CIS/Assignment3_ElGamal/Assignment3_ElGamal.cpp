//*MAIN
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "elGamal.h"
#include "elgamal.cpp"


using namespace std;


int main(){

    //Set seed for random numbers
    srand(time(NULL));

    ELGAMAL hasKey, sendsKey;


    string base = "1110";
    string exponent = "10110";
    string modulo = "1000110001";
    string sum = hasKey.Div(modulo, "10");


    cout << "\nBinary print: ";
    for (int i = 0; i < sum.size(); i++)
    {
        cout << sum[i];
    }

    sendsKey.getPublicKey_fromFile();

    cout << "\n\nIs " << modulo << " prime: " << hasKey.isPrime(modulo, modulo.size() + 10);

    return 0;
}
