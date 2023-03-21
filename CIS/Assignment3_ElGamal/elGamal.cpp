//*ELGAMAL Implementation
#include <iostream>
#include <vector>
#include "elGamal.h"

using namespace std;

//*Getter/Setter Functions


//*Calc Functions
//Modular Exponentiation
int ELGAMAL::ModExpo(int base, int modulo, int expo)
{
    
    //Convert expo to binary
    //Declare variable
    int i = 0;
    vector<int> exponent = {};

    //Loop to convert the exponent to binary
    while (expo > 0)
    {
        exponent.push_back(expo%2);
        expo = (expo - exponent[i])/2;
        i++;
    }


    //modular expo
    //Any number mod 1 is 0
    if (modulo == 1)
    {
        return 0;
    }
    
    //Declare variable for return  value
    int result = 1;

    
    //Short circuit to prevent error with the next if statement
    if (exponent.size() == 0)
    {
        return result;
    }

    
    if (exponent[0] == 1)
    {
        result = base;
    }


    
    for (int i = 1; i < exponent.size(); i++)
    {

        base = (base*base) % modulo;

        if (exponent[i] == 1)
        {
            result = (base*result) % modulo;
        }

    }

    return result;
}