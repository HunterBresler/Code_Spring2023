//*MAIN
#include <iostream>
#include <string>
#include <fstream>
#include "elGamal.h"
#include "elgamal.cpp"

using namespace std;


int main(){

    ELGAMAL hasKey, sendsKey;


    string base = "10111";
    string exponent = "10110";
    string modulo = "10111";
    string sum = hasKey.ModExpo(base,exponent, modulo);

    cout << "\nBinary print: ";
    for (int i = 0; i < sum.size(); i++)
    {
        cout << sum[i];
    }

    sendsKey.getPublicKey_fromFile();

    return 0;
}
