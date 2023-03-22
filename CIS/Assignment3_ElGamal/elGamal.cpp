//*ELGAMAL Implementation
#include <iostream>
#include <string>
#include <fstream>
#include "elGamal.h"


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


//*Binary Calc Functions
void ELGAMAL::MakeEqualSize(string &first, string &second)
{
    int lenFirst = first.size();
    int lenSecond = second.size();
    string addToFront = "";

    if (lenFirst > lenSecond) //When first is longer
    {

        //Add extra 0s
        for (int i = 0; i < lenFirst-lenSecond; i++)
        {
            addToFront += '0';
        }
        //Add original value
        second = addToFront + second;
    
    }
    else if (lenSecond > lenFirst) //When second is longer
    {

        //Add extra 0s
        for (int i = 0; i < lenFirst-lenSecond; i++)
        {
            addToFront += '0';
        }
        //Add original value
        first = addToFront + first;
    
    }
}


//Shift string by certain amonut for binary multiplication
string ELGAMAL::MakeShiftedString(string shiftStr, int shiftCount)
{
    for (int i = 0; i < shiftCount; i++)
    {
        shiftStr += "0";
    }
    return shiftStr;
}


//Modular Exponentiation
//
string ELGAMAL::ModExpo(string base, string modulo, string exponent)
{
    
    //Declare variable for return  value
    string result = "1";

    
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

        base = Multiply(base, base) % modulo;

        if (exponent[i] == 1)
        {
            result = Multiply(base, result) % modulo;
        }

    }

    return result;
    
}


string ELGAMAL::Add(string add1, string add2)
{

    int i = add1.size() - 1;
    int j = add2.size() - 1;
    string sum = "";
    int carry = 0; //Carry for bit addition

    while (i >= 0 || j >= 0 || carry == 1)
    {
        carry += ((i >= 0) ? add1[i] - '0': 0);
        carry += ((j >= 0) ? add2[j] - '0': 0);
        
        sum = char(carry%2 + '0') + sum;

        carry /= 2;

        //Decrement i and j
        i--;
        j--;
    }

    return sum;
}

//!Change to subtraction
string Sub(string sub1, string sub2)
{
    int i = sub1.size() - 1;
    int j = sub2.size() - 1;
    string sum = "";
    int carry = 0; //Carry for bit subtraction

    while (i >= 0 || j >= 0 || carry == 1)
    {
        carry += ((i >= 0) ? sub1[i] - '0': 0);
        carry += ((j >= 0) ? sub2[j] - '0': 0);
        
        sum = char(carry%2 + '0') + sum;

        carry /= 2;

        //Decrement i and j
        i--;
        j--;
    }

    return sum;
}


string ELGAMAL::Multiply(string X, string Y)
{

    string result = "0";
    string shifted;
    int len = Y.size();

    //Add 
    for (int i = len-1; i >= 0; i--)
    {
        if (Y[i] == '1')
        {
            shifted = MakeShiftedString(X, len - (i+1));
            cout << "\nshifted:" << shifted << endl;
            result = Add(shifted, "0");
            cout << "\nresult:" << result << endl;
        }
        else
        {
            continue;
        }
    }

    return result;
}

