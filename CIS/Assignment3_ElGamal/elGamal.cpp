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
string ELGAMAL::ModExpo(string base, string exponent, string modulo)
{
    
    //Declare variable for return  value
    string result = "1";

    //Short circuit if modulo is 1
    if (modulo == "1")
    {
        return "0";
    }

    //Short circuit to prevent error with the next if statement
    if (exponent.size() == 0)
    {   
        cout << "\nError:Exponent cannot be an empty value";
        return result;
    }

    
    if (exponent[0] == '1')
    {
        result = base;
    }

    //Checks for the exponent being 1 or 0
    if (exponent.size() == 1)
    {
        return Modulus(result, modulo);
    }
    
    for (int i = 1; i < exponent.size(); i++)
    {

        result = Modulus(Multiply(result, result), modulo);

        if (exponent[i] == '1')
        {
            result = Modulus(Multiply(base, result), modulo);
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


bool ELGAMAL::IsGreaterThan(string large, string small)
{
    int lSize = large.size();
    int sSize = small.size();
    bool equal = true;

    //check for negatives
    if (lSize < sSize)
    {
        return false;
    }
    else if (lSize == sSize) //make sure large is larger than small
    {
        for (int i = 0; i < lSize; i++)
        {
            if (large[i] != small[i] && small[i] == '1')
            {
                return false;
            }
            else if (large[i] == '1' && small[i] == '0')
            {
                equal = false;
                break;
            }
        }

        //Check if they're equal
        if (equal)
        {
            return false;
        }
    }

    return true;

}

//Binary subtraction
//WILL NOT COMPUTE NEGATIVES
string ELGAMAL::Sub(string minuend, string subtrahend)
{
    string sum = "";

    //Short circuit if minuend  and subtrahend are equal
    if (minuend == subtrahend)
    {
        return "0";
    }

    //Make sure minuend is greater than subtrahend
    if (!IsGreaterThan(minuend, subtrahend))
    {
        cout << "\nError: ELGAMAL::minuend must be larger than subtrahend";
        return "0";
    }

    //Make sure they are equal in size
    MakeEqualSize(minuend, subtrahend);


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

    //Remove excess 0s
    while (sum[0] == '0')
    {
        sum.erase(sum.begin());
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


    //Sub
    while (divisor.size() <= result.size())
    {
        if (result[0] == '1')
        {
            //Uses Sub to divide
            shifted = MakeShiftedString(divisor, result.size()-divisor.size());

            //Make sure shifted is greater than or equal to result before sub
            if (IsGreaterThan(result, shifted) || result == shifted)
            {
                result = Sub(result, shifted);
            }
            else if (result.size() > divisor.size()) //In case the shift makes result larger than divisor
            {
                shifted.pop_back();
                result = Sub(result, shifted);
            }
            else
            {
                break;
            }
        }
        else
        {
            result.erase(result.begin());
        }
    }

    //Check for no remainder
    //if (result.size() == 0)
    //{
    //    return "0";
    //}

    return result;
}
