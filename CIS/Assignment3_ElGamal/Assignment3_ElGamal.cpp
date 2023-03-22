//*MAIN
#include <iostream>
#include <vector>
#include <fstream>
#include "elGamal.h"
#include "elgamal.cpp"

using namespace std;


int main(){

    ELGAMAL hasKey, sendsKey;


    vector<char> add1 = {'0', '1', '1'};
    vector<char> add2 = {'0', '1', '0'};
    vector<char> sum = hasKey.BinaryAdd(add1, add2);

    cout << "\nBinary print: ";
    for (int i = 0; i < sum.size(); i++)
    {
        cout << sum[i];
    }

    return 0;
}
