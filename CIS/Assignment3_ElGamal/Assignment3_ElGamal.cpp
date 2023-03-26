//*MAIN
#include <iostream>
#include <string>
#include <fstream>
#include "elGamal.h"
#include "elgamal.cpp"

using namespace std;


int main(){

    ELGAMAL hasKey, sendsKey;


    string add1 = "1111";
    string add2 = "110";
    string sum = hasKey.Modulus(add1, add2);

    cout << "\nBinary print: ";
    for (int i = 0; i < sum.size(); i++)
    {
        cout << sum[i];
    }

    sendsKey.getPublicKey_fromFile();

    return 0;
}
