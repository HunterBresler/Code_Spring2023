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
void ELGAMAL::getPublicKey_fromFile()
{
    string line;
    fin.open("Public_key.txt");

    //Get prime from file
    getline(fin, line);
    line = line.substr(line.find(": ")+2); // increment to cut out the ": "
    prime = line;

    //Get generator from file
    getline(fin, line);
    line = line.substr(line.find(": ")+2);
    generator = line;

    //Get generator_pow_private_key from file
    getline(fin, line);
    line = line.substr(line.find(": ")+2);
    generator_pow_private_key = line;

}


void ELGAMAL::getPlainText_fromFile()
{

    string line;
    plain_text = "";
    fin.open("Plain_text.txt");

    //read the whole plain text
    while (fin)
    {
        //Get plain text from file
        getline(fin, line);
        plain_text += line;
    }

}


void ELGAMAL::getCipherText_fromFile()
{

    string line;
    cipher_text = "";
    fin.open("Cipher_text.txt");

    //read the whole cipher text
    while (fin)
    {
        //Get cipher text from file
        getline(fin, line);
        cipher_text += line;
    }

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


//Binary Modular Exponentiation
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

        base = Multiply(base, base);// % modulo;

        if (exponent[i] == 1)
        {
            result = Multiply(base, result);// % modulo;
        }

    }

    return result;
    
}


//Binary Addition
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


//Binary subtraction
//WILL NOT COMPUTE NEGATIVES
string ELGAMAL::Sub(string minuend, string subtrahend)
{
    string sum = "";

    //Make sure they are equal in size
    MakeEqualSize(minuend, subtrahend);

    //check for negatives (kinda)
    if (minuend.size() < subtrahend.size() || minuend == subtrahend)
    {
        cout << "Error: ELGAMAL::Sub cannot compute ";
        return "0";
    }


    //Replace subtrahend with it's 1s complement
    for (int i = 0; i < subtrahend.size(); i++)
    {
        subtrahend[i] = ((subtrahend[i] == '1') ? '0': '1');
    }


    //Add minuend and the 1s complement for subtraction
    sum = Add(minuend, subtrahend);

    //Check for carry and add it back into sum
    if (sum.size() > minuend.size())
    {
        sum.erase(sum.begin());
        sum = Add(sum, "1");
    }

    return sum;
}


string ELGAMAL::Xor(string a, string b)
{
    //Xor the input strings a and b
    //Assume a and b are equal in size
    string result = ""; 
	for(int i = 0; i < a.size(); i++)
    { 
		if(a[i] != b[i])
        { 
			result += "1"; 
		}
		else
        { 
			result += "0"; 
		} 
	} 

	return result; 
}


//Binary Multiplication
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
            //Uses repeated addition to multiply
            shifted = MakeShiftedString(X, len - (i+1));
            result = Add(shifted, result);
        }
        else
        {
            continue;
        }
    }

    return result;
}

string ELGAMAL::Modulus(string divadend, string divisor)
{

    string result = divadend;
    string shifted;
    int len = divadend.size();

    //Sub
    while (divisor.size() <= result.size())
    {
        if (result[0] == '1')
        {
            //Uses Xor to divide
            shifted = MakeShiftedString(divisor, result.size()-divisor.size());
            result = Xor(shifted, result);
        }
        else
        {
            result.erase(result.begin());
        }
    }

    return result;
}
