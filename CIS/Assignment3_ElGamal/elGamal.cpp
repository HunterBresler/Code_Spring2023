//*ELGAMAL Implementation
#include <iostream>
#include <vector>
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


//*Calc Functions
void ELGAMAL::MakeEqualSize(vector<char> &first, vector<char> &second)
{
    int lenFirst = first.size();
    int lenSecond = second.size();
    vector<char> replaceSmaller; //Avoid insertion at front


    if (lenFirst > lenSecond) //When first is longer
    {
        replaceSmaller.reserve(lenFirst);

        //Add extra 0s
        for (int i = 0; i < lenFirst-lenSecond; i++)
        {
            replaceSmaller[i] = '0';
        }

        //Add original value
        for (int i = lenFirst-lenSecond; i < lenFirst; i++)
        {
            replaceSmaller[i] = second[i];
        }

        copy(replaceSmaller.begin(), replaceSmaller.end(), second.begin());
    
    }
    else if (lenSecond > lenFirst) //When second is longer
    {

        replaceSmaller.reserve(lenSecond);

        //Add extra 0s
        for (int i = 0; i < lenSecond-lenFirst; i++)
        {
            replaceSmaller[i] = '0';
        }

        //Add original value
        for (int i = lenSecond-lenFirst; i < lenSecond; i++)
        {
            replaceSmaller[i] = first[i];
        }

        copy(replaceSmaller.begin(), replaceSmaller.end(), first.begin());
    
    }
}

//Modular Exponentiation
//
vector<char> ELGAMAL::ModExpo(vector<char> base, vector<char> modulo, vector<char> exponent)
{
    /*
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
    */
   return base;
}


vector<char> ELGAMAL::BinaryAdd(vector<char> add1, vector<char> add2)
{
    //Makes both parameters equal in size
    MakeEqualSize(add1, add2);

    vector<char> sum(add1.size());
    char carry = '0'; //Carry for bit addition

    for (int i = add1.size()-1; i >= 0; i--)
    {
        
        if (add1[i] == '1' && add2[i] == '1')
        {
            sum[i] = carry;
            carry = '1';

            //If the last digits and carry add to 1 or 2, add a 1 in front of sum
            if (i == 0)
            {
                sum.insert(sum.begin(), '1');
            }
        }
        else if (add1[i] == '0' && add2[i] == '0')
        {
            sum[i] = carry;
            carry = '0';
        }
        else if (carry == '1')
        {
            sum[i] = '0';
            carry = '1';

            //If the last digits and carry add to 1 or 2, add a 1 in front of sum
            if (i == 0)
            {
                sum.insert(sum.begin(), '1');
            }
        }
        else if (carry == '0')
        {
            sum[i] = '1';
        }
    }

    return sum;
}

vector<char> ELGAMAL::BinaryMultiply(vector<char> multi1, vector<char> multi2)
{
    MakeEqualSize(multi1, multi2);

    return multi1;
}

