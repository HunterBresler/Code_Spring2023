//*ELGAMAL Implementation
#include <iostream>
#include <vector>
#include <fstream>
#include "elGamal.h"

using namespace std;

//*Constructors
ELGAMAL::ELGAMAL()
{

}


//* Getter/Setter Functions
void ELGAMAL::getPublicKey_fromFileStream()
{

}

void ELGAMAL::setPrime()
{

}

void ELGAMAL::setGenerator()
{

}

void ELGAMAL::setGen_PowA()
{

}


//*Calc Functions
//Modular Exponentiation
//
vector<char> ELGAMAL::ModExpo(vector<char> base, vector<char> modulo, vector<char> exponent)
{

    //Declare variable for return  value
    vector<char> result = 1;

    
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


vector<char> ELGAMAL::BinaryAdd(vector<char> add1, vector<char> add2)
{

}

vector<char> ELGAMAL::BinaryMultiply(vector<char> multi1, vector<char> multi2)
{

}

