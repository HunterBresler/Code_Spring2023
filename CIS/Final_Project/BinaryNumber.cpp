//*BinaryNumber Implementation
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "BinaryNumber.h"

//*Constructors
BinaryNumber::BinaryNumber()
{
    number = "0";
}

BinaryNumber::BinaryNumber(string num)
{
    number = num;
}

BinaryNumber::BinaryNumber(char num)
{
    number = num;
}

//* Getter/Setter Functions
string BinaryNumber::get_Number()
{
    return number;
}

int BinaryNumber::size() const
{
    return number.size();
}

void BinaryNumber::set_Number(string newNum)
{
    number = newNum;
}


//*Binary Overload Operations
string operator+(const BinaryNumber &num1, const BinaryNumber &num2)
{
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    string sum = "";
    int carry = 0; //Carry for bit addition

    while (i >= 0 || j >= 0 || carry == 1)
    {
        carry += ((i >= 0) ? num1.number[i] - '0': 0);
        carry += ((j >= 0) ? num2.number[j] - '0': 0);
        
        sum = char(carry%2 + '0') + sum;

        carry /= 2;

        //Decrement i and j
        i--;
        j--;
    }

    return sum;
}

string operator-(const BinaryNumber &minuend, const BinaryNumber &subtrahend)
{
    string result = "0";

    //Short circuit if minuend  and subtrahend are equal
    if (minuend == subtrahend)
    {
        return "0";
    }

    //Make sure minuend is greater than subtrahend
    if (minuend > subtrahend)
    {
        cout << "\nError: ELGAMAL::minuend must be larger than subtrahend";
        return "0";
    }

    //Make sure they are equal in size
    result = subtrahend.PadLeft(minuend.size() - subtrahend.size()); 


    //Replace subtrahend with it's 1s complement
    for (int i = 0; i < subtrahend.size(); i++)
    {
        result[i] = ((subtrahend[i] == '1') ? '0': '1');
    }

    //Add minuend and the 1s complement for subtraction
    result += minuend;

    //Check for carry and add it back into sum
    if (result.size() > minuend.size())
    {
        result.erase(result.begin()); //Remove the first element
        result += '1';
    }

    //Remove excess 0s
    while (result[0] == '0')
    {
        result.erase(result.begin()); //Remove the first element
    }

    return result.number;
}

string operator*(const BinaryNumber &num1, const BinaryNumber &num2)
{
    string result = "0";
    string shifted;
    int len = num2.size();

    //Add 
    for (int i = len-1; i >= 0; i--)
    {
        if (num2[i] == '1')
        {
            //Uses repeated addition to multiply
            shifted = MakeShiftedString(num1, len - (i+1));
            result += shifted;
        }
        else
        {
            continue;
        }
    }

    return result;
}

string operator/(const BinaryNumber &divadend, const BinaryNumber &divisor)
{

}

string operator%(const BinaryNumber &divadend, const BinaryNumber &divisor)
{

}

bool operator>(const BinaryNumber &num1, const BinaryNumber &num2)
{

}

bool operator<(const BinaryNumber &num1, const BinaryNumber &num2)
{

}

bool operator>=(const BinaryNumber &num1, const BinaryNumber &num2)
{

}

bool operator<=(const BinaryNumber &num1, const BinaryNumber &num2)
{

}

bool operator==(const BinaryNumber &num1, const BinaryNumber &num2)
{

}

void BinaryNumber::operator=(const BinaryNumber &num2)
{
    number = num2.number;
}

void operator+=(BinaryNumber &num1, const BinaryNumber &num2)
{
    num1 = num1 + num2;
}

void operator-=(BinaryNumber &num1, const BinaryNumber &num2)
{
    num1 = num1 - num2;
}

void operator*=(BinaryNumber &num1, const BinaryNumber &num2)
{
    num1 = num1 * num2;
}

void operator/=(BinaryNumber &num1, const BinaryNumber &num2)
{
    num1 = num1 / num2;
}

void operator%=(BinaryNumber &num1, const BinaryNumber &num2)
{
    num1 = num1 % num2;
}


char BinaryNumber::operator[](const int &index) const
{
    if (index > number.size() || index < 0)
    {
        cout << "\nError:Index Out of Bounds";
        exit(0);
    }
    return number[index];
}

char& BinaryNumber::operator[](const int &index)
{
    if (index > number.size() || index < 0)
    {
        cout << "\nError:Index Out of Bounds";
        exit(0);
    }
    return number[index];
}


//*Binary Calc Functions
string BinaryNumber::PadRight(int PadCount) const
{
    string shifted = number;

    for (int i = 0; i < PadCount; i++)
    {
        shifted += "0";
    }
    return shifted;
}

string BinaryNumber::PadLeft(int PadCount) const
{
    string shifted = number;

    for (int i = 0; i < PadCount; i++)
    {
        shifted = "0" + shifted;
    }
    return shifted;
}

string ModExpo(const BinaryNumber &base, const BinaryNumber &exponent, const BinaryNumber &modulo);
string Xor(const BinaryNumber &num1, const BinaryNumber &num2);
string getRandom(const BinaryNumber &min, const BinaryNumber &max);