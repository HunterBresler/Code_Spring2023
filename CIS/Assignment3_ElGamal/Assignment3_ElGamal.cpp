//*MAIN
#include <iostream>
#include <string>
#include <fstream>
#include "elGamal.h"
#include "elgamal.cpp"

using namespace std;


int main(){

    ELGAMAL hasKey, sendsKey;


    string add1 = "101";
    string add2 = "100";
    string sum = hasKey.Multiply(add1, add2);

    cout << "\nBinary print: ";
    for (int i = 0; i < sum.size(); i++)
    {
        cout << sum[i];
    }

    return 0;
}
